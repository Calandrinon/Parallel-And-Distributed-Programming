//
// Created by calandrinon on 11/29/21.
//

#include "Graph.h"

Graph::Graph(int _numberOfNodes): numberOfNodes(_numberOfNodes) {
    for (int index = 0; index < _numberOfNodes; index++)
        this->container.emplace_back();
}

void Graph::addEdge(int node, int otherNode) {
    this->container[node].push_back(otherNode);
}

std::vector<int> Graph::getAdjacentNodes(int node) {
    return this->container[node];
}

int Graph::getNumberOfNodes() {
    return this->numberOfNodes;
}

void Graph::turnIntoCompleteGraph() {
    for (int firstIndex = 0; firstIndex < this->container.size(); firstIndex++) {
        for (int secondIndex = 0; secondIndex < this->container.size(); secondIndex++)
            if (firstIndex != secondIndex)
                this->container[firstIndex].push_back(secondIndex);
    }
}

void Graph::print() {
    std::cout << "Edges of the graph:\n";

    for (int nodeIndex = 0; nodeIndex < this->container.size(); nodeIndex++) {
        for (int neighbourIndex = 0; neighbourIndex < this->container[nodeIndex].size(); neighbourIndex++)
            std::cout << "(" << nodeIndex << "; " << this->container[nodeIndex][neighbourIndex] << ")\n";
    }
}
