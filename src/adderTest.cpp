#include "components/Adder.h"
#include <iostream>

int main(int argc, char** argv){
	Netlist n;
	add a{&n, "output = itemOne + itemTwo"};
	std::cout << a.toString() << std::endl;			
}
