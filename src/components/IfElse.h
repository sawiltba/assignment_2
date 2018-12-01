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

		ifelse(Netlist* netlist){
			this->netlist = netlist;
			this->idName = "ifelse";
			this->componentName = "IFELSE";
			this->latency = 1;
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

		std::string toString() override{
			std::string toReturn;
			int loop = 0;
			//if ('condition')
			toReturn += "if ( ";
			toReturn += this->condition;
			toReturn += " )\n";
			toReturn += "begin\n";

            while(loop < if_branch.operations.size()){
                //if_branch.getComponents().at(loop)->getComponentName();
                toReturn += if_branch.getComponents().at(loop)->toString();
                toReturn += "\n";
                loop++;
            }
            loop = 0;
            toReturn += "end\n";

            while(loop < else_branch.operations.size()){
                toReturn += else_branch.getComponents().at(loop)->toString();
                toReturn += "\n";
                loop++;
            }
            loop = 0;
            toReturn += "end\n";

			return toReturn;
		}
};

int ifelse::number = 0;

#endif
