#ifndef __COMPONENT_H
#define __COMPONENT_H
#include <vector>
#include <string>
#include "../Netlist.h"
//class Netlist;

class Component{
	protected:
		Netlist *netlist;
		int id;
		std::vector<std::string> inputs;
		std::vector<std::string> outputs;
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
		virtual std::string getID() = 0;
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
