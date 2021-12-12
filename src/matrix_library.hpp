#ifndef MATRIXLIBRARY_HPP
#define MATRIXLIBRARY_HPP

#include <vector>
#include <iostream>
#include <cassert>

namespace MatrixLibrary
{
    template <typename TData = double>
    class Matrix
    {
    public:
        // Constructor without input data
        Matrix(const size_t rows, const size_t cols): m_rows(rows), m_cols(cols), m_data(cols*rows) {}
        
        // Constructor with input data
        Matrix(const std::vector<std::vector<TData>>& data): 
            m_rows(data.empty() ? 0 : data.size()), m_cols(data.empty() ? 0 : data.front().size()), m_data(data)
        {
            // Assert that the input data is valid
            for (size_t i = 0; i < m_rows; ++i)
            {
                assert(m_data[i].size() == m_cols);
            }
        }

        // Prints the stored matrix's data
		void printData() const
		{
            for (size_t i = 0; i < m_rows; ++i)
            {

                for (size_t j = 0; j < m_cols; ++j)
                {
                    std::cout << m_data[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

    private:
        std::vector<std::vector<TData>> m_data;
        size_t m_rows;
        size_t m_cols;
    };
} // end namespace MatrixLibrary

#endif // #ifndef NEOMATRIX_HPP