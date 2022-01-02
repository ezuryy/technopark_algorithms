#ifndef TASK1_LISTGRAPH_H
#define TASK1_LISTGRAPH_H

// ListGraph, хранящий граф в виде массива списков смежности

#include <vector>
#include <queue>
#include <cassert>

#include "IGraph.h"

class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t size);

    explicit ListGraph(const IGraph& g);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount() const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;

    std::vector<size_t> getPrevVertices(size_t vertex) const override;
private:
    std::vector<std::vector<size_t>> adjacencyLists;
};

#endif //TASK1_LISTGRAPH_H
