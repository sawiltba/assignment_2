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
			id = number;
			number++;
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
			//MUX2x1 #(.DATAWIDTH(<width>)) <id> (a, b, sel, sum);\n
			size_t len = 34
				+ this->IOStrLen()
				+ this->getID().length()
				+ std::to_string(this->getWidth()).length();
			toReturn.resize(len);
			char* str = (char*)malloc(len + 1);
			sprintf(str, "MUX2x1 #(.DATAWIDTH(%d)) %s (%s, %s, %s, %s);\n",
					this->getWidth(), this->getID().c_str(),
					inputs[1].c_str(), inputs[2].c_str(), inputs[0].c_str(),
					outputs[0].c_str());
			toReturn.assign(str);
			free(str);
			return toReturn;
		}
};

int ifelse::number = 0;

#endif
