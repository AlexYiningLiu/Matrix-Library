# Matrix-Library
A library of basic matrix operations implemented using only standard library functions. 
Currently supports initialization using the C++ guidelines of the Rule of Five, as well as 
matrix multiplication, addition, subtraction, and transpose operations. The user can choose
to handle matrix multiplication either synchronously or asynchronously using multithreading.

## Current Limitations
- Does not support operations between Matrix objects instantitated using different types,
e.g. an integer Matrix and a double Matrix.
- Matrix representation is in the form of a vector of vectors. This could potentially be further optimized
to only use a 1D data structure along with a stride, which can improve time complexity involved in operations.

## Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`

## Running Instructions
- `.\matrixLib <num_threads> <type> <rows> <cols>`
