#include <iostream>
#include <fstream>
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

	// vector Netlist = Reader(inFile);
	// Printer(outFile, Netlist);

	return;
}