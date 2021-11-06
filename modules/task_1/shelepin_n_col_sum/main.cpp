// Copyright 2021 Shelepin Nikita
#include <gtest/gtest.h>
#include <vector>
#include "./col_sum.h"
#include <gtest-mpi-listener.hpp>

TEST(Columns_sums_MPI, Zero_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 0, cols = 123;

    if (rank == 0) {
        ASSERT_ANY_THROW(randomMatrix(rows, cols));
    }
}

TEST(Columns_sums_MPI, Matrix_3x3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 3, cols = 3;
    int* matrix = nullptr;

    if (rank == 0)
        matrix = randomMatrix(rows, cols);

    int* sum = parallelSum(matrix, rows, cols);

    if (rank == 0) {
        int* reference_sum = sequentialSum(matrix, rows, cols);

        for (int i = 0; i < cols; i++) {
            ASSERT_EQ(reference_sum[i], sum[i]);
        }
    }
}

TEST(Columns_sums_MPI, Matrix_25x50) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 25, cols = 50;
    int* matrix = nullptr;

    if (rank == 0)
        matrix = randomMatrix(rows, cols);

    int* sum = parallelSum(matrix, rows, cols);

    if (rank == 0) {
        int* reference_sum = sequentialSum(matrix, rows, cols);

        for (int i = 0; i < cols; i++) {
            ASSERT_EQ(reference_sum[i], sum[i]);
        }
    }
}

TEST(Columns_sums_MPI, Matrix_50x25) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 50, cols = 25;
    int* matrix = nullptr;

    if (rank == 0)
        matrix = randomMatrix(rows, cols);

    int* sum = parallelSum(matrix, rows, cols);

    if (rank == 0) {
        int* reference_sum = sequentialSum(matrix, rows, cols);

        for (int i = 0; i < cols; i++) {
            ASSERT_EQ(reference_sum[i], sum[i]);
        }
    }
}

TEST(Columns_sums_MPI, Matrix_100x100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 100, cols = 100;
    int* matrix = nullptr;

    if (rank == 0)
        matrix = randomMatrix(rows, cols);

    int* sum = parallelSum(matrix, rows, cols);

    if (rank == 0) {
        int* reference_sum = sequentialSum(matrix, rows, cols);

        for (int i = 0; i < cols; i++) {
            ASSERT_EQ(reference_sum[i], sum[i]);
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    std::srand(std::time(nullptr));

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
