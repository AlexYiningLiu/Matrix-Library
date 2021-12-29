#include <gtest/gtest.h>
#include <vector>
#include "matrix_library.hpp"
#include "identity_matrix.hpp"
#include "concurrency_utils.hpp"

using namespace MatrixLibrary;

class MatrixTest : public ::testing::Test 
{
    protected:
    void SetUp() override 
    {
        setPrintMemoryInfo(false);
        setNumThreads(2);
    }    
};

TEST_F(MatrixTest, TestConstructorData)
{
    auto mat = Matrix<double>(std::vector<std::vector<double>> {{1.0, 0.0},
                                                                {0.0, 1.5},
                                                                {2.0, 0.0}});
    std::vector<std::vector<double>> data_compare {{1.0, 0.0},
                                                   {0.0, 1.5},
                                                   {2.0, 0.0}};
    
    std::vector<std::vector<double>> data_mat = mat.getData();
    EXPECT_EQ(data_mat, data_compare);
}

TEST_F(MatrixTest, TestIdentityMultiplication)
{
    auto mat_id = IdentityMatrix<int> (3);
    Matrix<int> mat_id_mult({{2, 9, 4, 5},
                             {0, 0, 2, -13},
                             {0, 1, 1, 19},
                             {11, 0, 55, -3}});

    EXPECT_EQ((mat_id * mat_id_mult).getData(), mat_id_mult.getData());
}

TEST_F(MatrixTest, TestMultiplication)
{
    Matrix<short> mat1({{1, 0},
                        {0, 2},
                        {0, 1}});
    Matrix<short> mat2({{2, 1, 2},
                        {2, 1, 3}});
    std::vector<std::vector<short>> expected_result {{2, 1, 2},
                                                     {4, 2, 6},
                                                     {2, 1, 3}};

    auto mat_prod = mat1 * mat2;
    EXPECT_EQ(mat_prod.getData(), expected_result);
}

TEST_F(MatrixTest, TestMultiplicationInPlace)
{
    Matrix<short> mat1({{1, 0},
                        {0, 2},
                        {0, 1}});
    Matrix<short> mat2({{2, 1, 2},
                        {2, 1, 3}});
    std::vector<std::vector<short>> expected_result {{2, 1, 2},
                                                     {4, 2, 6},
                                                     {2, 1, 3}};

    mat1 *= mat2;
    EXPECT_EQ(mat1.getData(), expected_result);
}

TEST_F(MatrixTest, TestAddition)
{
    Matrix<short> mat1({{1, 0},
                        {0, 2},
                        {0, 1}});
    Matrix<short> mat2({{2, 1},
                        {2, 1},
                        {0, 6}});
    std::vector<std::vector<short>> expected_result {{3, 1},
                                                     {2, 3},
                                                     {0, 7}};

    EXPECT_EQ((mat1 + mat2).getData(), expected_result);
}

TEST_F(MatrixTest, TestAdditionInPlace)
{
    Matrix<short> mat1({{1, 0},
                        {0, 2},
                        {0, 1}});
    Matrix<short> mat2({{2, 1},
                        {2, 1},
                        {0, 6}});
    std::vector<std::vector<short>> expected_result {{3, 1},
                                                     {2, 3},
                                                     {0, 7}};

    mat1 += mat2;
    EXPECT_EQ(mat1.getData(), expected_result);
}

TEST_F(MatrixTest, TestSubtraction)
{
    Matrix<short> mat1({{1, 0},
                        {0, 2},
                        {0, 1}});
    Matrix<short> mat2({{2, 1},
                        {2, 1},
                        {0, 6}});
    std::vector<std::vector<short>> expected_result {{-1, -1},
                                                     {-2, 1},
                                                     {0, -5}};

    EXPECT_EQ((mat1 - mat2).getData(), expected_result);
}

TEST_F(MatrixTest, TestSubtractionInPlace)
{
    Matrix<short> mat1({{1, 0},
                        {0, 2},
                        {0, 1}});
    Matrix<short> mat2({{2, 1},
                        {2, 1},
                        {0, 6}});
    std::vector<std::vector<short>> expected_result {{-1, -1},
                                                     {-2, 1},
                                                     {0, -5}};

    mat1 -= mat2;
    EXPECT_EQ(mat1.getData(), expected_result);
}

TEST_F(MatrixTest, TestTranspose)
{
    Matrix<short> mat1({{1, 0},
                        {0, 2},
                        {0, 1}});
    std::vector<std::vector<short>> expected_result {{1, 0, 0},
                                                     {0, 2, 1}};

    EXPECT_EQ(mat1.transpose().getData(), expected_result);
}