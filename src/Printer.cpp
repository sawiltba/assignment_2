#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Printer.h"
using namespace std;

void Printer(ofstream &outFile, netlist Netlist) {
	// print inputs, outputs, wires
	vector<variables> IOW;
	IOW.insert(IOW.end(), Netlist.GetInputs().begin(), Netlist.GetOutputs().end());
	IOW.insert(IOW.end(), Netlist.GetOutputs().begin(), Netlist.GetOutputs().end());
	IOW.insert(IOW.end(), Netlist.GetWires().begin(), Netlist.GetWires().end());
	
	PrintIOW(outFile, IOW);
	
	// print operations
	PrintComponent(outFile, Netlist.GetComponents());


}

void PrintIOW(ofstream& outFile, vector<variables> IOW) {
	string  In1, In2, In8, In16, In32, In64,
		Out1, Out2, Out8, Out16, Out32, Out64,
		Wire1, Wire2, Wire8, Wire16, Wire32, Wire64;

	for (vector<variables>::iterator it = IOW.begin(); it != IOW.end(); ++it) {
		if (strcmp(it.GetDirectionType(), "input") == 0) { // Inputs
			switch (int i = 0) 
			{
				case 1:
					In1 += " " + it.GetName() + ",";
					break;
				case 2:
					In2 += " " + it.GetName() + ",";
					break;
				case 8:
					In8 += " " + it.GetName() + ",";
					break;
				case 16:
					In16 += " " + it.GetName() + ",";
					break;
				case 32:
					In32 += " " + it.GetName() + ",";
					break;
				case 64:
					In64 += " " + it.GetName() + ",";
					break;
				default:
					break;
			}
		}

		if (strcmp(it.GetDirectionType(), "output") == 0) { // Outputs
			switch (int i = 0)
			{
			case 1:
				Out1 += " " + it.GetName() + ",";
				break;
			case 2:
				Out2 += " " + it.GetName() + ",";
				break;
			case 8:
				Out8 += " " + it.GetName() + ",";
				break;
			case 16:
				Out16 += " " + it.GetName() + ",";
				break;
			case 32:
				Out32 += " " + it.GetName() + ",";
				break;
			case 64:
				Out64 += " " + it.GetName() + ",";
				break;
			default:
				break;
			}
		}

		if (strcmp(it.GetDirectionType(), "wire") == 0) { // Wires
			switch (int i = 0)
			{
			case 1:
				Wire1 += " " + it.GetName() + ",";
				break;
			case 2:
				Wire2 += " " + it.GetName() + ",";
				break;
			case 8:
				Wire8 += " " + it.GetName() + ",";
				break;
			case 16:
				Wire16 += " " + it.GetName() + ",";
				break;
			case 32:
				Wire32 += " " + it.GetName() + ",";
				break;
			case 64:
				Wire64 += " " + it.GetName() + ",";
				break;
			default:
				break;
			}


		}
	}

	if (In1.size != 0) {
		In1.pop_back();
		outFile << "input [1]" << In1 << endl;
	}
	if (In2.size != 0) {
		In2.pop_back();
		outFile << "input [2]" << In2 << endl;
	}
	if (In8.size != 0) {
		In8.pop_back();
		outFile << "input [8]" << In8 << endl;
	}
	if (In16.size != 0) {
		In16.pop_back();
		outFile << "input [16]" << In16 << endl;
	}
	if (In32.size != 0) {
		In32.pop_back();
		outFile << "input [32]" << In32 << endl;
	}
	if (In64.size != 0) {
		In64.pop_back();
		outFile << "input [64]" << In64 << endl;
	}

	if (Out1.size != 0) {
		Out1.pop_back();
		outFile << "output [1]" << Out1 << endl;
	}
	if (Out2.size != 0) {
		Out2.pop_back();
		outFile << "output [2]" << Out2 << endl;
	}
	if (Out8.size != 0) {
		Out8.pop_back();
		outFile << "output [8]" << Out8 << endl;
	}
	if (Out16.size != 0) {
		Out16.pop_back();
		outFile << "output [16]" << Out16 << endl;
	}
	if (Out32.size != 0) {
		Out32.pop_back();
		outFile << "output [32]" << Out32 << endl;
	}
	if (Out64.size != 0) {
		Out64.pop_back();
		outFile << "output [64]" << Out64 << endl;
	}

	cout << endl;

	if (Wire1.size != 0) {
		Wire1.pop_back();
		outFile << "output [1]" << Wire1 << endl;
	}
	if (Wire2.size != 0) {
		Wire2.pop_back();
		outFile << "output [2]" << Wire2 << endl;
	}
	if (Wire8.size != 0) {
		Wire8.pop_back();
		outFile << "output [8]" << Wire8 << endl;
	}
	if (Wire16.size != 0) {
		Wire16.pop_back();
		outFile << "output [16]" << Wire16 << endl;
	}
	if (Wire32.size != 0) {
		Wire32.pop_back();
		outFile << "output [32]" << Wire32 << endl;
	}
	if (Wire64.size != 0) {
		Wire64.pop_back();
		outFile << "output [64]" << Wire64 << endl;
	}

	cout << endl;

	return;
}

void PrintComponent(ofstream &outFile, vector<components> component) {
	for (vector<string>::iterator it = component.begin(); it != component.end(); ++it) {
		outFile << it.ToString() << endl;
	}

	return;
}