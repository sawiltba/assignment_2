#include "Netlist.h"
#include "components/Component.h"
#include "components/Adder.h"
#include "components/Comparator.h"
#include "components/Component.h"
#include "components/Multiplexor.h"
#include "components/Multiplier.h"
#include "components/Register.h"
#include "components/ShiftLeft.h"
#include "components/ShiftRight.h"
#include "components/Subtractor.h"

Netlist::Netlist(){

}

int Netlist::addRegister(std::string line){
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
	tokens.push_back(line.substr(begin, end));

	if(tokens.size() < 3){
		//ERROR
		return 1;
	}

	//tokens is {"register", "[U]Int#", "name1", ...}
	bool sign = tokens[1][0] == 'I'; //If signed, sign is true
	size_t numLoc = tokens[1].find("t") + 1;
	int width = std::stoi(tokens[1].substr(numLoc,
				std::string::npos));

	std::vector<Variable> newVars;
	std::vector<Component> newRegs;
	for(unsigned i = 2; i < tokens.size(); i++){
		newVars.push_back(Variable{tokens[i] + "_in",
				"wire", width, sign});
		newVars.push_back(Variable{tokens[i] + "_out",
				"wire", width, sign});
		newRegs.push_back(
				reg(this, tokens[0] + " " + tokens[1] + " " + tokens[i]));
	}

	wires.insert(wires.end(), newVars.begin(), newVars.end());
	operations.insert(operations.end(), newRegs.begin(), newRegs.end());
	return 0;

}

int Netlist::addVariable(std::string line){
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
	tokens.push_back(line.substr(begin, end));

	if(tokens.size() < 3){
		//ERROR
		return 1;
	}

	//tokens is {"<input/output/wire>", "[U]Int#", "name1", ...}
	bool sign = tokens[1][0] == 'I'; //If signed, sign is true
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
		return 1;
	}
	return 0;
}


int Netlist::addComponent(std::string line){
	if(line.find("register") != std::string::npos){
		return this->addRegister(line);
	} else if(line.find("<<") != std::string::npos){
		operations.push_back(shl (this, line));
	} else if(line.find(">>") != std::string::npos){
		operations.push_back(shr(this, line));
	} else if(line.find("<") != std::string::npos ||
			line.find(">") != std::string::npos ||
			line.find("==") != std::string::npos){
		operations.push_back(comp(this, line));
	} else if(line.find("+") != std::string::npos){
		operations.push_back(add(this, line));
	} else if(line.find("-") != std::string::npos){
		operations.push_back(sub (this, line));
	} else if(line.find("*") != std::string::npos){
		operations.push_back(mult (this, line));
	} else if(line.find("?") != std::string::npos){
		operations.push_back(mux(this, line));
	} else {
		return 1; //ERROR
	}
	return 0;
}
