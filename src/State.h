#ifndef __STATE_H
#define __STATE_H

#include <vector>
#include <memory>
#include "components/Component.h"
#include <iostream>

extern int State_id;

class State{
	private:
		std::vector<bool> branch;
		std::vector<std::shared_ptr<Component>> operations;
		int stateNum;
		std::vector<State> nextStates;
	public:
		State(){
			stateNum = State_id;
			State_id++;
		}

		int getStateNum(){
			return stateNum;
		}

		void setBranch(unsigned len, unsigned binary){
			branch.resize(len, false);
			unsigned position = 1 << (len - 1);
			for(unsigned i = 0; i < len; i++){
				branch[i] = (position & binary) != 0;
				position  = position >> 1;
			}
		}

		std::vector<bool> getBranch(){
			return branch;
		}


		bool branchMatch(std::vector<bool> otherBranch){
			for(int i = 0; i < branch.size(); i++){
			}
			for(int i = 0; i < otherBranch.size(); i++){
			}

			if(otherBranch.size() != branch.size()){
				return false;
			}
			for(unsigned i = 0; i < branch.size(); i++){
				if(branch[i] != otherBranch[i]){
					return false;
				}
			}
			return true;
		}

		void addNextState(State next){
			if(this->branchMatch(next.getBranch()) || next.getBranch().size() < branch.size()){
				nextStates.push_back(next);
			} else {
				for(unsigned i = 0; i < operations.size(); i++){
					if(operations[i]->getComponentName() == "IFELSE" 
							&& operations[i]->branchMatchUpToEnd(next.getBranch())){
						operations[i]->addNextState(next);
					}
				}
			}
		}

		bool addComponent(std::shared_ptr<Component> toAdd){
			if(toAdd->getBranch().size() > branch.size())
				return false;
			std::vector<bool> cmpBranch = toAdd->getBranch();
			bool add = true;
			for(unsigned i = 0; i < cmpBranch.size(); i++){
				add = cmpBranch[i] == branch[i] && add;
			}
			if(add){
				operations.push_back(toAdd);
				
			}
			return add;
		}

		std::string toString(){
			std::string toReturn = "";
			bool hasIf = false;
			for(std::shared_ptr<Component> cmp : operations){
				toReturn += cmp->toString();
				if(cmp->getComponentName() == "IFELSE"){
					hasIf = true;
				} else{
					toReturn += ";";
				}
				toReturn += "\n\t\t";
			}
			if(!hasIf){
				toReturn += "stateNext <= " + std::to_string(nextStates.at(0).getStateNum());
			}
			return toReturn;
		}
};

#endif
