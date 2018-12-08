#include "Netlist.h"
#include "components/Component.h"
#include "components/Adder.h"
#include "components/Comparator.h"
#include "components/Component.h"
#include "components/Multiplexor.h"
#include "components/Multiplier.h"
#include "components/Register.h"
#include "components/ShiftLeft.h"
#include "components/ShiftRight.h"
#include "components/Subtractor.h"

Netlist::Netlist(){

}

int Netlist::addRegister(std::string line){
    std::vector<std::string> tokens = this->tokenize(line);
    if(tokens.size() < 3){
        //ERROR
        return 1;
    }

    //tokens is {"register", "[U]Int#", "name1", ...}
    bool sign = tokens[1][0] == 'I'; //If signed, sign is true
    size_t numLoc = tokens[1].find("t") + 1;
    int width = std::stoi(tokens[1].substr(numLoc,
                std::string::npos));

    std::vector<Variable> newVars;
    std::vector<std::shared_ptr<Component>> newRegs;
    for(unsigned i = 2; i < tokens.size(); i++){
        newVars.push_back(Variable{tokens[i] + "_in",
                "wire", width, sign});
        newVars.push_back(Variable{tokens[i] + "_out",
                "wire", width, sign});
        std::shared_ptr<reg> a = std::shared_ptr<reg>{
            new reg{this, tokens[0] + " " + tokens[1] + " " + tokens[i]}
        };
        newRegs.push_back(a);
    }

    wires.insert(wires.end(), newVars.begin(), newVars.end());
    operations.insert(operations.end(), newRegs.begin(), newRegs.end());
    return 0;

}

int Netlist::addVariable(std::string line){
    std::vector<std::string> tokens = this->tokenize(line);

    if(tokens.size() < 3){
        //ERROR
        return 1;
    }

    //tokens is {"<input/output/wire>", "[U]Int#", "name1", ...}
    bool sign = tokens[1][0] == 'I'; //If signed, sign is true
    size_t numLoc = tokens[1].find("t") + 1;
    int width = std::stoi(tokens[1].substr(numLoc,
                std::string::npos));

    std::vector<Variable> newVars;
    for(unsigned i = 2; i < tokens.size(); i++){
        newVars.push_back(Variable{tokens[i],
                tokens[0], width, sign});
    }

    if(tokens[0] == "input"){
        inputs.insert(inputs.end(), newVars.begin(), newVars.end());
    } else if(tokens[0] == "variable"){
        wires.insert(wires.end(), newVars.begin(), newVars.end());
    } else if(tokens[0] == "output"){
        outputs.insert(outputs.end(), newVars.begin(), newVars.end());
    } else {
        //ERROR
        return 1;
    }
    return 0;
}

std::vector<std::string> Netlist::tokenize(std::string line){
    std::vector<std::string> tokens;
    //Get rid of commas
    while(line.find(",") != std::string::npos){
        line.erase(line.find(","), 1);
    }

    size_t begin = 0, end = line.find_first_of(" \t\n"), len = end - begin;
    while(end != std::string::npos){
        std::string token = line.substr(begin, len);
        while(token.find_first_of(" \t\n") != std::string::npos){
            token.erase(token.find_first_of(" \t\n"), 1);
        }
        if(token.size() > 0){
            tokens.push_back(token);
        }
        begin = end + 1;
        end = line.find_first_of(" \t\n", begin);
        len = end - begin;
    }
    std::string token = line.substr(begin, end);
    while(token.find_first_of(" \t\n") != std::string::npos){
        token.erase(token.find_first_of(" \t\n"), 1);
    }
    if(token.size() > 0){
        tokens.push_back(token);
    }
    return tokens;
}

void Netlist::insertComponents(std::vector<std::shared_ptr<Component>> toInsert){
    operations.insert(operations.end(), toInsert.begin(), toInsert.end());
}

void Netlist::pushComponent(std::shared_ptr<Component> toAdd){
    operations.push_back(toAdd);
}


int Netlist::addComponent(std::string line){
    std::vector<std::string> tokens = this->tokenize(line);
	std::shared_ptr<Component> cmpt;
    if(line.find("register") != std::string::npos){
        return this->addRegister(line);
    } else if(line.find("<<") != std::string::npos){
        cmpt = std::shared_ptr<shl>{new shl{this, line}};
    } else if(line.find(">>") != std::string::npos){
        cmpt = std::shared_ptr<shr>{new shr{this, line}};
    } else if(line.find("<") != std::string::npos ||
            line.find(">") != std::string::npos ||
            line.find("==") != std::string::npos){
        cmpt = std::shared_ptr<comp>{new comp{this, line}};
    } else if(line.find("+") != std::string::npos){
        cmpt = std::shared_ptr<add>{new add{this, line}};
    } else if(line.find("-") != std::string::npos){
        cmpt = std::shared_ptr<sub>{new sub{this, line}};
    } else if(line.find("*") != std::string::npos){
        cmpt = std::shared_ptr<mult>{new mult{this, line}};
    } else if(line.find("?") != std::string::npos){
        cmpt = std::shared_ptr<mux>{new mux{this, line}};
    } else if(line.find("=") != std::string::npos && tokens.size() == 3){
        //TODO: remove this?
		cmpt = std::shared_ptr<reg>{new reg{this, line, 1}};
        if(!cmpt->foundRegister()){
            operations.push_back(cmpt);
        }
    } else {
        return 1; //ERROR
    }
	findDependencies(cmpt);
    operations.push_back(cmpt);
    return 0;
}

void Netlist::findDependencies(std::shared_ptr<Component> cmpt){
	for (int i = 0; i < cmpt->getInputs().size(); i++) {
		for (int j = 0; j < operations.size(); j++) {
			//if(cmpt->getMasters().size() != 0){
				if (std::find(cmpt->getMasters().begin(), cmpt->getMasters().end(), operations.at(j)) == cmpt->getMasters().end()) {
					for (int k = 0; k < operations.at(j)->getOutputs().size(); k++) {
						if (cmpt->getInputs().at(i).compare(operations.at(j)->getOutputs().at(k)) == 0) {
							cmpt->addMaster(operations.at(j));
						}
					}
				}
			//}
			/*else{
				for (int k = 0; k < operations.at(j)->getOutputs().size(); k++) {
					if (cmpt->getInputs().at(i).compare(operations.at(j)->getOutputs().at(k)) == 0) {
					cmpt->addMaster(operations.at(j));
					}
				}
			}*/
		}
	}
}

std::vector<std::shared_ptr<Cycle>>& Netlist::getCycles(int latency, int* error) {
	cycles = std::vector<std::shared_ptr<Cycle>>{};
	for (int j = 1; j <= latency; j++) {
		std::shared_ptr<Cycle> newCycle{new Cycle{j}};
		for (int i = 0; i < operations.size(); i++) {
			if (operations.at(i)->getStartTime() == j) {
				newCycle->pushComponent(operations.at(i));
			}
			else if (operations.at(i)->getStartTime() > latency) {
				*error = 1;
				return cycles;
			}
		}
		newCycle->createStates();
		cycles.push_back(newCycle);
	}

	return cycles;
}
