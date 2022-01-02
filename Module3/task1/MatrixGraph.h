#ifndef TASK1_MATRIXGRAPH_H
#define TASK1_MATRIXGRAPH_H

#include <vector>

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t size);

    explicit MatrixGraph(const IGraph& g);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount() const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;

    std::vector<size_t> getPrevVertices(size_t vertex) const override;
private:
    std::vector<std::vector<bool>> matrix;
};

#endif //TASK1_MATRIXGRAPH_H
