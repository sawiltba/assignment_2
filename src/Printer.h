#ifndef PRINTER_H
#define PRINTER_H


#include <iostream>
#include <vector>
#include <memory>
#include "Variable.h"
#include "Netlist.h"

void Printer(std::ofstream &outFile, Netlist Netlist); // DOUBLE CHECK WHEN NETLIST CLASS IS WRITTEN

void PrintIOW(std::ofstream &outFile, std::vector<Variable> IOW);
void PrintComponent(std::ofstream &outFile, std::vector<std::shared_ptr<Component>> component);


#endif



#pragma once
