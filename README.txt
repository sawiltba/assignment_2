ECE 474

Kyle Cerniglia	kylecerniglia
Sarah Wiltbank	sawiltba
Ryan Sims	ryanjsims
Matthew Motooka	mmotooka
Laura Brubaker	laurabrubaker

Description:
The program receives input data in the form of pseudocode, it then parses the lines of code and identifies errors.
It then builds a netlist of variables, components, and wires from the valid data. Once fully formed it will output
a file with syntax correct verilog code.

Delegations:
	Ryan: Component.cpp, Variable.cpp

	Sarah: All signed verilog components

	Kyle: Reader.cpp, Netlist.cpp(addComponent), ShiftRight.h, cmake

	Matthew: Main.cpp, Printer.cpp

	Laura: Variable Parser, Debugging
