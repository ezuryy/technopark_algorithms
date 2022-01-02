#include <iostream>

#include "SetGraph.h"
#include "IGraph.h"

int main() {
    SetGraph graph(5);
    graph.addEdge(0,1);
    graph.addEdge(0,2);
    graph.addEdge(0,3);
    graph.addEdge(1,3);
    graph.addEdge(2,3);
    graph.addEdge(2,4);
    BFS(graph, 0, [](size_t vertex){std::cout << vertex << " ";});

    return 0;
}
