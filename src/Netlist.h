#ifndef __NETLIST_H
#define __NETLIST_H
#include <vector>
#include <string>
#include "Variable.h"

class Component;

class Netlist{
	private:
		std::vector<Variable> inputs, outputs, wires;
		std::vector<Component> operations;
	public:
		Netlist();
		void addVariable(std::string line);
		void addComponent(std::string line);
		std::vector<Variable> getInputs(){
			return inputs;	
		}
		std::vector<Variable> getOutputs(){
			return outputs;	
		}
		std::vector<Variable> getWires(){
			return wires;	
		}
};

#endif
