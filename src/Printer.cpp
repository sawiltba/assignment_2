#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Printer.h"
#include "Variable.h"
#include "components/Component.h"
using namespace std;

void Printer(string filename, ofstream &outFile, Netlist netlist) {
    string base = getBaseName(filename);
    outFile << "`timescale 1ns / 1ps" << endl;
    outFile << "module " << base << "(clk, rst,start,done, ";
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

    /*for(shared_ptr<Component> c : netlist.getComponents()){
        outFile << "\t" << c->toString();
    }*/
    
    outFile << "always @(posedge clk) begin\n";
    outFile << "if(rst == 1) begin\nstate <= 0;\nend\n";
    outFile << "else begin\nstate <= stateNext;\nend";
    outFile << "end\n";
    
    outFile << "always@(state, ";
    
    for(Variable v : netlist.getInputs()){
        if(v.getName() != "clk" && v.getName() != "rst"){
            outFile << "\t" << v.toString();
        }
    }
    
    outFile << ") begin\n";
    outFile << "case(state)\n";
    outFile << "\t32'd0: begin\n
    outFile << "\tdone <= 0;\n\tend";
    
    for(int i = 1; i < ; i++){
        outFile << "\t32'd" << i << ": begin\n
    outFile << "\t";
      for(shared_ptr<Component> c: netlist.getComponents()){
          if(i == c->id) {
              outFile << c->toString() << "\n\t";
          }
      }
        outFile << "end";
    }
    

    outFile << "endmodule" << endl;

    //IOW.insert(IOW.end(), netlist.getInputs().begin(), netlist.getInputs().end());
    //IOW.insert(IOW.end(), netlist.getOutputs().begin(), netlist.getOutputs().end());
    //IOW.insert(IOW.end(), netlist.getWires().begin(), netlist.getWires().end());

    //PrintIOW(outFile, IOW);

    // print operations
    //PrintComponent(outFile, netlist.getComponents());

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

void PrintIOW(ofstream& outFile, vector<Variable> IOW) {
    string  In1, In2, In8, In16, In32, In64,
            Out1, Out2, Out8, Out16, Out32, Out64,
            Wire1, Wire2, Wire8, Wire16, Wire32, Wire64;
    
    In1 += " start,";
    Wire32 += " State,";
    Out1 += " done,"
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
        
        
        if (it->getType().compare("variable") == 0) { // Wires
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
        outFile << "reg " << Wire1 << endl;
    }
    if (Wire2.size() != 0) {
        Wire2.pop_back();
        outFile << "reg [1:0]" << Wire2 << endl;
    }
    if (Wire8.size() != 0) {
        Wire8.pop_back();
        outFile << "reg [7:0]" << Wire8 << endl;
    }
    if (Wire16.size() != 0) {
        Wire16.pop_back();
        outFile << "reg [15:0]" << Wire16 << endl;
    }
    if (Wire32.size() != 0) {
        Wire32.pop_back();
        outFile << "reg [31:0]" << Wire32 << endl;
    }
    if (Wire64.size() != 0) {
        Wire64.pop_back();
        outFile << "reg [63:0]" << Wire64 << endl;
    }

    cout << endl;

    return;
}

/*void PrintComponent(ofstream &outFile, vector<Component> component) {
  for (vector<Component>::iterator it = component.begin(); it != component.end(); ++it) {
  outFile << it->toString() << endl;
  }

  return;

  }*/

