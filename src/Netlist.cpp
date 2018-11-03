#include "Netlist.h"

Netlist::Netlist(){

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


int Netlist::addComponent(Netlist* netlist, std::string line){
    std::vector<std::string> tokens;

    //Split string on spaces into tokens
	size_t begin = 0, end = line.find(" "), len = end - begin;
	while(end != std::string::npos){
		tokens.push_back(line.substr(begin, len));
		begin = end + 1;
		end = line.find(" ", begin);
		len = end - begin;
	}
	tokens.push_back(line.substr(begin, end));

	if(tokens.size() < 3){//error
        return 1;
	}
	else if(tokens.size() == 3){//equals operator (register)
        reg(this, line);
	}
	else if(tokens.size() < 6){//2 in, 1 out operation
        if(!tokens.at(3).compare("+")){//add
            add(this, line);
        }
        else if(!tokens.at(3).compare("-")){//subtract
            sub(this, line);
        }
        else if(!tokens.at(3).compare("*")){//multiply
            sub(this, line);
        }
        else if(!tokens.at(3).compare("==")){//comp equal to
            comp(this, line);
        }
        else if(!tokens.at(3).compare(">")){//comp greater than
            comp(this, line);
        }
        else if(!tokens.at(3).compare("<")){//comp less than
            comp(this, line);
        }
        else if(!tokens.at(3).compare("<<")){//shift left
            shl(this, line);
        }
        else if(!tokens.at(3).compare(">>")){//shift right
            shr(this, line);
        }
        else{//error
            return 1;
        }
	}
	else if(tokens.size() == 7){//multiplexor
        mux(this, line);
	}
	else{//error
        return 1;
	}
	return 0;
}
