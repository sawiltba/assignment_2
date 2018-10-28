#include "Reader.h"
#include <iostream>
#include <fstream>
#include <string>

Netlist read(ifstream inFile){
    Netlist net;
    ifstream progfile;
    string line;

    progfile.open(inFile);
    if(!progfile.is_open()){
        cout << inFile << "Read errors" << endl;
    }
    while(getline(progfile, line)){
        if(line.find("=") != -1){//equals found, component parser
            net.addComponent(line);
        }
        else{//no equals, variable parser
            net.addVariable(line);
        }
    }
    progfile.close();

    return net;
}
