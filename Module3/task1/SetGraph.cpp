#include "SetGraph.h"

SetGraph::SetGraph(size_t size) : vecOfSets(size) { }

SetGraph::SetGraph(const IGraph& g) : vecOfSets(g.verticesCount()) {
    for (size_t from = 0; from < vecOfSets.size(); ++from) {
        for (const auto& to : g.getNextVertices(from)) {
            vecOfSets[from].insert(to);
        }
    }
}

void SetGraph::addEdge(size_t from, size_t to) {
    assert(from < vecOfSets.size());
    assert(to < vecOfSets.size());
    vecOfSets[from].insert(to);
}

size_t SetGraph::verticesCount() const {
    return vecOfSets.size();
}

std::vector<size_t> SetGraph::getNextVertices(size_t vertex) const {
    assert(vertex < vecOfSets.size());
    std::vector<size_t> neighbors;
    for (const auto& to : vecOfSets[vertex]) {
        neighbors.push_back(to);
    }
    return neighbors;
}

std::vector<size_t> SetGraph::getPrevVertices(size_t vertex) const {
    assert(vertex < vecOfSets.size());
    std::vector<size_t> result;
    for (size_t from = 0; from < vecOfSets.size(); ++from) {
        if (vecOfSets[from].find(vertex) != vecOfSets[from].end()) {
            result.push_back(from);
            break;
        }
    }
    return result;
}
