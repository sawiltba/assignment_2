#ifndef PRINTER_H
#define PRINTER_H


#include <iostream>
#include <vector>
// #include "Netlist.h"
using namespace std;

void Printer(ofstream &outFile, netlist Netlist); // DOUBLE CHECK WHEN NETLIST CLASS IS WRITTEN

void PrintIOW(ofstream &outFile, vector<variables> IOW);
void PrintComponent(ofstream &outFile, vector<string> component);


#endif



#pragma once
