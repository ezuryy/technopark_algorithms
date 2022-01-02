#ifndef TASK1_SETGRAPH_H
#define TASK1_SETGRAPH_H

#include <set>

#include "IGraph.h"

class SetGraph : public IGraph {
public:
    explicit SetGraph(size_t size);

    explicit SetGraph(const IGraph& g);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount() const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;

    std::vector<size_t> getPrevVertices(size_t vertex) const override;
private:
    std::vector<std::set<size_t>> vecOfSets;
};


#endif //TASK1_SETGRAPH_H
