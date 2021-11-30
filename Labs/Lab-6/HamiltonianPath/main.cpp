#include <iostream>
#include "Graph.h"
#include "HamiltonianCycleDetector.h"

void sequentialImplementation(Graph* graph) {
    HamiltonianCycleDetector hamiltonianCycleDetector;
    hamiltonianCycleDetector.sequentialHamiltonianCycleDetection(*graph);

    if (hamiltonianCycleDetector.hasSolution()) {
        std::vector<int> hamiltonianCycle = hamiltonianCycleDetector.getHamiltonCycle();
        std::cout << "Sequential solution -> The Hamiltonian cycle is:\n";
        for (int nodeIndex : hamiltonianCycle)
            std::cout << nodeIndex << " ";
        std::cout << "\n";
    } else {
        std::cout << "The graph has no Hamiltonian cycle.\n";
    }
}

void parallelImplementation(Graph* graph) {
    HamiltonianCycleDetector hamiltonianCycleDetector;
    hamiltonianCycleDetector.parallelHamiltonianCycleDetection(*graph);

    if (hamiltonianCycleDetector.hasSolution()) {
        std::vector<int> hamiltonianCycle = hamiltonianCycleDetector.getParallelSolution();
        std::cout << "Parallel solution -> The Hamiltonian cycle is:\n";
        for (int nodeIndex : hamiltonianCycle)
            std::cout << nodeIndex << " ";
        std::cout << "\n";
    } else {
        std::cout << "The graph has no Hamiltonian cycle.\n";
    }
}

int main() {
    Graph graph(12);
    //graph.turnIntoCompleteGraph();
    graph.turnIntoRandomGraph();
    graph.print();

    sequentialImplementation(&graph);
    parallelImplementation(&graph);
    return 0;
}
