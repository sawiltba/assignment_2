#include <iostream>
#include "Reader.h"


using namespace std;

Netlist read(ifstream &inFile, int* error){
    Netlist net;
    string line;
    int comment = -1;

    while(getline(inFile, line)){
        //remove any comments if found
        comment = line.find("//");
        if(comment != -1){
            line.resize(comment);
        }

        if(!line.compare("\0")){
            //ignore only newline
        }
        else if(line.find("=") != -1 || line.find("register") != -1){//equals found, component parser
			if (net.addComponent(line) == 1) {
				cout << "add component errors in line " << line << endl;
				*error = 1;
				return net;
			 }
        }
        else{//no equals, variable parser
			if (net.addVariable(line) == 1) {
				cout << "Add Variable errors " << line << endl;
				*error == 1;
				return net;
			}
        }
		
    }
    return net;
}
