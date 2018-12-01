#include "ListR.h"

int *ListR(Netlist netlist)
{
	int a[3] = { 1 }; // Initialize vector a so all entries have value of 1
	// Start times of all vectors already computed
	int i = 1; // Set time step equal to 1

	// Define candidate vectors
	std::vector<std::shared_ptr<Component>>ALUCandidates;
	std::vector<std::shared_ptr<Component>>LogCandidates;
	std::vector<std::shared_ptr<Component>>MulCandidates;
	int atemp[3] = { 1 }; // Define a counter
	bool done = false; // define done

	while (!done) {
		// Define candidate vectors
		std::vector<std::shared_ptr<Component>>ALUCandidates;
		std::vector<std::shared_ptr<Component>>LogCandidates;
		std::vector<std::shared_ptr<Component>>MulCandidates;
		std::vector<int>ALUSlacks;
		std::vector<int>LogSlacks;
		std::vector<int>MulSlacks;
		std::vector<std::shared_ptr<Component>>Candidates [3];
		Candidates[0] = ALUCandidates;
		Candidates[1] = LogCandidates;
		Candidates[2] = MulCandidates;
		std::vector<int>Slacks[3];
		Slacks[0] = ALUSlacks;
		Slacks[1] = LogSlacks;
		Slacks[2] = MulSlacks;
		int atemp[3]; // Define a counter
		for (int j = 0; j <= 2; j++) { atemp[j] = a[j]; }

		// Determine candidate operations
		for (std::vector<std::shared_ptr<Component>>::iterator it = netlist.getComponents().begin(); it != netlist.getComponents().end(); ++it) {
			if (/*it is valid and ALU*/) { Candidates[0].push_back(*it); }
			if (/*it is valid and Logic*/) { Candidates[1].push_back(*it); }
			if (/*it is valid and Mul*/) { Candidates[2].push_back(*it); }
		}
		
		for (int k = 0; k <= 2; k++) {
			// Compute the slacks
			for (std::vector<std::shared_ptr<Component>>::iterator it = Candidates[k].begin(); it != Candidates[k].end(); ++it) {
				int temp = (*it)->getLatency() - i;
				Slacks[k].push_back(temp);
			}
			// Schedule candidate operations with zero slack and update a
			auto jt = Candidates[k].begin();
			for (auto it = ALUSlacks.begin(); it != ALUSlacks.end(); ++it) {
				if ((*it) == 0) {
					// Schedule
				}
				++jt;
			}
			// Schedule candidate oeprations requiring no additional resources

		}
		i++; // Increment time step
		// Check done
	}





	return a;
}
