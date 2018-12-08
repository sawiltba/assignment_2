#ifndef __LIST_R
#define __LIST_R

#include <vector>
#include <memory>

#include "Netlist.h"
#include "components/Component.h"

enum class RES {
    ALU,
    MULT,
    LOGIC
};

std::vector<std::shared_ptr<Component>> getCandidates(std::shared_ptr<Component> root, RES type);
int *ListR(Netlist* netlist, int latency);

#endif
