#ifndef __COMPONENT_H
#define __COMPONENT_H
#include <vector>
#include <string>
#include "Netlist.h"

class Component{
	protected:
		Netlist *netlist;
		int id;
		std::vector<std::string> inputs;
		std::vector<std::string> outputs;
	public:
		virtual std::string toString() = 0;
		virtual std::string getID() = 0;
		int getWidth(){
			
		}
}

#endif
