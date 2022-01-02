#include "IGraph.h"

void BFS(const IGraph& g, size_t vertex, void (*visit)(size_t)) {
    std::vector<bool> visited(g.verticesCount(), false);
    std::queue<size_t> bfsQueue;
    bfsQueue.push(vertex);
    visited[vertex] = true;
    while (!bfsQueue.empty()) {
        size_t current = bfsQueue.front();
        bfsQueue.pop();
        visit(current);
        auto neighbors = g.getNextVertices(current);
        for (const auto& neighbor : neighbors) {
            if (!visited[neighbor]) {
                bfsQueue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}