//
// Created by calandrinon on 11/29/21.
//

#include <vector>
#include <thread>
#include <mutex>
#include "HamiltonianCycleDetector.h"
#include "Graph.h"

HamiltonianCycleDetector::HamiltonianCycleDetector() {
    this->solutionFound = false;
}

void HamiltonianCycleDetector::tryFromNode(Graph graph, int currentNode) {
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

void HamiltonianCycleDetector::parallelTryFromNode(Graph graph, int currentNode, std::vector<int>* possibleSolution) {
    if (possibleSolution->size() == graph.getNumberOfNodes()) {
        int firstNodeInPath = (*possibleSolution)[0];
        int lastNodeInPath = (*possibleSolution)[possibleSolution->size() - 1];

        if (graph.doesEdgeExist(lastNodeInPath, firstNodeInPath)) {
            mutex.lock();
            if (!this->solutionFound) {
                this->solutionFound = true;
                possibleSolution->push_back(firstNodeInPath);
                this->solution = *possibleSolution;
            }
            mutex.unlock();
        }
        return;
    } else if (possibleSolution->empty()) {
        possibleSolution->push_back(currentNode);
    }

    for (int nodeIndex = 0; nodeIndex < graph.getNumberOfNodes() && !solutionFound; nodeIndex++) {
        if (!std::count(possibleSolution->begin(), possibleSolution->end(), nodeIndex) && graph.doesEdgeExist(currentNode, nodeIndex)) {
            possibleSolution->push_back(nodeIndex);
            parallelTryFromNode(graph, nodeIndex, possibleSolution);
            if (solutionFound)
                return;
            possibleSolution->pop_back();
        }
    }
}

void HamiltonianCycleDetector::parallelHamiltonianCycleDetection(Graph graph) {
    std::vector<std::thread> threads;
    int nodesPerThread = (int)(!graph.getNumberOfNodes() / std::thread::hardware_concurrency()
            ? 1
            : graph.getNumberOfNodes() / std::thread::hardware_concurrency());

    for (int threadIndex = 0; threadIndex < std::thread::hardware_concurrency(); threadIndex++)
        this->solutionsForEachThread.emplace_back();

    for (int nodeIndex = 0; nodeIndex < graph.getNumberOfNodes(); nodeIndex += nodesPerThread) {
        threads.emplace_back([=]() {
            int threadIndex = nodeIndex;
            for (int chunkNode = nodeIndex; chunkNode < nodeIndex + nodesPerThread; chunkNode++) {
                this->solutionsForEachThread[threadIndex].clear();
                this->parallelTryFromNode(graph, chunkNode, &this->solutionsForEachThread[threadIndex]);
            }
        });
    }

    for (int threadIndex = 0; threadIndex < threads.size(); threadIndex++)
        threads[threadIndex].join();
}

std::vector<int> HamiltonianCycleDetector::getHamiltonCycle() {
    return this->possibleHamiltonianCycle;
}

bool HamiltonianCycleDetector::hasSolution() const {
    return this->solutionFound;
}

std::vector<int> HamiltonianCycleDetector::getParallelSolution() {
    return this->solution;
}
