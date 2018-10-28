#ifndef __SUB_H
#define __SUB_H

#include "Component.h"

class sub: public Component {
	private:
		static int number;
	public:
		sub(Netlist *net, std::string line){
			netlist = net;
			id = number;
			number++;
			size_t begin = 0, end;
			end = line.find("=");
			outputs.push_back(line.substr(begin, end - 1));
			begin = end + 2;
			end = line.find("-");
			inputs.push_back(line.substr(begin, end - begin - 1));
			begin = end + 2;
			end = line.length();
			inputs.push_back(line.substr(begin, end - begin));
		}

		std::string toString() override{
			std::string toReturn;
			//ADD #(.DATAWIDTH(<width>)) <id> (a, b, sum);\n
			size_t len = 29 
				+ this->IOStrLen()
				+ this->getID().length()
				+ std::to_string(this->getWidth()).length();
			toReturn.resize(len);
			char* str = (char*)malloc(len + 1);
			sprintf(str, "SUB #(.DATAWIDTH(%d)) %s (%s, %s, %s);\n",
					this->getWidth(), this->getID().c_str(), 
					inputs[0].c_str(), inputs[1].c_str(),
					outputs[0].c_str());
			toReturn.assign(str);
			free(str);
			return toReturn;
		}

		std::string getID() override{
			std::string toReturn = "s" + std::to_string(id);
			return toReturn;
		}


};

sub::number = 0;

#endif
