//
// Created by calandrinon on 11/29/21.
//

#include <vector>
#include "HamiltonianCycleDetector.h"
#include "Graph.h"

HamiltonianCycleDetector::HamiltonianCycleDetector() {
    this->solutionFound = false;
}

void HamiltonianCycleDetector::tryFromNode(Graph graph, int currentNode = 0) {
    if (possibleHamiltonianCycle.size() == graph.getNumberOfNodes()) {
        int firstNodeInPath = possibleHamiltonianCycle[0];
        int lastNodeInPath = possibleHamiltonianCycle[possibleHamiltonianCycle.size() - 1];

        if (graph.doesEdgeExist(lastNodeInPath, firstNodeInPath)) {
            this->solutionFound = true;
            possibleHamiltonianCycle.push_back(firstNodeInPath);
        }
        return;
    } else if (possibleHamiltonianCycle.empty()) {
        possibleHamiltonianCycle.push_back(currentNode);
    }

    for (int nodeIndex = 0; nodeIndex < graph.getNumberOfNodes() && !solutionFound; nodeIndex++) {
        if (!std::count(possibleHamiltonianCycle.begin(), possibleHamiltonianCycle.end(), nodeIndex) && graph.doesEdgeExist(currentNode, nodeIndex)) {
            possibleHamiltonianCycle.push_back(nodeIndex);
            tryFromNode(graph, nodeIndex);
            if (solutionFound)
                return;
            possibleHamiltonianCycle.pop_back();
        }
    }
}

bool HamiltonianCycleDetector::sequentialHamiltonianCycleDetection(Graph graph) {
    for (int nodeIndex = 0; nodeIndex < graph.getNumberOfNodes(); nodeIndex++) {
        this->possibleHamiltonianCycle.clear();
        this->tryFromNode(graph, nodeIndex);
        if (this->solutionFound)
            return true;
    }

    return false;
}

std::vector<int> HamiltonianCycleDetector::getHamiltonCycle() {
    return this->possibleHamiltonianCycle;
}

bool HamiltonianCycleDetector::hasSolution() {
    return this->solutionFound;
}
