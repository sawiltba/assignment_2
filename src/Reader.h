#ifndef READER_H
#define READER_H

#include "Netlist.h"
#include "components/Component.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Netlist read(std::ifstream &inFile, int* error);

#endif

#pragma once
