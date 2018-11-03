#ifndef __MULT_H
#define __MULT_H
#include "Component.h"

class mult: public Component {
	private:
		static int number;

	public:
		mult(Netlist* netlist, std::string line){
			this->netlist = netlist;
            this->componentName = "MULT";
            this->idName = "mult";
			id = number;
			number++;
            this->calcIOs("*", line);
/*			size_t begin = 0, end = 0;
			end = line.find("=");
			outputs.push_back(line.substr(begin, end - 1));
			begin = end + 2;
			end = line.find("*");
			inputs.push_back(line.substr(begin, end - begin - 1));
			begin = end + 2;
			end = line.length();
			inputs.push_back(line.substr(begin, end - begin));
*/		}

/*		std::string toString() override{
			std::string toReturn;
			//MULT #(.DATAWIDTH(<width>)) <id> (a, b, sum);\n
			size_t len = 30 
				+ this->IOStrLen()
				+ this->getID().length()
				+ std::to_string(this->getWidth()).length();
			toReturn.resize(len);
			char* str = (char*)malloc(len + 1);
			sprintf(str, "MULT #(.DATAWIDTH(%d)) %s (%s, %s, %s);\n",
					this->getWidth(), this->getID().c_str(), 
					inputs[0].c_str(), inputs[1].c_str(),
					outputs[0].c_str());
			toReturn.assign(str);
			free(str);
			return toReturn;
		}

		std::string getID() override{
			std::string toReturn = "mult" + std::to_string(id);
			return toReturn;
		}
*/
};

int mult::number = 0;

#endif
