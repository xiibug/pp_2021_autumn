// Copyright 2021 Boyarskov Anton
#include <gtest/gtest.h>
#include "./matrix_max.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Max_MPI, Size_2x3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int n = 2, m = 3;

    if (rank == 0) {
        matrix = getRandomMatrix(n, m);
    }

    int global_max = getParallelMax(matrix, n, m);

    if (rank == 0) {
        int reference_max = getSequentialMax(matrix, n, m);
        ASSERT_EQ(reference_max, global_max);
    }
}

TEST(Parallel_Max_MPI, Size_5x5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int n = 5, m = 5;

    if (rank == 0) {
        matrix = getRandomMatrix(n, m);
    }

    int global_max = getParallelMax(matrix, n, m);

    if (rank == 0) {
        int reference_max = getSequentialMax(matrix, n, m);
        ASSERT_EQ(reference_max, global_max);
    }
}

TEST(Parallel_Max_MPI, Size_10x15) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int n = 10, m = 15;

    if (rank == 0) {
        matrix = getRandomMatrix(n, m);
    }

    int global_max = getParallelMax(matrix, n, m);

    if (rank == 0) {
        int reference_max = getSequentialMax(matrix, n, m);
        ASSERT_EQ(reference_max, global_max);
    }
}

TEST(Parallel_Max_MPI, Size_20x30) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int n = 2, m = 3;

    if (rank == 0) {
        matrix = getRandomMatrix(n, m);
    }

    int global_max = getParallelMax(matrix, n, m);

    if (rank == 0) {
        int reference_max = getSequentialMax(matrix, n, m);
        ASSERT_EQ(reference_max, global_max);
    }
}

TEST(Parallel_Max_MPI, Size_50x50) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrix = nullptr;
    const int n = 2, m = 3;

    if (rank == 0) {
        matrix = getRandomMatrix(n, m);
    }

    int global_max = getParallelMax(matrix, n, m);

    if (rank == 0) {
        int reference_max = getSequentialMax(matrix, n, m);
        ASSERT_EQ(reference_max, global_max);
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
