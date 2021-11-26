// Copyright 2021 Lakhov Kirill
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_col_sum.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Square_Matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;
    const int rows = 12;
    const int cols = 12;

    if (rank == 0) {
        matrix = getRandomMatrix(rows, cols);
    }

    int global_sum = parallelCalc(matrix, rows, cols);

    if (rank == 0) {
        int reference_sum = sequentialCalc(matrix, rows, cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Parallel_Operations_MPI, Test_Rectangular_Matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;
    const int rows = 12;
    const int cols = 7;

    if (rank == 0) {
        matrix = getRandomMatrix(rows, cols);
    }

    int global_sum = parallelCalc(matrix, rows, cols);

    if (rank == 0) {
        int reference_sum = sequentialCalc(matrix, rows, cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Parallel_Operations_MPI, Test_Rectangular_Matrix_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;
    const int rows = 8;
    const int cols = 15;

    if (rank == 0) {
        matrix = getRandomMatrix(rows, cols);
    }

    int global_sum = parallelCalc(matrix, rows, cols);

    if (rank == 0) {
        int reference_sum = sequentialCalc(matrix, rows, cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Parallel_Operations_MPI, Test_Large_Matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;
    const int rows = 100;
    const int cols = 88;

    if (rank == 0) {
        matrix = getRandomMatrix(rows, cols);
    }

    int global_sum = parallelCalc(matrix, rows, cols);

    if (rank == 0) {
        int reference_sum = sequentialCalc(matrix, rows, cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Parallel_Operations_MPI, Test_Large_Matrix_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> matrix;
    const int rows = 77;
    const int cols = 100;

    if (rank == 0) {
        matrix = getRandomMatrix(rows, cols);
    }

    int global_sum = parallelCalc(matrix, rows, cols);

    if (rank == 0) {
        int reference_sum = sequentialCalc(matrix, rows, cols);
        ASSERT_EQ(reference_sum, global_sum);
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
