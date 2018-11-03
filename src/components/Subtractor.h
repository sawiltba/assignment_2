#ifndef __SUB_H
#define __SUB_H

#include "Component.h"

class sub: public Component {
	private:
		static int number;
	public:
		sub(Netlist *net, std::string line){
			this->idName = "s";
			this->componentName = "SUB";
			netlist = net;
			id = number;
			number++;
			this->calcIOs("-", line);
		}

		std::string toString(){
			std::string toReturn;
			bool sign = this->isSigned();
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
			return (sign ? "S" : "") + toReturn;
		}

};

int sub::number = 0;

#endif
