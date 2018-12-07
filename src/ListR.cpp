#include "ListR.h"

std::vector<std::shared_ptr<Component>> getCandidates(std::shared_ptr<Component> root, RES type){
    auto toReturn = std::vector<std::shared_ptr<Component>>{};
    if(!root->canSchedule()){
        return toReturn;
    }
    if(!root->isScheduled()){
        switch(type){
            case RES::ALU:
                if(root->getComponentName() == "SUB" || root->getComponentName() == "ADD"){
                    toReturn.push_back(root);
                }
                break;
            case RES::MULT:
                if(root->getComponentName() == "MULT"){
                    toReturn.push_back(root);
                }
                break;
            case RES::LOGIC:
                if(root->getComponentName() != "SUB" && root->getComponentName() != "ADD" && root->getComponentName() != "MULT"){
                    toReturn.push_back(root);
                }
                break;
        }
    } else {
        for(auto child : root->getYounglings()){
            auto resources = getCandidates(child, type);
            toReturn.insert(toReturn.end(), resources.begin(), resources.end());
        }
    }
    return toReturn;
}

int *ListR(Netlist *netlist, int latency)
{
    int a[3] = { 1 }; // Initialize vector a so all entries have value of 1
    // Start times of all vectors already computed
    int i = 1; // Set time step equal to 1

    int atemp[3] = { 1 }; // Define a counter
    bool done = false; // define done
    std::vector<std::shared_ptr<Component>>Unscheduled; // Define unscheduled vector
    std::vector<std::shared_ptr<Component>>ALUCandidates; // Define candidate vectors
    std::vector<std::shared_ptr<Component>>LogCandidates;
    std::vector<std::shared_ptr<Component>>MulCandidates;
    std::vector<std::shared_ptr<Component>>Candidates[3];
    Candidates[0] = ALUCandidates;
    Candidates[1] = LogCandidates;
    Candidates[2] = MulCandidates;

    Unscheduled = netlist->getComponents();
    std::vector<std::shared_ptr<Component>>JediCouncil;
    for (auto it = Unscheduled.begin(); it != Unscheduled.end(); ++it) {
        if ((*it)->getMasters().empty()) {
            JediCouncil.push_back(*it);
            (*it)->calcTimeFrame(latency);
        }
    }

    while (!done) {

        std::vector<int>ALUSlacks;
        std::vector<int>LogSlacks;
        std::vector<int>MulSlacks;
        std::vector<int>Slacks[3];
        Slacks[0] = ALUSlacks;
        Slacks[1] = LogSlacks;
        Slacks[2] = MulSlacks;
        int atemp[3]; // Define a counter
        for (int j = 0; j <= 2; j++) { atemp[j] = a[j]; }

        // Determine candidate operations	FIXME
        //for (std::vector<std::shared_ptr<Component>>::iterator it = netlist->getComponents().begin(); it != netlist->getComponents().end(); ++it) {

        //}
        for(std::shared_ptr<Component> root : JediCouncil){
            auto ALUcand = getCandidates(root, RES::ALU);
            auto LOGcand = getCandidates(root, RES::LOGIC);
            auto MULcand = getCandidates(root, RES::MULT);

            Candidates[0].insert(Candidates[0].end(), ALUcand.begin(), ALUcand.end());            
            Candidates[1].insert(Candidates[1].end(), LOGcand.begin(), LOGcand.end());            
            Candidates[2].insert(Candidates[2].end(), MULcand.begin(), MULcand.end());            
        }

        for (int k = 0; k <= 2; k++) {
            for (int j = Candidates[k].size() - 1; j >= 0; j--) {
            //    int temp = (*it)->getStartTime() - i;
            //    Slacks[k].push_back(temp);
            //} // Compute the slacks

            //int j = 0;
            //for (auto it = Slacks[k].begin(); it != Slacks[k].end(); ++it) {
                if (Candidates[k][j]->getStartTime() - i == 0) {
                    Candidates[k][j]->schedule(i);
                    Candidates[k].erase(Candidates[k].begin() + j);
                    if (atemp[k] == 0) { a[k]++; }
                    else { atemp[k]--; }
                }
                //j++;
            } // Schedule candidate operations with zero slack and update a

            while (atemp[k] > 0 && Candidates[k].size() > 0) {
                int leastSlackIndex = 0;
                int leastSlack = Candidates[k][leastSlackIndex]->getStartTime() - i;
                for(int j = Candidates[k].size() - 1; j >= 0; j--){
                    int currSlack = Candidates[k][j]->getStartTime() - i;
                    if(currSlack < leastSlack){
                        leastSlack = currSlack;
                        leastSlackIndex = j;
                    }

                }
                
                /*int smallest = 256;
                int smollest = 0;
                int j = 0;
                for (auto it = Slacks[k].begin(); it != Slacks[k].end(); ++it) {
                    if ((*it) < smallest) { smollest = j; }
                } // Find smallest slack component*/

                atemp[k]--;
                Candidates[k][leastSlackIndex]->schedule(i);
                Candidates[k].erase(Candidates[k].begin() + leastSlackIndex); // Schedule smallest slack component
            } // Schedule candidate operations requiring no additional resources
        }
        i++; // Increment time step
        if (Unscheduled.empty() && Candidates[0].empty() && Candidates[1].empty() && Candidates[2].empty()) { done = true; } // Check done
    }
    return a;
}
