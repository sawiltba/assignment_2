#ifndef __ADDER_H
#define __ADDER_H
#include "Component.h"
#include "Netlist.h"

class add: public Component {
	private:
		static int number = 0;

	public:
		add(Netlist* netlist, std::string line){
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
			end = line.length() - 1;
			inputs.push_back(line.substr(begin, end - begin - 1));
		}

		std::string toString() override{
			std::string toReturn;
			//ADD #(.DATAWIDTH(<width>)) <id> (a, b, sum);
			size_t len = 29;
			
		}

}


#endif
