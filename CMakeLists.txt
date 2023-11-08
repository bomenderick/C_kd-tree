cmake_minimum_required(VERSION 3.12)
project(kd-tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(kd-tree )
find_library (PSAPI -lpsapi)

add_executable(kd-tree kdTree.h kdTree.cpp main.cpp)


