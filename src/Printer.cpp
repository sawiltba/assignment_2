#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Printer.h"
#include "Variable.h"
#include "components/Component.h"
using namespace std;

void Printer(ofstream &outFile, Netlist Netlist) {
	// print inputs, outputs, wires
	vector<Variable> IOW;
	IOW.insert(IOW.end(), Netlist.getInputs().begin(), Netlist.getOutputs().end());
	IOW.insert(IOW.end(), Netlist.getOutputs().begin(), Netlist.getOutputs().end());
	IOW.insert(IOW.end(), Netlist.getWires().begin(), Netlist.getWires().end());

	PrintIOW(outFile, IOW);

	// print operations
	PrintComponent(outFile, Netlist.getComponents());

	return;
}

void PrintIOW(ofstream& outFile, vector<Variable> IOW) {
	string  In1, In2, In8, In16, In32, In64,
		Out1, Out2, Out8, Out16, Out32, Out64,
		Wire1, Wire2, Wire8, Wire16, Wire32, Wire64;

	for (vector<Variable>::iterator it = IOW.begin(); it != IOW.end(); ++it) {
		if (it->getType().compare("input") == 0) { // Inputs
			switch (int i = it->getWidth())
			{
				case 1:
					In1 += " " + it->getName() + ",";
					break;
				case 2:
					In2 += " " + it->getName() + ",";
					break;
				case 8:
					In8 += " " + it->getName() + ",";
					break;
				case 16:
					In16 += " " + it->getName() + ",";
					break;
				case 32:
					In32 += " " + it->getName() + ",";
					break;
				case 64:
					In64 += " " + it->getName() + ",";
					break;
				default:
					break;
			}
		}

		if (it->getType().compare("output") == 0) { // Outputs
			switch (int i = it->getWidth())
			{
			case 1:
				Out1 += " " + it->getName() + ",";
				break;
			case 2:
				Out2 += " " + it->getName() + ",";
				break;
			case 8:
				Out8 += " " + it->getName() + ",";
				break;
			case 16:
				Out16 += " " + it->getName() + ",";
				break;
			case 32:
				Out32 += " " + it->getName() + ",";
				break;
			case 64:
				Out64 += " " + it->getName() + ",";
				break;
			default:
				break;
			}
		}

		if (it->getType().compare("wire") == 0) { // Wires
			switch (int i = it->getWidth())
			{
			case 1:
				Wire1 += " " + it->getName() + ",";
				break;
			case 2:
				Wire2 += " " + it->getName() + ",";
				break;
			case 8:
				Wire8 += " " + it->getName() + ",";
				break;
			case 16:
				Wire16 += " " + it->getName() + ",";
				break;
			case 32:
				Wire32 += " " + it->getName() + ",";
				break;
			case 64:
				Wire64 += " " + it->getName() + ",";
				break;
			default:
				break;
			}


		}
	}

	if (In1.size() != 0) {
		In1.pop_back();
		outFile << "input " << In1 << endl;
	}
	if (In2.size() != 0) {
		In2.pop_back();
		outFile << "input [1:0]" << In2 << endl;
	}
	if (In8.size() != 0) {
		In8.pop_back();
		outFile << "input [7:0]" << In8 << endl;
	}
	if (In16.size() != 0) {
		In16.pop_back();
		outFile << "input [15:0]" << In16 << endl;
	}
	if (In32.size() != 0) {
		In32.pop_back();
		outFile << "input [31:0]" << In32 << endl;
	}
	if (In64.size() != 0) {
		In64.pop_back();
		outFile << "input [63:0]" << In64 << endl;
	}

	if (Out1.size() != 0) {
		Out1.pop_back();
		outFile << "output reg" << Out1 << endl;
	}
	if (Out2.size() != 0) {
		Out2.pop_back();
		outFile << "output reg [1:0]" << Out2 << endl;
	}
	if (Out8.size() != 0) {
		Out8.pop_back();
		outFile << "output reg [7:0]" << Out8 << endl;
	}
	if (Out16.size() != 0) {
		Out16.pop_back();
		outFile << "output [15:0]" << Out16 << endl;
	}
	if (Out32.size() != 0) {
		Out32.pop_back();
		outFile << "output [31:0]" << Out32 << endl;
	}
	if (Out64.size() != 0) {
		Out64.pop_back();
		outFile << "output [63:0]" << Out64 << endl;
	}

	cout << endl;

	if (Wire1.size() != 0) {
		Wire1.pop_back();
		outFile << "wire " << Wire1 << endl;
	}
	if (Wire2.size() != 0) {
		Wire2.pop_back();
		outFile << "wire [1:0]" << Wire2 << endl;
	}
	if (Wire8.size() != 0) {
		Wire8.pop_back();
		outFile << "wire [7:0]" << Wire8 << endl;
	}
	if (Wire16.size() != 0) {
		Wire16.pop_back();
		outFile << "wire [15:0]" << Wire16 << endl;
	}
	if (Wire32.size() != 0) {
		Wire32.pop_back();
		outFile << "wire [31:0]" << Wire32 << endl;
	}
	if (Wire64.size() != 0) {
		Wire64.pop_back();
		outFile << "wire [63:0]" << Wire64 << endl;
	}

	cout << endl;

	return;
}

void PrintComponent(ofstream &outFile, vector<Component> component) {
	for (vector<Component>::iterator it = component.begin(); it != component.end(); ++it) {
		outFile << it->toString() << endl;
	}

	return();

}

