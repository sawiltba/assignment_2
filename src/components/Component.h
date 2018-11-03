#ifndef __COMPONENT_H
#define __COMPONENT_H
#include <vector>
#include <string>
#include "../Netlist.h"

//class Netlist;

class Component{
	protected:
		int id;
		Netlist *netlist;
        std::string idName;
        std::string componentName;
		std::vector<std::string> inputs;
		std::vector<std::string> outputs;

        virtual void calcIOs(std::string operation, std::string line){
			size_t begin = 0, end = 0;
			end = line.find("=");
			outputs.push_back(line.substr(begin, end - 1));
			begin = end + 2;
			end = line.find(operation);
			inputs.push_back(line.substr(begin, end - begin - 1));
			begin = end + operation.length() + 1;
			end = line.length();
			inputs.push_back(line.substr(begin, end - begin));
        }

		size_t IOStrLen(){
			size_t len = 0;
			for(std::string input : inputs){
				len += input.length();
			}
			for(std::string output : outputs){
				len += output.length();
			}
			return len;
		}
	public:
		virtual std::string toString(){
			std::string toReturn;
            bool sign = this->isSigned();
			//[S]<cName> #(.DATAWIDTH(<width>)) <id> (a, b, sum);\n
			size_t len = 26
                + this->componentName.length() 
				+ this->IOStrLen()
				+ this->getID().length()
				+ std::to_string(this->getWidth()).length();
			toReturn.resize(len);
			char* str = (char*)malloc(len + 1);
			sprintf(str, "%s #(.DATAWIDTH(%d)) %s (%s, %s, %s);\n",
                    this->componentName.c_str(), this->getWidth(), 
                    this->getID().c_str(), inputs[0].c_str(), inputs[1].c_str(),
					outputs[0].c_str());
			toReturn.assign(str);
			free(str);
			return (sign ? "S" : "") + toReturn;
        }
		
        virtual std::string getID(){
            return idName + std::to_string(id);
        }

		void checkRegisters(){
			std::vector<Component> regs = this->netlist->getComponents();
			for(Component reg : regs){
				if(reg.componentName.find("REG") == std::string::npos){
					return;
				}
				for(int i = 0; i < inputs.length(); i++){
					if(inputs[i] == reg.idName){
						inputs[i] = reg.outputs[0];
					}
				}
				for(int i = 0; i < outputs.length(); i++){
					if(outputs[i] == reg.idName){
						outputs[i] = reg.inputs[2];
					}
				}
			}
		}

		int getWidth(){
			int toReturn = 0;
			for(std::string input : inputs){
				for(Variable v : this->netlist->getInputs()){
					if(input == v.getName() && v.getWidth() > toReturn){
						toReturn = v.getWidth();
					}
				}
				for(Variable v : this->netlist->getWires()){
					if(input == v.getName() && v.getWidth() > toReturn){
						toReturn = v.getWidth();
					}
				}
			}
			for(std::string output : outputs){
				for(Variable v : this->netlist->getOutputs()){
					if(output == v.getName() && v.getWidth() > toReturn){
						toReturn = v.getWidth();
					}
				}
				for(Variable v : this->netlist->getWires()){
					if(output == v.getName() && v.getWidth() > toReturn){
						toReturn = v.getWidth();
					}
				}
			}
			return toReturn;
		}
		virtual bool isSigned(){
			for(std::string output : outputs){
				for(Variable outputVar : this->netlist->getOutputs()){
					if(output == outputVar.getName() && outputVar.isSigned()){
						return true;
					}
				}
				for(Variable wireVar : this->netlist->getWires()){
					if(output == wireVar.getName() && wireVar.isSigned()){
						return true;
					}
				}
			}
			return false;
		}
};

#endif
