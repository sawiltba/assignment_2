#ifndef __REG_H
#define __REG_H
#include "Component.h"

class reg: public Component {
	public:
		reg(Netlist *netlist, std::string line){
			this->netlist = netlist;
			std::vector<std::string> tokens;
			size_t begin = 0, end = line.find(" ");
			while(end != std::string::npos){
				tokens.push_back(line.substr(begin, end - begin));
				begin = end + 1;
				end = line.find(" ", begin);
			}
			tokens.push_back(line.substr(begin, end));
			//Tokens is {"register", "[U]Int#", "name"}

			this->idName = tokens[2];
			this->inputs.push_back("clk");
			this->inputs.push_back("rst");
			this->inputs.push_back(tokens[2] + "_in");
			this->outputs.push_back(tokens[2] + "_out");
			this->componentName = "REG";
			this->id = 0;
		}

		std::string getID() override {
			return idName;
		}

		std::string toString() override {
			std::string toReturn;
			//[S]REG #(.DATAWIDTH(<width>)) <id> (clk, rst, d, q);\n
			size_t len = 31 
				+ this->IOStrLen()
				+ this->getID().length()
				+ std::to_string(this->getWidth()).length();
			toReturn.resize(len);
			char* str = (char*)malloc(len + 1);
			sprintf(str, "%s #(.DATAWIDTH(%d)) %s (%s, %s, %s, %s);\n",
                    this->componentName.c_str(), this->getWidth(), 
                    this->getID().c_str(), inputs[0].c_str(), 
					inputs[1].c_str(), inputs[2].c_str(),
					outputs[0].c_str());
			toReturn.assign(str);
			free(str);
			return toReturn;
		}
};

#endif
