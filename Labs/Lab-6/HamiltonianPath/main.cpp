#include <iostream>
#include "Graph.h"
#include "HamiltonianCycleDetector.h"

int main() {
    Graph graph(1000);
    //graph.turnIntoCompleteGraph();
    graph.turnIntoRandomGraph();
    graph.print();

    HamiltonianCycleDetector hamiltonianCycleDetector;
    hamiltonianCycleDetector.sequentialHamiltonianCycleDetection(graph);

    if (hamiltonianCycleDetector.hasSolution()) {
        std::vector<int> hamiltonianCycle = hamiltonianCycleDetector.getHamiltonCycle();
        std::cout << "The Hamiltonian cycle is:\n";
        for (int nodeIndex : hamiltonianCycle)
            std::cout << nodeIndex << " ";
    } else {
        std::cout << "The graph has no Hamiltonian cycle.\n";
    }
    return 0;
}
