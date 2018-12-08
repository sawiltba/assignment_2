#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Printer.h"
#include "Variable.h"
#include "components/Component.h"
#include "State.h"
using namespace std;

void Printer(string filename, ofstream &outFile, Netlist netlist, vector<State> states ) {
    string base = getBaseName(filename);
    outFile << "`timescale 1ns / 1ps" << endl;
    outFile << "module " << "HLSM" << "(clk, rst, start, done, ";
    for(unsigned i = 0; i < netlist.getInputs().size(); i++){
        if(netlist.getInputs()[i].getName() != "clk" && netlist.getInputs()[i].getName() != "rst"){
            outFile << netlist.getInputs()[i].getName() << ", ";
        }
    }

    for(unsigned i = 0; i < netlist.getOutputs().size() - 1; i++){
        outFile << netlist.getOutputs()[i].getName() << ", ";
    }
    size_t last = netlist.getOutputs().size() - 1;
    outFile << netlist.getOutputs()[last].getName() << ");" << endl;

    outFile << "\tinput clk;" << endl;
    outFile << "\tinput rst;" << endl;
	outFile << "\tinput start" << endl << endl;

	outFile << "output reg done;" << endl;

	outFile << "reg [15:0] state, nextState;" << endl;

    // print inputs, outputs, wires
    for(Variable v : netlist.getInputs()){
        if(v.getName() != "clk" && v.getName() != "rst"){
            outFile << "\t" << v.toString();
        }
    }

    for(Variable v : netlist.getOutputs()){
        outFile << "\t" << v.toString();
    }

    for(Variable v : netlist.getWires()){
        if(v.isUsed()){
            outFile << "\t" << v.toString();
        }
    }
    
    outFile << "always @(posedge clk) begin" << endl;
	outFile << "\tif(rst == 1) begin" << endl;
	outFile << "\t\tstate <= 0;" << endl;
	outFile << "\tend" << endl;
	outFile << "\telse begin" << endl;
	outFile << "\t\tstate <= stateNext;" << endl; 
	outFile << "\tend" << endl;
    outFile << "end\n";
    
    outFile << "always@(state";
    
    for(Variable v : netlist.getInputs()){
        if(v.getName() != "clk" && v.getName() != "rst"){
            outFile << ", " << v.getName();
        }
    }
    
    outFile << ") begin" << endl;
    outFile << "case(state)" << endl;
    outFile << "\t32'd0: begin" << endl;
    outFile << "\t\tif(start) begin" << endl;
    outFile << "\t\t\tstateNext <= 1;" << endl;
    outFile << "\t\tend\n";
    outFile << "\tend\n";
    
    for(int i = 0; i < states.size(); i++){
		outFile << "\t32'd" << states.at(i).getStateNum() << ": begin" << endl;
		outFile << "\t\t";
		outFile << states.at(i).toString();
        outFile << "\tend\n";
    }

	outFile << "\t32'd" << states.size() + 1 << " begin\n";
	outFile << "\t\tdone <= 1;\n";
	outFile << "stateNext <= 0;";
	outFile << "\tend" << endl;
    
	outFile << "end\n";
    outFile << "endmodule" << endl;

    return;
}

string getBaseName(string filename){

    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }
    // Remove extension if present.
    const size_t period_idx = filename.rfind('.');
    if (string::npos != period_idx)
    {
        filename.erase(period_idx);
    }

    return filename;
}

