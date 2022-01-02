#include "ArcGraph.h"

ArcGraph::ArcGraph(size_t size) : vertixCount(size) { }

ArcGraph::ArcGraph(const IGraph& g) {
    vertixCount = g.verticesCount();
    for (size_t from = 0; from < vertixCount; ++from) {
        for (const auto& to : g.getNextVertices(from)) {
            vecOfPairs.emplace_back(from, to);
        }
    }
}

void ArcGraph::addEdge(size_t from, size_t to) {
    assert(from < vertixCount);
    assert(to < vertixCount);
    vecOfPairs.emplace_back(from, to);
}

size_t ArcGraph::verticesCount() const {
    return vertixCount;
}

std::vector<size_t> ArcGraph::getNextVertices(size_t vertex) const {
    assert(vertex < vertixCount);
    std::vector<size_t> neighbors;
    for (const auto& pair : vecOfPairs) {
        if (pair.first == vertex) {
            neighbors.push_back(pair.second);
        }
    }
    return neighbors;
}

std::vector<size_t> ArcGraph::getPrevVertices(size_t vertex) const {
    assert(vertex < vertixCount);
    std::vector<size_t> result;
    for (const auto& pair : vecOfPairs) {
        if (pair.second == vertex) {
            result.push_back(pair.first);
        }
    }
    return result;
}
