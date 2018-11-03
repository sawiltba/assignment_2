#ifndef READER_H
#define READER_H

#include "Netlist.h"
#include "components/Component.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

Netlist read(ifstream inFile);

#endif

#pragma once
