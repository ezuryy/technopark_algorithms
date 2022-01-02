#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

TEST(ListGraph, testBFS_ListGraph) {
    ListGraph graph(7);
    graph.addEdge(0,0);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(0,6);
    graph.addEdge(1,5);
    graph.addEdge(2,1);
    graph.addEdge(2,6);
    graph.addEdge(3,1);
    graph.addEdge(3,4);
    graph.addEdge(6,2);

    testing::internal::CaptureStdout();
    BFS(graph, 0, [](size_t vertex){std::cout << vertex << " ";});
    std::string output = testing::internal::GetCapturedStdout();

    std::string answer = "0 1 4 6 5 2 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 1, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "1 5 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 2, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "2 1 6 5 ";
    EXPECT_EQ(output, answer);
}

TEST(MatrixGraph, testBFS_MatrixGraph) {
    MatrixGraph graph(7);
    graph.addEdge(0,0);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(0,6);
    graph.addEdge(1,5);
    graph.addEdge(2,1);
    graph.addEdge(2,6);
    graph.addEdge(3,1);
    graph.addEdge(3,4);
    graph.addEdge(6,2);

    testing::internal::CaptureStdout();
    BFS(graph, 0, [](size_t vertex){std::cout << vertex << " ";});
    std::string output = testing::internal::GetCapturedStdout();

    std::string answer = "0 1 4 6 5 2 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 1, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "1 5 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 2, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "2 1 6 5 ";
    EXPECT_EQ(output, answer);
}

TEST(SetGraph, testBFS_SetGraph) {
    SetGraph graph(7);
    graph.addEdge(0,0);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(0,6);
    graph.addEdge(1,5);
    graph.addEdge(2,1);
    graph.addEdge(2,6);
    graph.addEdge(3,1);
    graph.addEdge(3,4);
    graph.addEdge(6,2);

    testing::internal::CaptureStdout();
    BFS(graph, 0, [](size_t vertex){std::cout << vertex << " ";});
    std::string output = testing::internal::GetCapturedStdout();

    std::string answer = "0 1 4 6 5 2 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 1, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "1 5 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 2, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "2 1 6 5 ";
    EXPECT_EQ(output, answer);
}

TEST(ArcGraph, testBFS_ArcGraph) {
    ArcGraph graph(7);
    graph.addEdge(0,0);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(0,6);
    graph.addEdge(1,5);
    graph.addEdge(2,1);
    graph.addEdge(2,6);
    graph.addEdge(3,1);
    graph.addEdge(3,4);
    graph.addEdge(6,2);

    testing::internal::CaptureStdout();
    BFS(graph, 0, [](size_t vertex){std::cout << vertex << " ";});
    std::string output = testing::internal::GetCapturedStdout();

    std::string answer = "0 1 4 6 5 2 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 1, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "1 5 ";
    EXPECT_EQ(output, answer);

    testing::internal::CaptureStdout();
    BFS(graph, 2, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();

    answer = "2 1 6 5 ";
    EXPECT_EQ(output, answer);
}

TEST(all, interface) {
    ListGraph graph(7);
    graph.addEdge(0,0);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(0,6);
    graph.addEdge(1,5);
    graph.addEdge(2,1);
    graph.addEdge(2,6);
    graph.addEdge(3,1);
    graph.addEdge(3,4);
    graph.addEdge(6,2);

    std::string answer = "0 1 4 6 5 2 ";

    MatrixGraph mGraph(graph);
    testing::internal::CaptureStdout();
    BFS(mGraph, 0, [](size_t vertex){std::cout << vertex << " ";});
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, answer);

    SetGraph sGraph(mGraph);
    testing::internal::CaptureStdout();
    BFS(sGraph, 0, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, answer);

    ArcGraph aGraph(sGraph);
    testing::internal::CaptureStdout();
    BFS(aGraph, 0, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, answer);

    ListGraph lGraph(aGraph);
    testing::internal::CaptureStdout();
    BFS(lGraph, 0, [](size_t vertex){std::cout << vertex << " ";});
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, answer);
}
