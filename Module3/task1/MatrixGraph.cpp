#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(size_t size) : matrix(size) {
    for (size_t i = 0; i < size; ++i) {
        matrix[i].resize(size);
        fill(matrix[i].begin(), matrix[i].end(), 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph& g) : matrix(g.verticesCount()){
    size_t size = g.verticesCount();
    for (size_t from = 0; from < size; ++from) {
        matrix[from].resize(size);
        auto neighbors = g.getNextVertices(from);
        for (const auto& to : neighbors) {
            matrix[from][to] = 1;
        }
    }
}

void MatrixGraph::addEdge(size_t from, size_t to) {
    assert(to < matrix.size());
    assert(from < matrix.size());
    matrix[from][to] = 1;
}

size_t MatrixGraph::verticesCount() const {
    return matrix.size();
}

std::vector<size_t> MatrixGraph::getNextVertices(size_t vertex) const {
    assert(vertex < matrix.size());
    std::vector<size_t> neighbors;
    for (size_t to = 0; to < matrix.size(); ++to) {
        if (matrix[vertex][to] == 1)
            neighbors.push_back(to);
    }
    return neighbors;
}

std::vector<size_t> MatrixGraph::getPrevVertices(size_t vertex) const {
    assert(vertex < matrix.size());
    std::vector<size_t> result;
    for (size_t from = 0; from < matrix.size(); ++from) {
        if (matrix[from][vertex] == 1)
            result.push_back(from);
    }
    return result;
}
