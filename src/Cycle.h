#ifndef __CYCLE_H
#define __CYCLE_H

#include <vector>
#include <memory>
#include "./components/Component.h"


class Cycle {
private:
	std::vector<State> states;
	std::vector<std::shared_ptr<Component>> operations;
public:
	Cycle();
	int createStates();
	void pushComponent(std::shared_ptr<Component> toAdd);
	std::vector<State>& getStates() {
		return states;
	}

};

#endif
