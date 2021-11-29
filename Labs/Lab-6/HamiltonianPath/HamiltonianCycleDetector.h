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
        void sequentialCycleDetection(Graph graph);
        std::vector<int> getHamiltonCycle();
};


#endif //HAMILTONIANPATH_HAMILTONIANCYCLEDETECTOR_H
