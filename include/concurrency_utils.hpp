/**
 * @file concurrency_utils.hpp
 * @author Alex Liu (alex.liuyining@outlook.com)
 * @brief Utiliy functions that implement multithreaded calculations
 * @date 2021-12
 */

#ifndef CONCURRENCY_UTILS_HPP
#define CONCURRENCY_UTILS_HPP

#include <thread>
#include <future>
#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>

namespace MatrixLibrary
{
    // Mutex used to protect cout for all threads started by multiplyMatricesAsync
    static std::mutex mtx_static;

    /**
     * Compute certain elements of the multiplication result based on given parameters 
     * 
     * @tparam TData 
     * @param result 
     * @param starting_row 
     * @param rows_per_thread 
     * @param data1 
     * @param data2
     * @param cols1
     * @param cols2
     */
    template <typename TData>
    void computeGivenRows(std::vector<std::vector<TData>> &result, const size_t starting_row, const size_t rows_per_thread, 
        const std::vector<std::vector<TData>> &data1, const std::vector<std::vector<TData>> &data2, size_t cols1, size_t cols2)
    {
        std::unique_lock<std::mutex> uLock(mtx_static, std::defer_lock);

        const size_t ending_row = starting_row + rows_per_thread;
        for (size_t i = starting_row; i < ending_row; ++i)
        {
            for (size_t j = 0; j < cols2; ++j)
            {
                for (size_t k = 0; k < cols1; ++k)
                {
                    result[i][j] += data1[i][k] * data2[k][j];
                }
            }
        }
        uLock.lock();
        // std::cout << "Row " << ending_row << " finished computing" << "\n";
    }

    /**
     * Employs std::async to achieve multithreaded computation of matrix multiplication
     * 
     * @tparam TData 
     * @param result Vector of vectors holding the final computation result
     * @param data1 Vector of vectors representing the first operand
     * @param data2 Vector of vectors representing the second operand
     * @param n_threads The number of threads to use for the computation
     */
    template <typename TData>
    void multiplyMatricesAsync(std::vector<std::vector<TData>> &result, const std::vector<std::vector<TData>>& data1, const std::vector<std::vector<TData>>& data2, size_t n_threads)
    {
        size_t final_rows = data1.size();
        size_t final_cols = data2.front().size();
        size_t data1_cols = data1.front().size();

        // If chosen n_threads is greater than number of rows available, create one thread per row
        n_threads = (n_threads > final_rows) ? final_rows : n_threads;

        // Calculate the workload in terms of the number of rows in the final result's computation that is assigned to each thread
        const size_t rows_per_thread = final_rows / n_threads;
        const size_t remaining_rows = final_rows % n_threads;
        size_t starting_row = 0;

        // Container for the threads used for computation
        std::vector<std::future<void>> futures;
        for (size_t i = 0; i < n_threads-1; ++i)
        {
            futures.emplace_back(
                std::async(std::launch::async, computeGivenRows<TData>, std::ref(result), starting_row, rows_per_thread, std::ref(data1), std::ref(data2), data1_cols, final_cols));
            starting_row += rows_per_thread;
        }

        // Compute the result for the last thread separately, as it may need to handle larger number of rows
        futures.emplace_back(
            std::async(std::launch::async, computeGivenRows<TData>, std::ref(result), starting_row, rows_per_thread + remaining_rows, std::ref(data1), std::ref(data2), data1_cols, final_cols));
        
        // Wait for all threads to finish work
        std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr)
        {
            ftr.wait();
        });
    }
} // end namespace MatrixLibrary

#endif // #ifndef CONCURRENCY_UTILS_HPP
