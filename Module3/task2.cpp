// Дан невзвешенный неориентированный граф. В графе может быть
// несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между
// заданными вершинами. Требуемая сложность O(V+E).

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

class Graph {
public:
    Graph() = default;
    explicit Graph(const size_t& vertexNumber) {
        neighbors.resize(vertexNumber);
    }
    void addEdge(const size_t& from, const size_t& to) {
        neighbors[from].push_back(to);
        neighbors[to].push_back(from);
    }
    size_t minPathsCount(size_t from, size_t to);
private:
    std::vector<std::vector<size_t>> neighbors;
};

size_t Graph::minPathsCount(size_t from, size_t to) {
    std::vector<size_t> distance(neighbors.size(), SIZE_MAX);
    distance[from] = 0;

    std::vector<size_t> minPathCounter(neighbors.size(), 0);
    minPathCounter[from] = 1;

    std::queue<size_t> q;
    q.push(from);

    while(!q.empty()) {
        size_t vertex = q.front();
        q.pop();
        for (const auto& neigh : neighbors[vertex]) {
            if (minPathCounter[neigh] == 0) { // мы еще не знаем ни одного пути до этой вершины
                distance[neigh] = distance[vertex] + 1;
                minPathCounter[neigh] = minPathCounter[vertex];
                q.push(neigh);
            } else if (distance[neigh] == distance[vertex] + 1) { // есть другой способ дойти до neigh такой же длины
                minPathCounter[neigh] += minPathCounter[vertex]; // то добавляем кол-во способов дойти до род. вершины
            }
        }
    }
    return minPathCounter[to];
}

int main() {
    size_t vertexNumber = 0;
    size_t edgeNumber = 0;
    std::cin >> vertexNumber >> edgeNumber;

    Graph graph(vertexNumber);
    size_t from = 0;
    size_t to = 0;
    for (size_t i = 0; i < edgeNumber; ++i) {
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    std::cin >> from >> to;
    std::cout << graph.minPathsCount(from, to) << "\n";
    return 0;
}
