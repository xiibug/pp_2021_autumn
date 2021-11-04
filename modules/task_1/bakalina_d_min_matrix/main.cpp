// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./min_matrix.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, parallel_search_min_in_matrix_with_size_10_x_10) {
    int ProcRank = 0;
    const int n = 10;
    const int m = 10;
    int* mtrx = 0;
    int ph_min = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        mtrx = new int[n * m];
        for (unsigned int i = 0; i < n * m; i++) {
             mtrx[i] = 1;
        }
    }
    ph_min = pharal_search(mtrx, n, m);
    if (ProcRank == 0) {
        delete[] mtrx;
        ASSERT_EQ(ph_min, 1);
    }
}

TEST(Parallel_Operations_MPI, parallel_search_min_in_matrix_with_size_100_x_100) {
    int ProcRank = 0;
    const int n = 100;
    const int m = 100;
    int* mtrx = 0;
    int ph_min = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        mtrx = new int[n * m];
        for (unsigned int i = 0; i < n * m; i++) {
             mtrx[i] = i + 1;
        }
    }
    ph_min = pharal_search(mtrx, n, m);
    if (ProcRank == 0) {
        delete[] mtrx;
        ASSERT_EQ(ph_min, 1);
    }
}

TEST(Parallel_Operations_MPI, parallel_search_works_in_large_matrix) {
    int ProcRank = 0;
    const int n = 1000;
    const int m = 1000;
    int* mtrx = 0;
    int ph_min = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0)
    {
        mtrx = new int[n * m];
        for (unsigned int i = 0; i < n * m; i++) {
             mtrx[i] = i + 1;
        }
    }
    ph_min = pharal_search(mtrx, n, m);
    if (ProcRank == 0) {
        delete[] mtrx;
        ASSERT_EQ(ph_min, 1);
    }
}

TEST(Parallel_Operations_MPI, parallel_search_on_random_matrix_with_small_size) {
    int ProcRank = 0;
    const int n = 10;
    const int m = 10;
    int* mtrx = 0;
    int ph_min = 0, lin_min = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
    create_random_matrix(mtrx, n, m);
    }
    ph_min = pharal_search(mtrx, n, m);
    if (ProcRank == 0) {
        lin_min = lin_search(mtrx, n * m);
        delete[] mtrx;
        ASSERT_EQ(ph_min, lin_min);
	}
}

TEST(Parallel_Operations_MPI, parallel_search_on_random_matrix_with_large_size) {
    int ProcRank = 0;
    const int n = 10000;
    const int m = 10000;
    int* mtrx = 0;
    int ph_min = 0, lin_min = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        create_random_matrix(mtrx, n, m);
    }
    ph_min = pharal_search(mtrx, n, m);
    if (ProcRank == 0) {
        lin_min = lin_search(mtrx, n * m);
        delete[] mtrx;
        ASSERT_EQ(ph_min, lin_min);
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

