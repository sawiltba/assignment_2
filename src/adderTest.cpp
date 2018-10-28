#include "Netlist.h"
#include "components/Adder.h"
#include <iostream>

int main(int argc, char** argv){
	Netlist n;
	std::string line = "output = itemOne + itemTwo";
	add a{&n, line};
	std::cout << line.length() << std::endl;
	std::cout << a.toString() << std::endl;			
}
