#include "Reader.h"
#include <iostream>
#include <fstream>
#include <string>

Netlist read(ifstream inFile){
    Netlist net;
    string line;
    comment = -1;

    while(getline(inFile, line)){
        //remove any comments if found
        comment = line.find("//");
        if(comment != -1){
            line.resize(comment);
        }

        if(!line.compare("\0")){
            //ignore only newline
        }
        else if(line.find("=") != -1){//equals found, component parser
            net.addComponent(line);
        }
        else{//no equals, variable parser
            net.addVariable(line);
        }
    }
    return net;
}
