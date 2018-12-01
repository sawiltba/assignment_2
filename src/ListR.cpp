#include "ListR.h"

int *ListR(Netlist *netlist)
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
		for (std::vector<std::shared_ptr<Component>>::iterator it = netlist->getComponents().begin(); it != netlist->getComponents().end(); ++it) {
			if (/*it is valid and ALU*/) { Candidates[0].push_back(*it); }
			if (/*it is valid and Logic*/) { Candidates[1].push_back(*it); }
			if (/*it is valid and Mul*/) { Candidates[2].push_back(*it); }
		}
		
		for (int k = 0; k <= 2; k++) {
			for (std::vector<std::shared_ptr<Component>>::iterator it = Candidates[k].begin(); it != Candidates[k].end(); ++it) {
				int temp = (*it)->getLatency() - i;
				Slacks[k].push_back(temp);
			} // Compute the slacks

			int j = 0;
			for (auto it = Slacks[k].begin(); it != Slacks[k].end(); ++it) {
				if ((*it) == 0) {
					Candidates[k].erase(Candidates[k].begin() + j);
					if (atemp[k] == 0) { a[k]++; }
					else { atemp[k]--; }
				}
				j++;
			} // Schedule candidate operations with zero slack and update a
			
			while (atemp[k] > 0) {
				int smallest = 256;
				int smollest = 0;
				int j = 0;
				for (auto it = Slacks[k].begin(); it != Slacks[k].end(); ++it) {
					if ((*it) < smallest) { smollest = j; }
				} // Find smallest slack component
				atemp[k]--;
				Candidates[k].erase(Candidates[k].begin() + j); // Schedule smallest slack component
			} // Schedule candidate operations requiring no additional resources
		}
		i++; // Increment time step
		if (Unscheduled.empty() && Candidates[0].empty() && Candidates[1].empty() && Candidates[2].empty()) { done = true; } // Check done
	}
	return a;
}