//
// Created by calandrinon on 11/29/21.
//

#include <vector>
#include "HamiltonianCycleDetector.h"
#include "Graph.h"

HamiltonianCycleDetector::HamiltonianCycleDetector() {
    this->solutionFound = false;
}

void HamiltonianCycleDetector::sequentialCycleDetection(Graph graph) {
    if (possibleHamiltonianCycle.size() == graph.getNumberOfNodes()) {
        int firstNodeInPath = possibleHamiltonianCycle[0];
        int lastNodeInPath = possibleHamiltonianCycle[possibleHamiltonianCycle.size() - 1];

        if (std::find(graph.getAdjacentNodes(firstNodeInPath).begin(), graph.getAdjacentNodes(firstNodeInPath).end(), lastNodeInPath) != possibleHamiltonianCycle.end())
            this->solutionFound = true;
        return;
    }

    for (int nodeIndex = 0; nodeIndex < graph.getNumberOfNodes(); nodeIndex++) {
        if (!std::count(possibleHamiltonianCycle.begin(), possibleHamiltonianCycle.end(), nodeIndex)) {
            possibleHamiltonianCycle.push_back(nodeIndex);
            sequentialCycleDetection(graph);
            if (solutionFound)
                return;
            possibleHamiltonianCycle.pop_back();
        }
    }
}

std::vector<int> HamiltonianCycleDetector::getHamiltonCycle() {
    return this->possibleHamiltonianCycle;
}
