#include "Reader.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Netlist read(ifstream inFile){
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
        else if(line.find("=") != -1){//equals found, component parser
            net.addComponent(net, line);
        }
        else{//no equals, variable parser
            net.addVariable(net, line);
        }
    }
    return net;
}
