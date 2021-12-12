#include "matrix_library.hpp"
#include <vector>

using namespace MatrixLibrary;

int main()
{
    std::vector<std::vector<int>> inputData {{1, 0, 0},
                                            {0, 1, 0},
                                            {0, 0, 1}};

    auto testMatrix = Matrix<int>(inputData);

    testMatrix.printData();
}