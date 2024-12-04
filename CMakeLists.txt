cmake_minimum_required(VERSION 3.27.8)
project(Project3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project3 src/main.cpp src/BTree.cpp src/hashMap.cpp)
