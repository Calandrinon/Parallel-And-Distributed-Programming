//
// Created by calandrinon on 11/29/21.
//

#ifndef HAMILTONIANPATH_GRAPH_H
#define HAMILTONIANPATH_GRAPH_H
#include <iostream>
#include <vector>

class Graph {
    private:
        std::vector<std::vector<int>> container;
        int numberOfNodes;

    public:
        Graph(int _numberOfNodes);
        void addEdge(int node, int otherNode);
        std::vector<int> getAdjacentNodes(int node);
        int getNumberOfNodes();
        void turnIntoCompleteGraph();
        void turnIntoRandomGraph();
        bool doesEdgeExist(int firstNode, int secondNode);
        void print();
};


#endif //HAMILTONIANPATH_GRAPH_H
