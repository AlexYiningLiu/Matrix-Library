cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(TESTNAME "TestCases")

# build source
project(MatrixLibrary)

file(GLOB project_SRCS src/*.cpp)
file(GLOB project_HEADERS include/*.hpp)

set(SOURCES ${project_SRCS} ${project_HEADERS})

add_executable(matrixLib ${SOURCES})
target_include_directories(matrixLib PRIVATE include)

# build tests
project(${TESTNAME})

add_subdirectory(test)
enable_testing()
add_test(${TESTNAME} ${TESTNAME})
