// Требуется отыскать самый короткий маршрут между городами.
// Из города может выходить дорога, которая возвращается в этот же город.
//
// Требуемое время работы O((N + M)log N), где N – количество городов,
// M – известных дорог между ними.
// N ≤ 10000, M ≤ 250000.
// Длина каждой дороги ≤ 10000.

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef std::pair<size_t, size_t> Edge;

struct Neighbors {
    std::vector<Edge> edges;
};

class Graph {
public:
    Graph() = default;
    explicit Graph(const size_t& vertexNumber) {
        neighbors.resize(vertexNumber);
    }
    void addEdge(const size_t& from, const size_t& to, const size_t& distance) {
        neighbors[from].edges.emplace_back(Edge(distance, to));
        neighbors[to].edges.emplace_back(Edge(distance, from));
    }
    size_t Dijkstra(size_t from, size_t to);
private:
    std::vector<Neighbors> neighbors;
};

size_t Graph::Dijkstra(size_t from, size_t to) {
    std::vector<size_t> distance(neighbors.size(), SIZE_MAX);
    distance[from] = 0;

    std::multiset<Edge> q;
    q.insert(Edge(distance[from], from));

    while(!q.empty()) {
        size_t vertex = q.begin()->second;
        q.erase(q.begin());
        for (const auto& neigh : neighbors[vertex].edges) {
            if (distance[neigh.second] > distance[vertex] + neigh.first) {
                if (distance[vertex] != SIZE_MAX)
                    q.erase(Edge(distance[vertex], vertex));
                distance[neigh.second] = distance[vertex] + neigh.first;
                q.insert(Edge(neigh.first, neigh.second));
            }
        }
    }
    return distance[to];
}

int main() {
    size_t vertexNumber = 0;
    size_t edgeNumber = 0;
    std::cin >> vertexNumber >> edgeNumber;

    Graph graph(vertexNumber);
    size_t from = 0;
    size_t to = 0;
    size_t distance = 0;
    for (size_t i = 0; i < edgeNumber; ++i) {
        std::cin >> from >> to >> distance;
        graph.addEdge(from, to, distance);
    }

    std::cin >> from >> to;
    std::cout << graph.Dijkstra(from, to) << "\n";
    return 0;
}