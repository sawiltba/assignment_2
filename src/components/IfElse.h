#ifndef __IFELSE_H
#define __IFELSE_H
#include "Component.h"

class ifelse: public Component {
	private:
		static int number;
		std::string condition;

	public:
	    Netlist if_branch;
	    Netlist else_branch;

		ifelse(Netlist* netlist, std::string input){
            this->condition = input;
            this->inputs.push_back(input);
			this->netlist = netlist;
			this->idName = "ifelse";
			this->componentName = "IFELSE";
			this->latency = 0;
			id = number;
			number++;
		}

        int* ListRIfElse(){
            int aIfElse[3];
            int aIf[3] = ListR(if_branch);
            int aElse[3] = ListR(else_branch);

            if(aIf[0] > aElse[0]){
                aIfElse[0] = aIf[0];
            }
            else{
                aIfElse[0] = aElse[0];
            }

            if(aIf[1] > aElse[1]){
                aIfElse[1] = aIf[1];
            }
            else{
                aIfElse[1] = aElse[1];
            }

            if(aIf[2] > aElse[2]){
                aIfElse[2] = aIf[2];
            }
            else{
                aIfElse[2] = aElse[2];
            }

            return aIfElse;
        }

		int latencyIfElse(){
            int lat = this->latency;
            int lat_if = alap(if_branch);
            int lat_else = alap(else_branch);
            if(lat_if > lat_else){
                lat += lat_if;
            }
            else{
                lat += lat_else;
            }
            return lat;
		}

		void calcIOsIfElse(){
		    int loop = 0;
		    while(loop < if_branch.inputs.size()){
                outputs.push_back(if_branch.inputs.at(loop);
                loop++;
		    }
		    loop = 0;
		    while(loop < if_branch.outputs.size()){
                outputs.push_back(if_branch.outputs.at(loop);
                loop++;
		    }
		    loop = 0;

		    while(loop < else_branch.inputs.size()){
                outputs.push_back(else_branch.inputs.at(loop);
                loop++;
		    }
		    loop = 0;
		    while(loop < else_branch.outputs.at(loop)){
                inputs.push_back(else_branch.inputs.at(loop));
                loop++;
		    }
		    loop = 0;
        }

		int getNumber(){
			return number;
		}

		void setIfElseMaster(){
		    if(this->if_branch.getComponents().size()){
                this->addMaster(this->if_branch.getComponents().front()->getMasters());
		    }
		    else{
                this->addMaster(this->else_branch.getComponents().front()->getMasters());
		    }
		}

		void setIfElseYounglings(){
		    if(this->if_branch.getComponents().size()){
                this->addYoungling(this->if_branch.getComponents().back()->getYounglings());
		    }
		    else{
                this->addYoungling(this->else_branch.getComponents().back()->getYounglings());
		    }
		}

		void setTrue(){
		    int loop = 0;
            while(loop < this->if_branch.getComponents().size()){
                this->if_branch.getComponents().at(loop)->getIfBranches().push_back(true);
                loop++;
            }
		}

		void setFalse(){
		    int loop = 0;
            while(loop < this->if_branch.getComponents().size()){
                this->else_branch.getComponents().at(loop)->getIfBranches().push_back(false);
                loop++;
            }
		}

		std::string toString() override{
			std::string toReturn;
			int loop = 0;
			//if ('condition')
			toReturn += "if ( ";
			toReturn += this->condition;
			toReturn += " ) begin\n";
			toReturn += this->nextState[0];
            toReturn += "end\n";
			toReturn += "else begin\n";
			toReturn += this->nextState[1];
            toReturn += "end\n";
			return toReturn;
		}
};

int ifelse::number = 0;

#endif
