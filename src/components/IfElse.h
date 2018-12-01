#ifndef __IFELSE_H
#define __IFELSE_H
#include "Component.h"

class ifelse: public Component {
	private:
		static int number;

	public:
	    std::vector<Component> if_branch;
	    std::vector<Component> else_branch;

		ifelse(Netlist* netlist, std::string line){
			this->netlist = netlist;
			this->idName = "ifelse";
			this->componentName = "IFELSE";
			id = number;
			number++;
		}

		void addIfElseComponent(int tf, std::string line){
            //copy of add component minus the section of the ifelse

            //add inputs for all sub components

            //add outputs for all sub components
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
