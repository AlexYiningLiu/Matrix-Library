/**
 * @file identity_matrix.hpp
 * @author Alex Liu (alex.liuyining@outlook.com)
 * @brief Identity matrix class, derived from Matrix class
 * @date 2021-12
 */

#ifndef IDENTITY_MATRIX_HPP
#define IDENTITY_MATRIX_HPP

#include <stdexcept>
#include <iostream>
#include "matrix_library.hpp"

namespace MatrixLibrary
{
    template <typename TData>
    class IdentityMatrix : public Matrix<TData>
    {
    public:
        /**
         * The only constructor, takes a single dimensional number
         *  @param size
         */
        IdentityMatrix (const size_t size) : Matrix<TData> (size, size)
        {
            if (size <= 0)
            {
                throw std::invalid_argument("Dimension must be positive integer");
            }

            for (size_t i = 0; i < size; ++i)
            {
                this->m_data[i][i] = (TData) 1.0;
            }

            if (printMemoryInfo)
            {
                std::cout << "Identity Dimensions-only Constructor called" << std::endl;
            }
        }

        Matrix<TData> operator*(const Matrix<TData> &mat) const override
        {
            std::cout << "Overriden function * called!" << "\n";
            Matrix<TData> r(mat);
            return r;
        }

        Matrix<TData> transpose() const override
        {
            std::cout << "Overriden function transpose called!" << "\n";
            Matrix<TData> r(*this);
            return r;
        }
    };
} // end namespace MatrixLibrary

#endif // #ifndef IDENTITY_MATRIX_HPP
