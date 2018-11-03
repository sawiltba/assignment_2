#ifndef PRINTER_H
#define PRINTER_H


#include <iostream>
#include <vector>
#include "Variable.h"
#include "Netlist.h"
using namespace std;

void Printer(ofstream &outFile, Netlist Netlist); // DOUBLE CHECK WHEN NETLIST CLASS IS WRITTEN

void PrintIOW(ofstream &outFile, vector<Variable> IOW);
void PrintComponent(ofstream &outFile, vector<string> component);


#endif



#pragma once
