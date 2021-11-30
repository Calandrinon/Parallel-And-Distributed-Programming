//
// Created by calandrinon on 11/29/21.
//

#ifndef HAMILTONIANPATH_HAMILTONIANCYCLEDETECTOR_H
#define HAMILTONIANPATH_HAMILTONIANCYCLEDETECTOR_H


#include <vector>
#include "Graph.h"

class HamiltonianCycleDetector {
    private:
        std::vector<int> possibleHamiltonianCycle;
        bool solutionFound;

    public:
        HamiltonianCycleDetector();
        void tryFromNode(Graph graph, int currentNode);
        bool sequentialHamiltonianCycleDetection(Graph graph);
        std::vector<int> getHamiltonCycle();
        bool hasSolution();
};


#endif //HAMILTONIANPATH_HAMILTONIANCYCLEDETECTOR_H
