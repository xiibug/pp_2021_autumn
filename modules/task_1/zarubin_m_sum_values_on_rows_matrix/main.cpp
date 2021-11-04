// Copyright 2021 Zarubin Mikhail
#include <gtest/gtest.h>
#include <vector>
#include "./sum_values_on_rows_matrix.h"
#include <gtest-mpi-listener.hpp>

TEST(GENERATE_MATRIX, can_generate_random_matrix) {
    std::vector<int> matrix(3 * 3);
    ASSERT_NO_THROW(getRandomMatrix(matrix, 3, 3));
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
        for (int proc = 1; proc < size; proc++) {
            MPI_Send(matrix.data(), static_cast<int>(count_row * count_column),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Status status;
        MPI_Recv(matrix.data(), static_cast<int>(count_row * count_column),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    ASSERT_NO_THROW(getParallelOperations(matrix, count_row, count_column));
}

TEST(PARALLEL_OPERATIONS, correct_work_on_square_matrix) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 2, count_column = 2;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
        for (int proc = 1; proc < size; proc++) {
            MPI_Send(matrix.data(), static_cast<int>(count_row * count_column),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Status status;
        MPI_Recv(matrix.data(), static_cast<int>(count_row * count_column),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_rows_than_columns) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 45, count_column = 120;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
        for (int proc = 1; proc < size; proc++) {
            MPI_Send(matrix.data(), static_cast<int>(count_row * count_column),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Status status;
        MPI_Recv(matrix.data(), static_cast<int>(count_row * count_column),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    std::vector<int> result = getParallelOperations(matrix, count_row, count_column);

    if (rank == 0) {
        std::vector<int> expected_result = getSequentialOperations(matrix, count_row, count_column);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_rectangular_matrix_which_more_columns_than_rows) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type count_row = 120, count_column = 45;
    std::vector<int> matrix(count_row * count_column);

    if (rank == 0) {
        getRandomMatrix(matrix, count_row, count_column);
        for (int proc = 1; proc < size; proc++) {
            MPI_Send(matrix.data(), static_cast<int>(count_row * count_column),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Status status;
        MPI_Recv(matrix.data(), static_cast<int>(count_row * count_column),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
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
