#include "ListGraph.h"

ListGraph::ListGraph(size_t size) : adjacencyLists(size) { }

ListGraph::ListGraph(const IGraph& g) : adjacencyLists(g.verticesCount()){
    for (size_t i = 0; i < adjacencyLists.size(); ++i) {
        adjacencyLists[i] = g.getNextVertices(i);
    }
}

void ListGraph::addEdge(size_t from, size_t to) {
    assert(to < adjacencyLists.size());
    assert(from < adjacencyLists.size());
    adjacencyLists[from].push_back(to);
}

size_t ListGraph::verticesCount() const {
    return adjacencyLists.size();
}

std::vector<size_t> ListGraph::getNextVertices(size_t vertex) const {
    assert(vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

std::vector<size_t> ListGraph::getPrevVertices(size_t vertex) const {
    assert(vertex < adjacencyLists.size());
    // O(V + E)
    std::vector<size_t> result;
    for (size_t from = 0; from < adjacencyLists.size(); ++from) {
        for (size_t i = 0; i < adjacencyLists[from].size(); ++i) {
            if (adjacencyLists[from][i] == vertex) {
                result.push_back(from);
                break;
            }
        }
    }
    return result;
}