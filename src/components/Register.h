#ifndef __REG_H
#define __REG_H
#include "Component.h"

class reg: public Component {
	private:
		static int number;
        bool foundReg = false;
	public:
		reg(Netlist *netlist, std::string line, int a){
			this->netlist = netlist;
			std::vector<std::string> tokens;
			size_t begin = 0, end = line.find(" ");
			while(end != std::string::npos){
				tokens.push_back(line.substr(begin, end - begin));
				begin = end + 1;
				end = line.find(" ", begin);
			}
			tokens.push_back(line.substr(begin, end - begin));
			//Tokens is {output, =, input}

			
			this->inputs.push_back(tokens[2]);
			this->inputs.push_back("clk");
			this->inputs.push_back("rst");
			this->outputs.push_back(tokens[0]);
			this->componentName = "REG";
			this->id = number;
			this->idName = "reg" + std::to_string(number);
			number++;
            this->checkRegisters();
		}
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
			this->inputs.push_back(tokens[2] + "_in");
			this->inputs.push_back("clk");
			this->inputs.push_back("rst");
			this->outputs.push_back(tokens[2] + "_out");
			this->componentName = "REG";
			this->id = -1;
		}
        
        void checkRegisters() override {
			std::vector<std::shared_ptr<Component>> regs = this->netlist->getComponents();
			for(std::shared_ptr<Component> reg : regs){
				if(reg->getComponentName().find("REG") == std::string::npos || reg->getID() != this->outputs[0]){
					continue;
				}
                for(std::shared_ptr<Component> elem : regs){
                    for(unsigned i = 0; i < elem->getOutputs().size(); i++){
                        if(this->inputs[0] == elem->getOutputs()[i]){
                            elem->setOutput(i, reg->getInputs()[0]);
                            this->foundReg = true;
                            number -= 1;
                        }
                    }
                }
			}
        }

        bool foundRegister(){
            return this->foundReg;
        }

		std::string getID() override {
			return idName;
		}

		std::string toString() override {
			std::string toReturn;
			//REG #(.DATAWIDTH(<width>)) <id> (clk, rst, d, q);\n
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

int reg::number = 0;
#endif
