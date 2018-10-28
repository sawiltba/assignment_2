#include <iostream>
#include <fstream>
#include "Printer.h"
<<<<<<< HEAD
//#include "Netlist.h"
=======
#include "Reader.h"
>>>>>>> e167c22f730e356d284da8d0bc6cdb528c2e59d3

using namespace std;

int main(int argc, char *argv[]) {
	// command line parse and check
	if (argc != 3) {
		cout << "Invalid command line argument";
		return;
	}
	ifstream inFile;
	ofstream outFile;
	inFile.open(argv[1]);
	outFile.open(argv[2]);

	netlist Netlist = Reader(inFile);
	inFile.close;
	Printer(outFile, Netlist);
	outFile.close;

	return;
}
