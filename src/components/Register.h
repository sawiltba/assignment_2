#ifndef __REG_H
#define __REG_H
#include "Component.h"

class reg: public Component {
	private:
		static int number;

	public:
		reg(Netlist* netlist, std::string line){
			this->netlist = netlist;
			size_t begin = 0, end = 0;
			id = number;
			number++;
			end = line.find("=");
			outputs.push_back(line.substr(begin, end - 1));
			begin = end + 2;
			end = line.find("+");
			inputs.push_back(line.substr(begin, end - begin - 1));
			begin = end + 2;
			end = line.length();
			inputs.push_back(line.substr(begin, end - begin));
		}

		int getNumber(){
			return number;
		}

		std::string toString() override{
			std::string toReturn;
			//REG #(.DATAWIDTH(<width>)) <id> (clk, rst, d, q);\n
			size_t len = 29 
				+ this->IOStrLen()
				+ this->getID().length()
				+ std::to_string(this->getWidth()).length();
			toReturn.resize(len);
			char* str = (char*)malloc(len + 1);
			sprintf(str, "ADD #(.DATAWIDTH(%d)) %s (%s, %s, %s);\n",
					this->getWidth(), this->getID().c_str(), 
					inputs[0].c_str(), inputs[1].c_str(),
					outputs[0].c_str());
			toReturn.assign(str);
			free(str);
			return toReturn;
		}

		std::string getID() override{
			std::string toReturn = "a" + std::to_string(id);
			return toReturn;
		}
};

#endif