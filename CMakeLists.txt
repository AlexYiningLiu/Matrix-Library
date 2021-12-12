cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 11)

project(MatrixLibrary)

file(GLOB project_SRCS src/*.cpp)

add_executable(matrixLib ${project_SRCS})
