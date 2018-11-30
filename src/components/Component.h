#ifndef __COMPONENT_H
#define __COMPONENT_H
#include <vector>
#include <string>
#include <stdexcept>
#include "../Netlist.h"

//class Netlist;

class Component{
	protected:
		int id, width = -1, startTime, endTime, latency;
		std::vector<Component> younglings;
		std::vector<Component> masters;
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
            if(line.find(" ", begin) < end){
                end = line.find(" ", begin);
            }
			inputs.push_back(line.substr(begin, end - begin));
            this->checkRegisters();
            this->checkConnections(line);
            this->checkWidths();
        }

        virtual void checkConnections(std::string line){
            size_t len = inputs.size() + outputs.size();
            std::vector<bool> connections;
            connections.resize(len, false);
            for(unsigned i = 0; i < inputs.size(); i++){
                for(Variable &v : netlist->getInputs()){
                    if(v.getName() == inputs[i]){
                        connections[i] = true;
                        v.setUsed();
                    }
                }
                for(Variable &v : netlist->getWires()){
                    if(v.getName() == inputs[i]){
                        connections[i] = true;
                        v.setUsed();
                    }
                }
            }
            for(unsigned i = 0; i < outputs.size(); i++){
                for(Variable &v : netlist->getOutputs()){
                    if(v.getName() == outputs[i]){
                        connections[i + inputs.size()] = true;
                        v.setUsed();
                    }
                }
                for(Variable &v : netlist->getWires()){
                    if(v.getName() == outputs[i]){
                        connections[i + inputs.size()] = true;
                        v.setUsed();
                    }
                }
            }
            for(unsigned i = 0; i < connections.size(); i++){
                if(!connections[i]){
                    throw std::length_error{"Missing connection! At line: " + line};
                }
            }
        }

        virtual void checkWidths(){
            bool sign = this->isSigned();
            this->getWidth();
			for(unsigned i = 0; i < inputs.size(); i++){
				for(Variable v : this->netlist->getInputs()){
					if(inputs[i] == v.getName() && v.getWidth() < this->width && !v.isSigned() && sign){
						inputs[i] = "$signed({1'b0, " + inputs[i] + "})";
					} else if(inputs[i] == v.getName() && v.getWidth() > this->width){
                        char width[16] = "";
                        sprintf(width, "[%d:0]", this->width - 1);
                        inputs[i] = inputs[i] + std::string{width};
                    }
				}
				for(Variable v : this->netlist->getWires()){
					if(inputs[i] == v.getName() && v.getWidth() < this->width && !v.isSigned() && sign){
						inputs[i] = "$signed({1'b0, " + inputs[i] + "})";
					} else if(inputs[i] == v.getName() && v.getWidth() > this->width){
                        char width[16] = "";
                        sprintf(width, "[%d:0]", this->width - 1);
                        inputs[i] = inputs[i] + std::string{width};
                    }
				}
			}
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
		virtual std::string toString() = 0;
		
        virtual std::string getID(){
            return idName + std::to_string(id);
        }

		virtual void checkRegisters(){
			std::vector<std::shared_ptr<Component>> regs = this->netlist->getComponents();
			for(std::shared_ptr<Component> reg : regs){
				if(reg->componentName.find("REG") == std::string::npos){
					return;
				}
				for(int i = 0; i < inputs.size(); i++){
					if(inputs[i] == reg->idName){
						inputs[i] = reg->outputs[0];
					}
				}
				for(int i = 0; i < outputs.size(); i++){
					if(outputs[i] == reg->idName){
						outputs[i] = reg->inputs[2];
					}
				}
			}
		}

        std::string getComponentName(){
            return componentName;
        }

		virtual int getWidth() {
            if(this->width != -1){
                return this->width;
            }
			int toReturn = 0;
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
            this->width = toReturn;
            if(this->width <= 0){
                throw std::length_error("Width of component must be greater than zero!");
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

        std::vector<std::string> getInputs(){
            return this->inputs;
        }
        std::vector<std::string> getOutputs(){
            return this->outputs;
        }
        void setInput(int index, std::string value){
            this->inputs[index] = value;
        }
        void setOutput(int index, std::string value){
            this->outputs[index] = value;
        }
};

#endif
