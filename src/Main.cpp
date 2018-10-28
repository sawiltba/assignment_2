#include <iostream>
#include <fstream>
#include "Printer.h"

using namespace std;

int main(int argc, char *argv[]) {
	// command line parse and check
	if (argc != 3) {
		cout << "Incorrect command line argument";
		return;
	}
	ifstream inFile;
	ofstream outFile;
	inFile.open(argv[1]);
	outFile.open(argv[2]);

	// netlist Netlist = Reader(inFile);
	// Printer(outFile, Netlist);

	return;
}