#include "Cycle.h"


Cycle::Cycle() {

}

int Cycle::createStates() {

}

void Cycle::pushComponent(std::shared_ptr<Component> toAdd) {
	operations.push_back(toAdd);
}
