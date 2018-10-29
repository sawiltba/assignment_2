#include "Netlist.h"
#include "components/Component.h"
#include "components/Adder.h"
#include "components/Subtractor.h"
#include "components/Multiplier.h"
#include "components/ShiftLeft.h"

#include <iostream>

int main(int argc, char** argv){
	Netlist n;
	n.addVariable("input Int8 itemOne, itemTwo");
	n.addVariable("input Int16 number, 1234");
	n.addVariable("output Int32 output, diff");
    n.addVariable("wire UInt16 connection");
	std::string line = "output = itemOne + itemTwo";
	add a{&n, line};
    sub s{&n, "diff = number - 1234"};
    mult m{&n, "output = itemOne * diff"};
    shl shifter{&n, "connection = itemTwo << 1234"};
	std::cout << a.toString();
    std::cout << s.toString();
    std::cout << m.toString();
    std::cout << shifter.toString();

}
