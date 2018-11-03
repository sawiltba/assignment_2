#ifndef __NETLIST_H
#define __NETLIST_H

#include "Variable.h"
#include "components/Adder.h"
#include "components/Comparator.h"
#include "components/Component.h"
#include "components/Multiplexor.h"
#include "components/Multiplier.h"
#include "components/Register.h"
#include "components/ShiftLeft.h"
#include "components/ShiftRight.h"
#include "components/Subtractor.h"

#include <vector>
#include <string>

class Component;

class Netlist {
private:
	std::vector<Variable> inputs, outputs, wires;
	std::vector<Component> operations;
public:
	Netlist();
	void addVariable(std::string line);
	int addComponent(std::string line);
	std::vector<Variable> getInputs() {
		return inputs;
	}
	std::vector<Variable> getOutputs() {
		return outputs;
	}
	std::vector<Variable> getWires() {
		return wires;
	}
	std::vector<Component> getComponents() {
		return operations;
	}

};

#endif
