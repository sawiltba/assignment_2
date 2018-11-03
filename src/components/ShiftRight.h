#ifndef __SHR_H
#define __SHR_H
#include "Component.h"

class shr: public Component {
	private:
        static int number;
    public:
        shr(Netlist* netlist, std::string line){
            this->netlist = netlist;
            this->idName = "shr";
            this->componentName = "SHR";
            this->calcIOs(">>", line);
            id = number++;
        }
};

int shr::number = 0;

#endif
