#ifndef PRINTER_H
#define PRINTER_H


#include <iostream>
#include <vector>
#include <memory>
#include "Variable.h"
#include "Netlist.h"
#include "State.h"

void Printer(std::string filename, std::ofstream &outFile, Netlist Netlist, std::vector<State> states);
std::string getBaseName(std::string filename);
//void PrintIOW(std::ofstream &outFile, std::vector<Variable> IOW);
//void PrintComponent(std::ofstream &outFile, std::vector<std::shared_ptr<Component>> component);


#endif



#pragma once
