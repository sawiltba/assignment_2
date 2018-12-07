#ifndef __NETLIST_H
#define __NETLIST_H

#include "Variable.h"
#include "Cycle.h"

#include <vector>
#include <string>
#include <memory>

class Component;

class Netlist{
	private:
		std::vector<Variable> inputs, outputs, wires;
		std::vector<std::shared_ptr<Component>> operations;
	public:
		Netlist();
		int addVariable(std::string line);
		int addComponent(std::string line);
        void insertComponents(std::vector<std::shared_ptr<Component>> toInsert);
        void pushComponent(std::shared_ptr<Component> toAdd);
		int addRegister(std::string line);
		void findDependencies(std::shared_ptr<Component> cmpt);
        std::vector<std::string> tokenize(std::string line);
		std::vector<Variable>& getInputs(){
			return inputs;
		}
		std::vector<Variable>& getOutputs(){
			return outputs;
		}
		std::vector<Variable>& getWires(){
			return wires;
		}
		std::vector<std::shared_ptr<Component>>& getComponents() {
			return operations;
		}
		std::vector<Cycle> getCycles(int latency, int* error);
};

#endif
