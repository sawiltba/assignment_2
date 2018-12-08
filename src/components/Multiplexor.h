#ifndef __MUX_H
#define __MUX_H
#include "Component.h"

class mux: public Component {
	private:
		static int number;

	public:
		mux(Netlist* netlist, std::string line){
			this->netlist = netlist;
			this->idName = "mux";
			this->componentName = "MUX2x1";
			size_t begin = 0, end = 0;
			id = number;
			number++;
			cmpID = componentNumber;
			componentNumber++;
			end = line.find("=");
			outputs.push_back(line.substr(begin, end - 1));
			begin = end + 2;
			end = line.find("?");
			inputs.push_back(line.substr(begin, end - begin - 1));
			begin = end + 2;
			end = line.find(":");
			inputs.push_back(line.substr(begin, end - begin - 1));
			begin = end + 2;
			end = line.find(" ", begin);
			inputs.push_back(line.substr(begin, end - begin));
		}

		int getNumber(){
			return number;
		}

		std::string toString() override{
		//	std::string toReturn;
		//	//MUX2x1 #(.DATAWIDTH(<width>)) <id> (a, b, sel, sum);\n
		//	size_t len = 34 
		//		+ this->IOStrLen()
		//		+ this->getID().length()
		//		+ std::to_string(this->getWidth()).length();
		//	toReturn.resize(len);
		//	char* str = (char*)malloc(len + 1);
		//	sprintf(str, "MUX2x1 #(.DATAWIDTH(%d)) %s (%s, %s, %s, %s);\n",
		//			this->getWidth(), this->getID().c_str(), 
		//			inputs[1].c_str(), inputs[2].c_str(), inputs[0].c_str(),
		//			outputs[0].c_str());
		//	toReturn.assign(str);
		//	free(str);
		//	return toReturn;
		//}

		//std::string printString() {
			std::string toPrint;
			std::vector<std::string> outputs = this->getOutputs();
			std::vector<std::string> inputs = this->getInputs();
			toPrint = outputs.at(0) + " = " + inputs.at(0) + " ? " + inputs.at(1) + " : " + inputs.at(2);
			return(toPrint);
		};
};

int mux::number = 0;

#endif
