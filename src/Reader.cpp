#include <iostream>
#include <algorithm>
#include "Reader.h"
#include "components/IfElse.h"


using namespace std;

void addDependencies(vector<shared_ptr<Component>> branch_ops, vector<shared_ptr<Component>> net_ops, 
		vector<string> hlsm_inputs){
    for(auto branchOp : branch_ops){
        while(branchOp->missingMaster(hlsm_inputs)){
            string unlinkedInput = branchOp->getUnlinkedInput(hlsm_inputs);
            for(auto net_itr = net_ops.rbegin(); net_itr != net_ops.rend(); net_itr++){
                if(find((*net_itr)->getOutputs().begin(), 
							(*net_itr)->getOutputs().end(), 
							unlinkedInput) != (*net_itr)->getOutputs().end()){
                    branchOp->addMaster(*net_itr);
                    break;
                }
            }
        }
    }
}

Netlist read(ifstream &inFile, int* error){
    Netlist net;
    string line;
    int comment = -1;

    while(getline(inFile, line)){
        //remove any comments if found
        comment = line.find("//");
        if(comment != -1){
            line.resize(comment);
        }

        if(!line.compare("\0")){
            //ignore only newline
        }
		else if(line.find("if") != -1){
            //if ( t ) {...
            auto tokens = net.tokenize(line);
			shared_ptr<ifelse> newIf = shared_ptr<ifelse>{new ifelse{&net, tokens[2]}};
			Netlist trueBranch = read(inFile, error);
            Netlist falseBranch;
            auto loc = inFile.tellg();
            string next;
            getline(inFile, next);
            if(next.find("else") != -1){
                falseBranch = read(inFile, error);
            } else {
                inFile.seekg(loc);
            }
			auto trueOps = trueBranch.getComponents();
            auto falseOps = falseBranch.getComponents();
            for(auto op : trueOps){
                op->addMaster(newIf);
				op->addBranch(true);
            }
            for(auto op : falseOps){
                op->addMaster(newIf);
				op->addBranch(false);
            }
			vector<string> hlsm_inputs;
			for(Variable v : net.getInputs()){
				hlsm_inputs.push_back(v.getName());
			}
            addDependencies(trueOps, net.getComponents(), hlsm_inputs);
            addDependencies(falseOps, net.getComponents(), hlsm_inputs);
            net.pushComponent(newIf);
            net.insertComponents(trueOps);
            net.insertComponents(falseOps);
		}
		else if(line.find("}") != -1){
            return net;
		}
        else if(line.find("=") != -1 || line.find("register") != -1){//equals found, component parser
			if (net.addComponent(line) == 1) {
				cout << "add component errors in line " << line << endl;
				*error = 1;
				return net;
			 }
        }
        else{//no equals, variable parser
			if (net.addVariable(line) == 1) {
				cout << "Add Variable errors " << line << endl;
				*error = 1;
				return net;
			}
        }

    }
    return net;
}
