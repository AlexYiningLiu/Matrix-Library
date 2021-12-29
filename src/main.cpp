#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <random>
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include "matrix_library.hpp"
#include "identity_matrix.hpp"

using namespace MatrixLibrary;

void testAllCases()
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
    Matrix<int> mat1(inputData1);
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
    auto mat3_assign = Matrix<int>(6, 3);
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

    std::cout << "Test addition." << "\n";
    auto mat_sum = identity + identity;
    mat_sum.printData();

    std::cout << "Test subtraction." << "\n";
    auto mat_diff = identity - identity;
    mat_diff.printData();

    std::cout << "Test identity matrix class." << "\n";
    auto mat_id = IdentityMatrix<int> (3);
    mat_id.printData();

    std::cout << "Test identity matrix transpose." << "\n";
    mat_id.transpose().printData();

    std::cout << "Test identity matrix multiplication." << "\n";
    Matrix<int> mat_id_mult({{2, 9, 4},
                            {0, 0, 2},
                            {0, 1, 1}});
    (mat_id * mat_id_mult).printData();
}

template <typename TData>
void testLargeDimensionMultiplication(const size_t rows, const size_t cols)
{
    // Define parameters to create random uniform distribution
    const TData low_bound = (TData)-100.0;
    const TData high_bound = (TData)100.0;
    std::random_device rd;
    std::mt19937 dre(10);
    std::uniform_real_distribution<double> distribution(low_bound, high_bound);

    std::vector<std::vector<TData>> data(rows, std::vector<TData>(cols));

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    double timeElapsed;

    // Populate data with randomly generated values
    for (size_t i = 0; i < rows; ++i)
    {
        std::generate(data[i].begin(), data[i].end(), [&distribution, &dre]{ return (TData)distribution(dre); });
    }

    // Create Matrix instances, both with identical values
    Matrix<TData> mat1(std::move(data));
    Matrix<TData> mat2;

    if (rows == cols)
    {
        mat2 = mat1;
    }
    else
    {
        mat2 = mat1.transpose();
    }

    startTime = std::chrono::high_resolution_clock::now();
    auto mat3 = std::move(mat1 * mat2);
    timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
    std::cout << "Computation time with user-defined number of threads: " << timeElapsed << " ms" << std::endl;

    // Get baseline time result without multithreading
    setNumThreads(1);
    startTime = std::chrono::high_resolution_clock::now();
    auto mat4 = std::move(mat1 * mat2);
    timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
    std::cout << "Computation time without multithreading: " << timeElapsed << " ms" << std::endl;

    if (rows <= 20 && cols <= 20)
    {
        std::cout << "Matrix 1:" << std::endl;
        mat1.printData();
        std::cout << "Matrix 2:" << std::endl;
        mat2.printData();
        std::cout << "Result:" << std::endl;
        mat3.printData();
    }
    else
    {
        std::cout << "Row and column size exceeded printing current limit of 20, hence, the matrices won't be printed" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    // Define default values for test parameters
    size_t n_threads = 1;
    size_t cols = 3, rows = 3;
    char testDataType = 'a';

    // Whether or not to print messages for Matrix instantiation
    setPrintMemoryInfo(false);

    if (argc == 5)
    {
        try
        {
            n_threads = std::stoi(argv[1]);
            testDataType = *argv[2];
            rows = std::stoi(argv[3]);
            cols = std::stoi(argv[4]);

            if (n_threads <= 0 || cols <= 0 || rows <= 0)
            {
                throw;
            }
        }
        catch (...)
        {
            std::cout << "Arguments are invalid, check README file for correct usage" << std::endl;
            return 0;
        }        
    }
    else
    {
        std::cout << "Using default parameters for tests" << std::endl;
    }
    std::cout << "Will use " << n_threads << " threads for multiplication computation" << std::endl;
    setNumThreads(n_threads);

    switch (testDataType)
    {
    case 'a':
        testAllCases();
        break;
    case 'i':
        testLargeDimensionMultiplication<int>(rows, cols);
        break;
    case 'd':
        testLargeDimensionMultiplication<double>(rows, cols);
        break;
    case 'f':
        testLargeDimensionMultiplication<float>(rows, cols);
        break;
    case 'l':
        testLargeDimensionMultiplication<long>(rows, cols);
        break;
    case 's':
        testLargeDimensionMultiplication<short>(rows, cols);
        break;
    default:
        testAllCases();
        break;
    }

    return 0;
}
