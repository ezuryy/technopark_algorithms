#ifndef TASK1_IGRAPH_H
#define TASK1_IGRAPH_H

#include <iostream>
#include <vector>
#include <queue>

class IGraph {
public:
    virtual ~IGraph() = default;

    virtual void addEdge(size_t from, size_t to) = 0;

    virtual size_t verticesCount() const  = 0;

    virtual std::vector<size_t> getNextVertices(size_t vertex) const = 0;

    virtual std::vector<size_t> getPrevVertices(size_t vertex) const = 0;
};

void BFS(const IGraph& g, size_t vertex, void (*visit)(size_t));

#endif //TASK1_IGRAPH_H
