cmake_minimum_required(VERSION 3.20)
project(task1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")

add_executable(main main.cpp IGraph.h IGraph.cpp SetGraph.h SetGraph.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        testGraphs
        test.cpp
        IGraph.h
        IGraph.cpp
        ListGraph.h
        ListGraph.cpp
        MatrixGraph.h
        MatrixGraph.cpp
        SetGraph.h
        SetGraph.cpp
        ArcGraph.h
        ArcGraph.cpp
)

target_link_libraries(
        testGraphs
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(testGraphs)
