#include "matrix_library.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace MatrixLibrary;

int main()
{
    std::cout << "Test default constructor." << "\n";
    Matrix<int> mat_default;
    mat_default.printData();

    std::cout << "Test dimensions-only constructor." << "\n";
    auto mat0 = Matrix<float>(2, 4);
    mat0.printData();

    std::cout << "Test constructor." << "\n";
    std::vector<std::vector<int>> inputData1 {{1, 0, 0},
                                            {0, 1, 0},
                                            {0, 0, 1}};
    Matrix<int> mat1 (inputData1);
    mat1.printData();

    std::cout << "Test constructor in a different way." << "\n";
    auto mat2 = Matrix<double>(std::vector<std::vector<double>> {{1.0, 0.0},
                                                                {0.0, 1.5},
                                                                {2.0, 0.0}});
    mat2.printData(1);

    std::cout << "Test copy assignment operator." << "\n";
    auto mat2_assign = Matrix<double>(3, 3);
    mat2_assign = mat2;
    mat2_assign.printData(1);

    std::cout << "Test copy constructor." << "\n";
    auto mat2_copy(mat2);
    mat2_copy.printData(1);

    std::cout << "Test move constructor." << "\n";
    auto mat3(std::move(Matrix<int>(2, 3)));
    mat3.printData();

    std::cout << "Test move assignment operator." << "\n";
    auto mat3_assign = Matrix<int> (6, 3);
    mat3_assign = std::move(mat3);
    mat3_assign.printData();

    std::cout << "Test storing multiplication result in new matrix, where operand datatypes are the same (double)." << "\n";
    Matrix<double> identity({{1.0, 0.0, 0.0},
                            {0.0, 1.0, 0.0},
                            {0.0, 0.0, 1.0}});
    auto mat_prod = identity * mat2;
    mat_prod.printData(1);

    std::cout << "Test storing multiplication result in new matrix, where operand datatypes are the same (short)." << "\n";
    Matrix<short> mat5({{1, 0},
                        {0, 2},
                        {0, 1}});

    Matrix<short> mat6({{2, 1, 2},
                        {2, 1, 3}});
    auto mat_5_6 = mat5 * mat6;
    mat_5_6.printData();

    std::cout << "Test multiplication in-place." << "\n";
    Matrix<short> mat_mod(mat5);
    mat_mod *= mat6;
    mat_mod.printData();

    std::cout << "Test transpose." << "\n";
    auto mat_trans = mat_mod.transpose();
    mat_trans.printData();
}
