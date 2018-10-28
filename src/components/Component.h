#ifndef __COMPONENT_H
#define __COMPONENT_H
#include <vector>
#include <string>
#include "../Netlist.h"

class Component{
	protected:
		Netlist *netlist;
		int id;
		std::vector<std::string> inputs;
		std::vector<std::string> outputs;
		size_t IOStrLen(){
			size_t len = 0;
			for(std::string input : inputs){
				len += input.length();
			}
			for(std::string output : outputs){
				len += output.length();
			}
			return len;
		}
	public:
		virtual std::string toString() = 0;
		virtual std::string getID() = 0;
		int getWidth(){
			return 16;
		}
};

#endif
