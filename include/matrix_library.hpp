/**
 * @file matrix_library.hpp
 * @author Alex Liu (alex.liuyining@outlook.com)
 * @brief A header-only library of matrix arithmetic operations using standard library functions
 * @date 2021-12
 */

#ifndef MATRIX_LIBRARY_HPP
#define MATRIX_LIBRARY_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include "concurrency_utils.hpp"

namespace MatrixLibrary
{
    // Number of threads to use for matrix computations, set as a static variable of the namespace
    static size_t n_threads = 1;

    template <typename TData>
    class Matrix
    {
    public:
        /**
         * Default constructor.
         */
        Matrix() : m_rows(0), m_cols(0)
        {
            std::cout << "Default Constructor called" << std::endl;
        }

        /**
         * Constructor without input data available. A matrix of zeros of size rows by cols will be instantiated.
         *  @param rows
         *  @param cols
         */
        Matrix(const size_t rows, const size_t cols): m_rows(rows), m_cols(cols), m_data(rows, std::vector<TData>(cols))
        {
            if (rows <= 0 || cols <= 0)
            {
                throw std::invalid_argument("Row and column must be positive integers");
            }
            std::cout << "Dimensions-only Constructor called" << std::endl;
        }
        
        /**
         * Constructor with input data available.
         *  @param data Vector of vectors holding the input data
         */
        Matrix(const std::vector<std::vector<TData>>& data): 
            m_rows(data.size()), m_cols(data.front().size()), m_data(data)
        {
            std::cout << "Constructor with data called" << std::endl;
            // Assert that the input data type is numeric
            static_assert(std::is_arithmetic<TData>::value, "TData must be numeric");

            // Assert that the input data is valid in terms of dimensions
            assert(m_rows > 0 && m_cols > 0 && "Matrix must have at least 1 row");
            for (size_t i = 0; i < m_rows; ++i)
            {
                assert(m_data[i].size() == m_cols && "Each row must have the same size");
            }
        }

        /**
         * Copy constructor.
         * 
         */
        Matrix(const Matrix &source): m_rows(source.m_rows), m_cols(source.m_cols), m_data(source.m_data)
        {
            std::cout << "Copy Constructor called" << std::endl;
        }

        /**
         * Move constructor.
         * 
         */
        Matrix(Matrix &&source): m_rows(source.m_rows), m_cols(source.m_cols)
        {
            std::cout << "Move Constructor called" << std::endl;
            m_data = std::move(source.m_data);
        }

        /**
         * Copy assignment operator.
         * 
         */
        Matrix &operator=(const Matrix &source)
        {
            std::cout << "Copy Assignment Operator called" << std::endl;
            m_rows = source.m_rows;
            m_cols = source.m_cols;
            m_data = source.m_data;
            return *this;
        }

        /**
         * Move assignment operator.
         * 
         */
        Matrix &operator=(Matrix &&source)
        {            
            std::cout << "Move assignment operator called" << std::endl;
            if (this == &source)
            {
                return *this;
            }
            m_rows = source.m_rows;
            m_cols = source.m_cols;
            m_data = std::move(source.m_data);
            return *this;
        }

        /**
         * Overloaded * operator, each Matrix operand must have the same datatype, or else the compiler will fail.
         * @param mat The other Matrix to multiply with
         * @return A new Matrix holding the result
         */
        virtual Matrix operator*(const Matrix &mat) const
        {
            assert(m_cols == mat.m_rows && "First matrix's cols must match second matrix's rows");

            std::vector<std::vector<TData>> r_data(m_rows, std::vector<TData>(mat.m_cols));

            // Serial computation, no multithreading
            if (n_threads == 1)
            {
                std::cout << "Multiplying without multithreading" << "\n";
                for (size_t i = 0; i < m_rows; ++i)
                {
                    for (size_t j = 0; j < mat.m_cols; ++j)
                    {
                        for (size_t k = 0; k < m_cols; ++k)
                        {
                            r_data[i][j] += m_data[i][k] * mat.m_data[k][j];
                        }
                    }
                }
            }
            // Employ multithreaded computation
            else
            {
                std::cout << "Multiplying with multithreading" << "\n";
                multiplyMatricesAsync(r_data, m_data, mat.m_data, n_threads);
            }

            Matrix<TData> r(r_data);
            return r;
        }

        /**
         * Overloaded *= operator, each Matrix operand must have the same datatype, or else the compiler will fail.
         * @param mat The other Matrix to multiply with
         */
        Matrix &operator*=(const Matrix &mat)
        {
            *this = std::move((*this) * mat);
            return *this;
        }

        /**
        * Overloaded + operator, each Matrix operand must have the same datatype, or else the compiler will fail.
        * @param mat The other Matrix to add with
        * @return A new Matrix holding the result
        */
        Matrix operator+(const Matrix& mat) const
        {
            assert(m_cols == mat.m_cols && m_rows == mat.m_rows && "Two matrices must have the same dimensions");

            std::vector<std::vector<TData>> r_data(m_rows, std::vector<TData>(m_cols));

            for (size_t i = 0; i < m_rows; ++i)
            {
                for (size_t j = 0; j < mat.m_cols; ++j)
                {                    
                    r_data[i][j] += (m_data[i][j] + mat.m_data[i][j]);
                }
            }
            Matrix<TData> r(r_data);
            return r;
        }

        /**
         * Overloaded += operator, each Matrix operand must have the same datatype, or else the compiler will fail.
         * @param mat The other Matrix to add with
         */
        Matrix& operator+=(const Matrix& mat)
        {
            *this = std::move((*this) + mat);
            return *this;
        }

        /**
        * Overloaded - operator, each Matrix operand must have the same datatype, or else the compiler will fail.
        * @param mat The other Matrix that will be subtracted from the current
        * @return A new Matrix holding the result
        */
        Matrix operator-(const Matrix& mat) const
        {
            assert(m_cols == mat.m_cols && m_rows == mat.m_rows && "Two matrices must have the same dimensions");

            std::vector<std::vector<TData>> r_data(m_rows, std::vector<TData>(m_cols));

            for (size_t i = 0; i < m_rows; ++i)
            {
                for (size_t j = 0; j < mat.m_cols; ++j)
                {
                    r_data[i][j] += (m_data[i][j] - mat.m_data[i][j]);
                }
            }
            Matrix<TData> r(r_data);
            return r;
        }

        /**
         * Overloaded -= operator, each Matrix operand must have the same datatype, or else the compiler will fail.
         * @param mat The other Matrix to subtract with
         */
        Matrix& operator-=(const Matrix& mat)
        {
            *this = std::move((*this) - mat);
            return *this;
        }

        /**
         * Instantiates a new Matrix which contains the result of transposing the current Matrix.
         * @return A new matrix holding the transpose
         */
        virtual Matrix transpose() const
        {
            std::vector<std::vector<TData>> r_data(m_cols, std::vector<TData>(m_rows));
            
            for (size_t i = 0; i < m_rows; ++i)
            {
                for (size_t j = 0; j < m_cols; ++j)
                {
                    r_data[j][i] = m_data[i][j];
                }
            }
            Matrix<TData> r(r_data);
            return r;            
        }

        /**
         * Prints the data stored in the matrix.
         *
         * @param p the number of decimals to display in case the data is floating point, default p = 2
         * @return void
         */
		void printData(int p = 2) const
		{
            for (size_t i = 0; i < m_rows; ++i)
            {
                for (size_t j = 0; j < m_cols; ++j)
                {
                    std::cout << std::fixed << std::setprecision(p) << m_data[i][j] << " ";
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
        }

        /**
         * Getter for the dimensions of the matrix, returned as a pair in the form of rows, cols
         * 
         * @return std::pair <size_t, size_t>
         */
        std::pair<size_t, size_t> getDimensions() const
        {
            std::pair<size_t, size_t> dim;
            dim.first = m_rows;
            dim.second = m_cols;
            return dim;
        }

    protected:
        std::vector<std::vector<TData>> m_data;
        size_t m_rows;
        size_t m_cols;
    };

    static void setNumThreads(const size_t n_threads_)
    {
        n_threads = n_threads_;
    }

    template class Matrix<int>;
    template class Matrix<double>;
	template class Matrix<float>;
	template class Matrix<long>;
    template class Matrix<short>;
} // end namespace MatrixLibrary

#endif // #ifndef MATRIX_LIBRARY_HPP
