#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Printer.h"

#include "Netlist.h"
#include "Reader.h"
#include "ListR.h"

int State_id = 1;

using namespace std;

int main(int argc, char *argv[]) {
    // command line parse and check
    if (argc != 4) {
        cout << "Invalid command line arguments, format: NETLIST_FILENAME LATENCY VERILOG_FILENAME" << endl;
        return 1;
    }
    ifstream inFile; 
    ofstream outFile;	
    inFile.open(argv[1]);
    if(!inFile.is_open()){
        cout << argv[1] << " Read errors" << endl;
        return 1;
    }

    int error = 0;
    try{
        Netlist netlist = read(inFile, &error);
        if (error == 1) {
            inFile.close();
            return 1;
        }
		int latency = stoi(string{argv[2]});
        ListR(&netlist, latency);
		vector<shared_ptr<Cycle>> cycles = netlist.getCycles(latency, &error);
		if(error == 1){
			cout << "Error creating cycles with latency " << latency << endl;
		}
		vector<State> states;
		for(int i = 0; i < cycles.size(); i++){
			vector<State> cycleStates = cycles.at(i)->getStates();
			
			states.insert(states.end(), cycles.at(i)->getStates().begin(), cycles.at(i)->getStates().end());
		}

        outFile.open(argv[3]);
        if (!outFile.is_open()) {
            cout << argv[3] << " Read errors" << endl;
            return 1;
        }
        inFile.close();
        Printer(std::string{argv[3]}, outFile, netlist, states);
        outFile.close();
    } catch(length_error &e){
        cout << e.what() << endl;
        return 1;
    } catch(out_of_range &e){
		cout << e.what() << endl;
		return 2;
	}

    return 0;
}
