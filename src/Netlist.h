#ifndef __NETLIST_H
#define __NETLIST_H
#include <vector>
#include <string>
#include "Variable.h"
#include "components/Component.h"

#include "components/Adder.h"
#include "components/Subtractor.h"
#include "components/Multiplier.h"
#include "components/Multiplexor.h"
#include "components/Register.h"
#include "components/Comparator.h"
#include "components/ShiftRight.h"
#include "components/ShiftLeft.h"

class Netlist{
	private:
		std::vector<Variable> inputs, outputs, wires;
		std::vector<Component> operations;
	public:
		Netlist(){};
		void addVariable(std::string line);
		void addComponent(std::string line);
		std::vector<Variable> getInputs();
		std::vector<Variable> getOutputs();
		std::vector<Variable> getWires();
}

#endif
