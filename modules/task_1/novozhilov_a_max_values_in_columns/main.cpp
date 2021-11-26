// Copyright 2021 Novozhilov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./max_values_in_columns.h"
#include <gtest-mpi-listener.hpp>


TEST(Parallel_Operations_MPI, Test_matrix_one_column) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;

    if (rank == 0) {
        matrix = getRandomMatrix(25, 1);
    }

    std::vector<int> max = maxValuesInColumnsParallel(matrix, 25, 1);

    if (rank == 0) {
        std::vector<int> max1 = maxValuesInColumnsSequential(matrix);
        ASSERT_EQ(max, max1);
    }
}

TEST(Parallel_Operations_MPI, Test_even_number_of_rows) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;

    if (rank == 0) {
        matrix = getRandomMatrix(100, 25);
    }

    std::vector<int> max = maxValuesInColumnsParallel(matrix, 100, 25);

    if (rank == 0) {
        std::vector<int> max1 = maxValuesInColumnsSequential(matrix);
        ASSERT_EQ(max, max1);
    }
}

TEST(Parallel_Operations_MPI, Test_odd_number_of_rows) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;

    if (rank == 0) {
        matrix = getRandomMatrix(125, 25);
    }

    std::vector<int> max = maxValuesInColumnsParallel(matrix, 125, 25);

    if (rank == 0) {
        std::vector<int> max1 = maxValuesInColumnsSequential(matrix);
        ASSERT_EQ(max, max1);
    }
}


TEST(Parallel_Operations_MPI, Test_huge_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;

    if (rank == 0) {
        matrix = getRandomMatrix(1000, 1500);
    }

    std::vector<int> max = maxValuesInColumnsParallel(matrix, 1000, 1500);

    if (rank == 0) {
        std::vector<int> max1 = maxValuesInColumnsSequential(matrix);
        ASSERT_EQ(max, max1);
    }
}

TEST(Parallel_Operations_MPI, Test_square_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;

    if (rank == 0) {
        matrix = getRandomMatrix(100, 100);
    }

    std::vector<int> max = maxValuesInColumnsParallel(matrix, 100, 100);

    if (rank == 0) {
        std::vector<int> max1 = maxValuesInColumnsSequential(matrix);
        ASSERT_EQ(max, max1);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::vector<int> result1;
    std::vector<int> result2;
    MPI_Init(&argc, &argv);
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();
    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
