#ifndef TASK1_ARCGRAPH_H
#define TASK1_ARCGRAPH_H

#include "IGraph.h"

typedef std::pair<size_t, size_t> Edge;

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(size_t size);

    explicit ArcGraph(const IGraph& g);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount() const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;

    std::vector<size_t> getPrevVertices(size_t vertex) const override;
private:
    std::vector<Edge> vecOfPairs;
    size_t vertixCount;
};

#endif //TASK1_ARCGRAPH_H
