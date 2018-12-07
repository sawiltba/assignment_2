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

		void createStates(){
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
					states[i].addComponent(cmp); //Only adds if cmp's branch matches the state's branch
				}
			}
		}
};

#endif
