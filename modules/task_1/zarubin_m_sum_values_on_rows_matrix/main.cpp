// Copyright 2021 Zarubin Mikhail
#include <gtest/gtest.h>
#include <vector>
#include "./sum_values_on_rows_matrix.h"
#include <gtest-mpi-listener.hpp>

TEST(GENERATE_MATRIX, can_generate_random_matrix) {
    std::vector<int> matrix(3 * 3);
    ASSERT_NO_THROW(getRandomMatrix(matrix, 3, 3));
}

TEST(TRANSPOSE_MATRIX, can_transpose_matrix) {
    std::vector<int> matrix(3 * 3);
    ASSERT_NO_THROW(transposeMatrix(matrix, 3, 3));
}

TEST(TRANSPOSE_MATRIX, correct_work_on_square_matrix) {
    std::vector<int> matrix{ 1, 2, 3,
                             7, 4, 8,
                             3, 5, 6 };
    std::vector<int> expected_result{ 1, 7, 3,
                                      2, 4, 5,
                                      3, 8, 6 };
    std::vector<int> result = transposeMatrix(matrix, 3, 3);
    ASSERT_EQ(result, expected_result);
}

TEST(TRANSPOSE_MATRIX, correct_work_on_rectangular_matrix_which_more_rows_than_columns) {
    std::vector<int> matrix{ 1, 2,
                             3, 7,
                             4, 8,
                             3, 5 };
    std::vector<int> expected_result{ 1, 3, 4, 3,
                                      2, 7, 8, 5 };
    std::vector<int> result = transposeMatrix(matrix, 4, 2);
    ASSERT_EQ(result, expected_result);
}

TEST(TRANSPOSE_MATRIX, correct_work_on_rectangular_matrix_which_more_columns_than_rows) {
    std::vector<int> matrix{ 1, 2, 3, 7,
                             4, 8, 3, 5 };
    std::vector<int> expected_result{ 1, 4,
                                      2, 8,
                                      3, 3,
                                      7, 5 };
    std::vector<int> result = transposeMatrix(matrix, 2, 4);
    ASSERT_EQ(result, expected_result);
}

TEST(SEQUENTIAL_OPERATIONS, can_run_sequential_operations) {
    std::vector<int> matrix(3 * 3);
    getRandomMatrix(matrix, 3, 3);
    ASSERT_NO_THROW(getSequentialOperations(matrix, 3, 3));
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_on_square_matrix) {
    std::vector<int> matrix{ 1, 2, 3,
                             7, 4, 8,
                             3, 5, 6 };
    std::vector<int> expected_result{ 6,19,14 };
    std::vector<int> result = getSequentialOperations(matrix, 3, 3);
    ASSERT_EQ(result, expected_result);
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_rows_than_columns) {
    std::vector<int> matrix{ 1, 2,
                             3, 7,
                             4, 8,
                             3, 5 };
    std::vector<int> expected_result{ 3, 10, 12, 8 };
    std::vector<int> result = getSequentialOperations(matrix, 4, 2);
    ASSERT_EQ(result, expected_result);
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_columns_than_rows) {
    std::vector<int> matrix{ 1, 2, 3, 7,
                             4, 8, 3, 5 };
    std::vector<int> expected_result{ 13, 20 };
    std::vector<int> result = getSequentialOperations(matrix, 2, 4);
    ASSERT_EQ(result, expected_result);
}

TEST(PARALLEL_OPERATIONS, can_run_parallel_operations) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 120, count_column = 120;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
    }

    ASSERT_NO_THROW(getParallelOperations(matrix, count_row, count_column));
}

TEST(PARALLEL_OPERATIONS, correct_work_on_square_matrix_var_1) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 120, count_column = 120;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_square_matrix_var_2) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 123, count_column = 123;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_rows_than_columns_var_1) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 120, count_column = 45;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_rows_than_columns_var_2) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 87, count_column = 23;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_columns_than_rows_var_1) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 45, count_column = 120;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_columns_than_rows_var_2) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 23, count_column = 87;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
