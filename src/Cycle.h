#ifndef __CYCLE_H
#define __CYCLE_H

#include <vector>
#include <memory>
#include "State.h"
#include "components/Component.h"

class Cycle{
	private:
		std::vector<State> states;
		std::vector<std::shared_ptr<Component>> operations;
		int num;

	public:
		Cycle(int cycleNum){
			num = cycleNum;
		}

		int getCycleNum(){
			return num;
		}

		void pushComponent(std::shared_ptr<Component> cmp){
			operations.push_back(cmp);
		}

		bool createStates(){
			unsigned maxlen = 0;
			for(std::shared_ptr<Component> cmp : operations){
				if(cmp->getBranch().size() > maxlen){
					maxlen = cmp->getBranch().size();
				}
			}
			states.resize(1 << maxlen);

			for(unsigned i = 0; i < states.size(); i++){
				states[i].setBranch(maxlen, i);
				for(std::shared_ptr<Component> cmp : operations){
					states[i].addComponent(cmp);
					//Only adds if cmp's branch matches the state's branch
				}
			}
		}

		std::vector<State> getNextBranchStates(std::vector<bool> branch){
			std::vector<State> toReturn;
			if(states.size() == 1 || branch.size() == 0){
				return states;
			}
			unsigned size = branch.size();
			if(states[0].getBranch().size() < size){
				size = states[0].getBranch().size();
			}

			for(State& s : states){
				bool add = true;
				for(unsigned i = 0; i < size; i++){
					add = add && branch[i] == s.getBranch()[i];
				}
				if(add){
					toReturn.push_back(s);
				}
			}

			return toReturn;
		}
	
		std::vector<State>& getStates() {
			return states;
		}
};

#endif
