cmake_minimum_required(VERSION 3.8)
project(NanoRobosCerebrais)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Grafo.h Vertice.h Heap.cpp Heap.h Aresta.h UnionFind.cpp UnionFind.h)
add_executable(NanoRobosCerebrais ${SOURCE_FILES})

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")