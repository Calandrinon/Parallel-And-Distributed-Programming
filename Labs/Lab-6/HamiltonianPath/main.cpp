#include <iostream>
#include "Graph.h"
#include "HamiltonianCycleDetector.h"

int main() {
    Graph graph(10);
    graph.turnIntoCompleteGraph();

    HamiltonianCycleDetector hamiltonianCycleDetector;
    hamiltonianCycleDetector.sequentialCycleDetection(graph);
    std::vector<int> hamiltonianCycle = hamiltonianCycleDetector.getHamiltonCycle();

    std::cout << "The Hamiltonian cycle is:\n";
    for (int node: hamiltonianCycle)
        std::cout << node << " ";
    std::cout << hamiltonianCycle[0] << "\n";
    return 0;
}
