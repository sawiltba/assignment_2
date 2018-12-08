#include "ListR.h"
#include <iostream>

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
    int* a = (int*)malloc(3 * sizeof(int)); // Initialize vector a so all entries have value of 1
    for(int i = 0; i < 3; i++){
		a[i] = 1;
	}
	
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
        for(std::shared_ptr<Component> root : JediCouncil){
            auto ALUcand = getCandidates(root, RES::ALU);
            auto LOGcand = getCandidates(root, RES::LOGIC);
            auto MULcand = getCandidates(root, RES::MULT);

            Candidates[0].insert(Candidates[0].end(), ALUcand.begin(), ALUcand.end());            
            Candidates[1].insert(Candidates[1].end(), LOGcand.begin(), LOGcand.end());            
            Candidates[2].insert(Candidates[2].end(), MULcand.begin(), MULcand.end());            
        }
		
        for (int k = 0; k <= 2; k++) {
			bool toSchedule = false;
            for (int j = Candidates[k].size() - 1; j >= 0; j--) {
				if(Candidates[k][j]->isScheduled()){
					continue;
				}
                if (Candidates[k][j]->getStartTime() - i == 0) {
						Candidates[k][j]->schedule(i);
						if (atemp[k] == 0) { a[k]++; }
						else { atemp[k]--; }
                }
				if(!Candidates[k][j]->isScheduled()){
					toSchedule = true;
				}
            } // Schedule candidate operations with zero slack and update a
            while (atemp[k] > 0 && toSchedule) {
                int leastSlackIndex = 0;
                int leastSlack = Candidates[k][leastSlackIndex]->getStartTime() - i;
                for(int j = Candidates[k].size() - 1; j >= 0; j--){
                    int currSlack = Candidates[k][j]->getStartTime() - i;
                    if(currSlack < leastSlack){
                        leastSlack = currSlack;
                        leastSlackIndex = j;
                    }

                }
                
                atemp[k]--;
                Candidates[k][leastSlackIndex]->schedule(i);
				toSchedule = false;
				for(int j = 0; j < Candidates[k].size(); j++){
					if(!Candidates[k][j]->isScheduled()){
						toSchedule = true;
					}
				}
                // Schedule smallest slack component

            } // Schedule candidate operations requiring no additional resources
        }
		bool allScheduled = true;
		for(int num = 0; num < Unscheduled.size(); num++){
			if(!Unscheduled[num]->isScheduled()){
				allScheduled = false;
			}
		}
        i++; // Increment time step
        if (allScheduled
			   	/*&& Candidates[0].empty() 
				&& Candidates[1].empty() 
				&& Candidates[2].empty()*/) { 
			done = true; 
		} // Check done
    }
    return a;
}
