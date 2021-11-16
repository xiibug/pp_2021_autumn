// Copyright 2021 Vorobyova Anna
#include <gtest/gtest.h>
#include "./matrix_sum.h"
#include <gtest-mpi-listener.hpp>

TEST(Matrix_Sum_MPI, Matrix_3x4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int rows = 3, cols = 4;

    if (rank == 0) {
        matrix = getRandomMatrix(rows * cols);
    }

    int global_sum = getParallelSum(matrix, rows * cols);

    if (rank == 0) {
        int reference_sum = getSequentialSum(matrix, rows * cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Matrix_Sum_MPI, Matrix_5x10) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int rows = 5, cols = 10;

    if (rank == 0) {
        matrix = getRandomMatrix(rows * cols);
    }

    int global_sum = getParallelSum(matrix, rows * cols);

    if (rank == 0) {
        int reference_sum = getSequentialSum(matrix, rows * cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Matrix_Sum_MPI, Matrix_10x20) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int rows = 10, cols = 20;

    if (rank == 0) {
        matrix = getRandomMatrix(rows * cols);
    }

    int global_sum = getParallelSum(matrix, rows * cols);

    if (rank == 0) {
        int reference_sum = getSequentialSum(matrix, rows * cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Matrix_Sum_MPI, Matrix_30x40) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int rows = 30, cols = 40;

    if (rank == 0) {
        matrix = getRandomMatrix(rows * cols);
    }

    int global_sum = getParallelSum(matrix, rows * cols);

    if (rank == 0) {
        int reference_sum = getSequentialSum(matrix, rows * cols);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Matrix_Sum_MPI, Matrix_50x50) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int rows = 50, cols = 50;

    if (rank == 0) {
        matrix = getRandomMatrix(rows * cols);
    }

    int global_sum = getParallelSum(matrix, rows * cols);

    if (rank == 0) {
        int reference_sum = getSequentialSum(matrix, rows * cols);
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
