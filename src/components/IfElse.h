#ifndef __IFELSE_H
#define __IFELSE_H
#include "Component.h"
#include "../State.h"
#include <iostream>

class ifelse: public Component {
	private:
		static int number;
		std::string condition;
		std::vector<State> nextStates;
	public:

		ifelse(Netlist* netlist, std::string input){
            this->condition = input;
            this->inputs.push_back(input);
			this->netlist = netlist;
			this->idName = "ifelse";
			this->componentName = "IFELSE";
			this->latency = 0;
			id = number;
			number++;
			nextStates.resize(2);
		}

		void addBranch(bool a) override{
			branch.insert(branch.begin(), a);
			for(std::shared_ptr<Component> cmp : younglings){
				cmp->addBranch(a);
			}
		}

		void addNextState(State& next) override {
			auto b = next.getBranch();
			if(b[b.size() - 1]){
				nextStates[0] = next;
			} else{
				nextStates[1] = next;
			}
		}

		int getNumber(){
			return number;
		}

		std::string toString() override{
			std::string toReturn;
			std::cout << "IfElse tostring" << std::endl;
			int loop = 0;
			//if ('condition')
			toReturn += "if ( ";
			toReturn += this->condition;
			toReturn += " ) begin\n";
			toReturn += "\t\t\tstateNext <= " + std::to_string(this->nextStates[0].getStateNum()) + ";\n";
            toReturn += "\t\tend\n";
			toReturn += "\t\telse begin\n";
			toReturn += "\t\t\tstateNext <= " + std::to_string(this->nextStates[1].getStateNum()) + ";\n";
            toReturn += "\t\tend\n";
			return toReturn;
		}
};

int ifelse::number = 0;

#endif
