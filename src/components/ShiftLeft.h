#ifndef __SHL_H
#define __SHL_H
#include "Component.h"
#include "..\Netlist.h"

class shl: public Component {
    private:
        static int number;
    public:
        shl(Netlist* netlist, std::string line){
            this->netlist = netlist;
            this->idName = "shl";
            this->componentName = "SHL";
            this->calcIOs("<<", line);
            id = number++;
        }
};

int shl::number = 0;

#endif
