#ifndef __NETLIST_H
#define __NETLIST_H
#include <vector>
#include <string>
#include "Variable.h"
#include "components/Component.h"

#include "components/Adder.h"
#include "components/Subtractor.h"
#include "components/Multiplier.h"
#include "components/Multiplexor.h"
#include "components/Register.h"
#include "components/Comparator.h"
#include "components/ShiftRight.h"
#include "components/ShiftLeft.h"

class Netlist{
	private:
		std::vector<Variable> inputs, outputs, wires;
		std::vector<Component> operations;
	public:
		Netlist(){};
		void addVariable(std::string line){
			std::vector<std::string> tokens;
			//Get rid of commas
			while(line.find(",") != std::string::npos){
				line.erase(line.find(","), 1);
			}

			//Split string on spaces into tokens
			size_t begin = 0, end = line.find(" "), len = end - begin;
			while(end != std::string::npos){
				tokens.push_back(line.substr(begin, len));
				begin = end + 1;
				end = line.find(" ", begin);
				len = end - begin;
			}
			tokens.push_back(begin, end);

			if(tokens.size() < 3){
				//ERROR
			}

			//tokens is {"<input/output/wire>", "[U]Int#", "name1", ...}
			bool sign = tokens[1][0] == "I"; //If signed, sign is true
			size_t numLoc = tokens[1].find("t") + 1;
			int width = std::stoi(tokens[1].substr(numLoc, 
											  std::string::npos));

			std::vector<Variable> newVars;
			for(unsigned i = 2; i < tokens.size(); i++){
				newVars.push_back(Variable{tokens[i], 
						tokens[0], width, sign});
			}

			if(tokens[0] == "input"){
				inputs.insert(inputs.end(), newVars.begin(), newVars.end());
			} else if(tokens[0] == "wire"){
				wires.insert(wires.end(), newVars.begin(), newVars.end());
			} else if(tokens[0] == "output"){
				outputs.insert(outputs.end(), newVars.begin(), newVars.end());
			} else {
				//ERROR
				//Throw some error
			}
		}
		void addComponent(std::string line);
		std::vector<Variable> getInputs();
		std::vector<Variable> getOutputs();
		std::vector<Variable> getWires();
};

#endif
