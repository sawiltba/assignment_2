#ifndef __COMPONENT_H
#define __COMPONENT_H
#include <vector>
#include <string>

class Netlist;

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
				for(Variable v : netlist->getInputs()){
					if(input == v.getName() && v.width() > toReturn){
						toReturn = v.width();
					}
				}
				for(Variable v : netlist->getWires()){
					if(input == v.getName() && v.width() > toReturn){
						toReturn = v.width();
					}
				}
			}
			for(std::string output : outputs){
				for(Variable v : netlist->getOutputs()){
					if(output == v.getName() && v.width() > toReturn){
						toReturn = v.width();
					}
				}
				for(Variable v : netlist->getWires()){
					if(output == v.getName() && v.width() > toReturn){
						toReturn = v.width();
					}
				}
			}
			return toReturn;
		}
		virtual bool isSigned(){
			for(std::string output : outputs){
				for(Variable outputVar : netlist->getOutputs()){
					if(output == outputVar.getName() && outputVar.isSigned()){
						return true;
					}
				}
				for(Variable wireVar : netList->getWires()){
					if(output == wireVar.getName() && wireVar.isSigned()){
						return true;
					}
				}
			}
			return false;
		}
};

#endif
