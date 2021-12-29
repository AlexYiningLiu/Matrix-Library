# Matrix-Library

Capstone project for the [Udacity C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

##### Table of Contents 
- [Description](#description)
- [Project Files](#project-files)
- [Build Instructions](#build-instructions)
- [Running Instructions](#running-instructions)
- [Current Limitations](#current-limitations)
- [Rubric Points](#rubric-points)

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

## Current Limitations
- Does not support operations between Matrix objects instantitated using different types,
e.g. an integer Matrix and a double Matrix.
- Matrix representation is in the form of a vector of vectors. This could potentially be further optimized
to only use a 1D data structure along with a stride, which can improve time complexity involved in operations.

## Rubric Points
The points belowed were addressed in this project.

### Loop, Functions, I/O
- The project demonstrates an understanding of C++ functions and control structures.
- The project accepts user input and processes the input (see the `main` function in `main.cpp`)

### Object Oriented Programming
- The project uses Object Oriented Programming techniques.
- Classes use appropriate access specifiers for class members (see `matrix_library.hpp and` `identity_matrix.hpp`).
- Class constructors utilize member initialization lists (see each constructor of `matrix_library.hpp`).
- Classes abstract implementation details from their interfaces.
- Classes encapsulate behavior.
- Classes follow an appropriate inheritance hierarchy (see inheritance implementation in class definition in `identity_matrix.hpp`).
- Templates generalize functions in the project (the entirety of the library is built using templates).
- Derived class functions override virtual base class functions (see lines 39 and 46 in `identity_matrix.hpp`).
- Overloaded functions allow the same function to operate on different parameters (see overloading of arithmetic operators, e.g. line 150 in `matrix_library.hpp`).

### Memory management
- The project makes use of references in function declarations.
- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
- The project follows the Rule of 5 (see implementation of Rule of 5 for the Matrix class in `matrix_library.hpp`).
- The project uses move semantics to move data, instead of copying it, where possible (see lines 126, 139, and 146 in `main.cpp`).

### Concurrency
- The project uses multithreading (see `concurrency_utils.hpp`).
- A promise and future is used in the project (a promise isn't used, but futures are used starting in line 81 of `concurrency_utils.hpp`).
- A mutex or lock is used in the project (see line 39 in `concurrency_utils.hpp`).
