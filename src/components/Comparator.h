#ifndef __COMP_H
#define __COMP_H
#include "Component.h"

class comp: public Component {
	private:
		static int number;
		void calcIOs(std::string operation, std::string line) override {
			size_t begin = 0, end = 0;
			end = line.find("=");
			std::string output = line.substr(begin, end - 1);
			begin = end + 2;
			end = line.find(operation);
			inputs.push_back(line.substr(begin, end - begin - 1));
			begin = end + operation.length() + 1;
			end = line.length();
			inputs.push_back(line.substr(begin, end - begin));
			if(operation == ">"){
				outputs.push_back(output);
				outputs.push_back("null");
				outputs.push_back("null");
			} else if(operation == "=="){
				outputs.push_back("null");
				outputs.push_back("null");
				outputs.push_back(output);
			} else if(operation == "<"){
				outputs.push_back("null");
				outputs.push_back(output);
				outputs.push_back("null");
			}
		}
	public:
		//comp #(.DATAWIDTH(8)) c0 (in1, in2, gt, lt, eq)
		comp(Netlist* netlist, std::string line){
			this->netlist = netlist;
			this->id = number;
			number++;
			if(line.find(">") != std::string::npos){
				this->calcIOs(">", line);
			} else if(line.find("==") != std::string::npos){
				this->calcIOs("==", line);
			} else if(line.find("<") != std::string::npos){
				this->calcIOs("<", line);
			}
		}

		std::string toString() override {
			std::string toReturn;
			bool sign = this->isSigned();
			//[S]COMP #(.DATAWIDTH(<width>)) c# (a, b, gt, lt, eq);\n
			size_t len = 36
				+ this->componentName
		}
};

#endif
