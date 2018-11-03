#ifndef __COMP_H
#define __COMP_H
#include "Component.h"

class comp: public Component {
	private:
		static int number;
		
	public:
		//comp #(.DATAWIDTH(8)) c0 (in1, in2, gt, lt, eq)
		comp(Netlist* netlist, std::string line){
			this->netlist = netlist;
			this->id = number;
			number++;
			if(line.find("<") != std::string::npos){
				
			} else if(line.find("==") != std::string::npos){

			} else if(line.find(">") != std::string::npos){

			}
		}
};

#endif
