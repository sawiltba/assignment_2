#include <iostream>
#include <fstream>
#include "Printer.h"

#include "Netlist.h"
#include "Reader.h"


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
    if(!inFile.is_open()){
        cout << argv[1] << " Read errors" << endl;
    }
	outFile.open(argv[2]);
	if(!outFile.is_open()){
        cout << argv[2] << " Read errors" << endl;
    }
	Netlist Netlist = read(inFile);
	inFile.close;
	Printer(outFile, Netlist);
	outFile.close;

	return 1;
}
