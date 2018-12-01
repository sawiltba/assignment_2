#ifndef __SHL_H
#define __SHL_H
#include "Component.h"

class shl: public Component {
	private:
		static int number;
	public:
		shl(Netlist* netlist, std::string line){
			this->netlist = netlist;
			this->idName = "shl";
			this->componentName = "SHL";
			this->calcIOs("<<", line);
			id = number++;
			cmpID = componentNumber++;
            this->checkRegisters();
		}

		std::string toString(){
			std::string toReturn;
			//[S]<cName> #(.DATAWIDTH(<width>)) <id> (a, b, sum);\n
			size_t len = 26
				+ this->componentName.length() 
				+ this->IOStrLen()
				+ this->getID().length()
				+ std::to_string(this->getWidth()).length();
			toReturn.resize(len);
			char* str = (char*)malloc(len + 1);
			sprintf(str, "%s #(.DATAWIDTH(%d)) %s (%s, %s, %s);\n",
					this->componentName.c_str(), this->getWidth(), 
					this->getID().c_str(), inputs[0].c_str(), inputs[1].c_str(),
					outputs[0].c_str());
			toReturn.assign(str);
			free(str);
			return toReturn;
		}

};

int shl::number = 0;

#endif
