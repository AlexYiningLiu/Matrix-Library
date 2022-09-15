# Matrix-Library

##### Table of Contents 
- [Description](#description)
- [Project Files](#project-files)
- [Build Instructions](#build-instructions)
- [Running Instructions](#running-instructions)
- [Current Limitations](#current-limitations)

## Description
A library of basic matrix operations implemented using only standard library functions. 
Currently supports initialization using the C++ guidelines of the Rule of Five, as well as 
matrix multiplication, addition, subtraction, and transpose operations. The user can choose
to handle matrix multiplication either synchronously or asynchronously using multithreading.

## Project Files

### `matrix_library.hpp`
[matrix_library.hpp](include/matrix_library.hpp) contains the base Matrix class and function definitions

### `identity_matrix.hpp`
[identity_matrix.hpp](include/identity_matrix.hpp) contains a derived class of the Matrix class with several overriden functions

### `concurreny_utils.hpp`
[concurrency_utils.hpp](include/concurrency_utils.hpp) contains utility functions used for multi-threaded matrix multiplication

### `main.cpp`
[main.cpp](src/main.cpp) contains driver code that processes user command line arguments, and runs one of two different test functions

### `test_cases.cpp`
[test_cases.cpp](test/test_cases.cpp) contains unit testing code that runs a series of matrix operations and verifies their correctness, using GoogleTest framework

## Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`

## Running Instructions
`.\matrixLib <num_threads> <type> <rows> <cols>`

Where **num_threads** is the number of threads to use for matrix multiplication, **type** is the data type of the 
matrices used for the timed multiplication test, and **rows** and **cols** are the dimensions of the matrix used for
the timed multiplication test.
Possible input values for the **type** argument include:
- `i`: integer
- `d`: double
- `f`: float
- `l`: long
- `s`: short

Example command line input: `./matrixLib 3 i 50 40` will run a timed multiplication test between a randomly generated 50 by 40 integer matrix
and its own transpose using 3 threads. It will also run the same calculation using a single thread, and the computations will be outputted.

Example command line input: `./matrixLib` will run a series of small tests which covers all the included functionalities of the Matrix class.

![alt text](https://github.com/AlexYiningLiu/Matrix-Library/blob/master/img/sample_command_line.PNG?raw=true)

To run the unit tests:
1. `cd build/test/bin`
2. `./TestCases`

The unit test results will be displayed in terminal.

## Current Limitations
- Does not support operations between Matrix objects instantitated using different types,
e.g. an integer Matrix and a double Matrix.
- Matrix representation is in the form of a vector of vectors. This could potentially be further optimized
to only use a 1D data structure along with a stride, which can improve time complexity involved in operations.
