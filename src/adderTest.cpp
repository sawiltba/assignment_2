#include "Netlist.h"
#include "components/Component.h"
#include "components/Adder.h"

#include <iostream>

int main(int argc, char** argv){
	Netlist n;
	n.addVariable("input UInt8 itemOne, itemTwo");
	n.addVariable("output UInt64 output");
	std::string line = "output = itemOne + itemTwo";
	add a{&n, line};
	std::cout << line.length() << std::endl;
	std::cout << a.toString();
	std::cout << a.isSigned() << std::endl;
}
