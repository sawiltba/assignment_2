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
        std::string token = line.substr(begin, len);
        while(token.find(" ") != std::string::npos){
            token.erase(token.find(" "), 1);
        }
        if(token.size() > 0){
            tokens.push_back(token);
        }
        begin = end + 1;
        end = line.find(" ", begin);
        len = end - begin;
    }
    std::string token = line.substr(begin, end);
    while(token.find(" ") != std::string::npos){
        token.erase(token.find(" "), 1);
    }
    if(token.size() > 0){
        tokens.push_back(token);
    }

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
    std::vector<std::shared_ptr<Component>> newRegs;
    for(unsigned i = 2; i < tokens.size(); i++){
        newVars.push_back(Variable{tokens[i] + "_in",
                "wire", width, sign});
        newVars.push_back(Variable{tokens[i] + "_out",
                "wire", width, sign});
        std::shared_ptr<reg> a = std::shared_ptr<reg>{
            new reg{this, tokens[0] + " " + tokens[1] + " " + tokens[i]}
        };
        newRegs.push_back(a);
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
        std::string token = line.substr(begin, len);
        while(token.find(" ") != std::string::npos){
            token.erase(token.find(" "), 1);
        }
        if(token.size() > 0){
            tokens.push_back(token);
        }
        begin = end + 1;
        end = line.find(" ", begin);
        len = end - begin;
    }
    std::string token = line.substr(begin, end);
    while(token.find(" ") != std::string::npos){
        token.erase(token.find(" "), 1);
    }
    if(token.size() > 0){
        tokens.push_back(token);
    }

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
        std::shared_ptr<shl> a = std::shared_ptr<shl>{new shl{this, line}};
        operations.push_back(a);
    } else if(line.find(">>") != std::string::npos){
        std::shared_ptr<shr> a = std::shared_ptr<shr>{new shr{this, line}};
        operations.push_back(a);
    } else if(line.find("<") != std::string::npos ||
            line.find(">") != std::string::npos ||
            line.find("==") != std::string::npos){
        std::shared_ptr<comp> a = std::shared_ptr<comp>{new comp{this, line}};
        operations.push_back(a);
    } else if(line.find("+") != std::string::npos){
        std::shared_ptr<add> a = std::shared_ptr<add>{new add{this, line}};
        operations.push_back(a);
    } else if(line.find("-") != std::string::npos){
        std::shared_ptr<sub> a = std::shared_ptr<sub>{new sub{this, line}};
        operations.push_back(a);
    } else if(line.find("*") != std::string::npos){
        std::shared_ptr<mult> a = std::shared_ptr<mult>{new mult{this, line}};
        operations.push_back(a);
    } else if(line.find("?") != std::string::npos){
        std::shared_ptr<mux> a = std::shared_ptr<mux>{new mux{this, line}};
        operations.push_back(a);
    } else if(line.find("=") != std::string::npos){
        std::shared_ptr<reg> a = std::shared_ptr<reg>{new reg{this, line, 1}};
        if(!a->foundRegister()){
            operations.push_back(a);
        }
    } else {
        return 1; //ERROR
    }
    return 0;
}
