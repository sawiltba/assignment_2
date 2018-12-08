#ifndef __COMPONENT_H
#define __COMPONENT_H
//#include "../Netlist.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <algorithm>

class State;
class Netlist;

class Component{
	protected:
		int id, width = -1, startTime = -1, endTime = -1, latency = 1;
		std::vector<std::shared_ptr<Component>> younglings;
		std::vector<std::shared_ptr<Component>> masters;
		Netlist *netlist;
        bool scheduled = false;
        std::string idName;
        std::string componentName;
		std::vector<std::string> inputs;
		std::vector<std::string> outputs;
		std::vector<bool> branch;

        virtual void calcIOs(std::string operation, std::string line){
			size_t begin = 0, end = 0;
			while(line[begin] == '\t'){
				begin++;
			}
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
        }

        virtual void checkConnections(std::string line); /*{
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
        }*/

        virtual void checkWidths();/*{
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
        }*/

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
		int cmpID;
		static int componentNumber;
		virtual std::string toString() = 0;

        virtual bool missingMaster(){
            return this->getUnlinkedInput() != "";
        }

        virtual std::string getUnlinkedInput(){
            for(std::string input : inputs){
                bool found = false;
                for(auto master : masters){
					std::vector<std::string> outputs = master->getOutputs();
                    if(std::find(outputs.begin(), outputs.end(), input) != outputs.end()){
                        found = true;
                        break;
                    }
                }
                if(!found){
                    return input;
                }
            }
            return "";
        }

		virtual int calcTimeFrame(int maxLatency){
			if(younglings.size() == 0){
				startTime = maxLatency - latency + 1;
				endTime = maxLatency;
				return startTime;
			}
			if(startTime != -1){
				return startTime;
			}
			int earliestYoungStart = maxLatency;
			for(auto itr = younglings.begin(); itr != younglings.end(); itr++){
				int currStart = (*itr)->calcTimeFrame(maxLatency);
				if(currStart < earliestYoungStart){
					earliestYoungStart = currStart;
				}
			}
			startTime = earliestYoungStart - latency;
			endTime = earliestYoungStart - 1;
			return startTime;
		}

		virtual int getStartTime(){
			return startTime;
		}

		virtual int getEndTime(){
			return endTime;
		}

		virtual int getLatency(){
			return latency;
		}

        virtual bool canSchedule(){
            for(auto m : masters){
                if(!m->isScheduled()){
                    return false;
                }
            }
            return true;
        }

        virtual void schedule(int cycle){
            startTime = cycle;
            endTime = cycle + latency - 1;
            scheduled = true;
        }

        virtual bool isScheduled(){
            return scheduled;
        }

		virtual void addYoungling(std::shared_ptr<Component> youngling){
			younglings.push_back(youngling);
		}

		virtual void addMaster(std::shared_ptr<Component> master){
			/*for(auto itr = masters.rbegin(); itr != masters.rend(); itr++){
				if(*itr == master){
					return;
				}
			}*/
			masters.push_back(master);
			master->addYoungling(std::shared_ptr<Component>{this});
		}

		virtual std::vector<std::shared_ptr<Component>> getMasters(){
			return masters;
		}

		virtual std::vector<std::shared_ptr<Component>> getYounglings(){
			return younglings;
		}

        virtual std::string getID(){
            return idName + std::to_string(id);
        }

		virtual void checkRegisters();/*{
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
		}*/

		virtual bool foundRegister(){
			return false;
		}

        std::string getComponentName(){
            return componentName;
        }

		std::vector<bool> getBranch(){
			return branch;
		}

		bool branchMatch(std::vector<bool> otherBranch){
			if(otherBranch.size() != branch.size()){
				return false;
			}
			for(unsigned i = 0; i < branch.size(); i++){
				if(branch[i] != otherBranch[i]){
					return false;
				}
			}
			return true;
		}

		bool branchMatchUpToEnd(std::vector<bool> otherBranch){
			for(unsigned i = 0; i < branch.size() && i < otherBranch.size(); i++){
				if(branch[i] != otherBranch[i]){
					return false;
				}
			}
			return true;
		}
		
		virtual void addNextState(State& next) {

		}

		virtual void addBranch(bool a){
			branch.insert(branch.begin(), a);
		}

		virtual int getWidth();/* {
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
		}*/

		virtual bool isSigned();/*{
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
		}*/

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

//int Component::componentNumber = 1;
#endif
