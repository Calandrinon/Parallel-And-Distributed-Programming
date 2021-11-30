#include <iostream>
#include "Graph.h"
#include "HamiltonianCycleDetector.h"

int main() {
    Graph graph(30);
    //graph.turnIntoCompleteGraph();
    graph.turnIntoRandomGraph();
    graph.print();

    HamiltonianCycleDetector hamiltonianCycleDetector;
    hamiltonianCycleDetector.tryFromNode(graph, 0);
    std::vector<int> hamiltonianCycle = hamiltonianCycleDetector.getHamiltonCycle();

    if (hamiltonianCycleDetector.hasSolution()) {
        std::cout << "The Hamiltonian cycle is:\n";
        for (int nodeIndex : hamiltonianCycle)
            std::cout << nodeIndex << " ";
    } else {
        std::cout << "The graph has no Hamiltonian cycle.\n";
    }
    return 0;
}
