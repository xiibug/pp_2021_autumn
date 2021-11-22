//  Copyright 2021 Kuklin Andrey
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_sum.h"
#include <gtest-mpi-listener.hpp>

TEST(Parrallel_Operations_MPI, Test_sum_with_fix_equal_sizes) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<std::vector<int>> matrix;
    int i = 5, j = 5;

    if (procRank == 0)
        matrix = getRandMatrix(i, j);

    int matSumParal = matrixSumParal(matrix, i, j);

    if (procRank == 0) {
        int matSumSequential = 0;
        for (int sz = 0; sz < i; sz++) {
            matSumSequential += matrixSumSequential(matrix[sz]);
        }
        ASSERT_EQ(matSumSequential, matSumParal);
    }
}

TEST(Parrallel_Operations_MPI, Test_sum_with_fix_different_sizes) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<std::vector<int>> matrix;
    int i = 9, j = 2;

    if (procRank == 0)
        matrix = getRandMatrix(i, j);

    int matSumParal = matrixSumParal(matrix, i, j);

    if (procRank == 0) {
        int matSumSequential = 0;
        for (int sz = 0; sz < i; sz++) {
            matSumSequential += matrixSumSequential(matrix[sz]);
        }
        ASSERT_EQ(matSumSequential, matSumParal);
    }
}

TEST(Parrallel_Operations_MPI, Test_sum_with_rand_sizes) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<std::vector<int>> matrix;
    int i, j;

    srand(time(0));
    i = rand() % 20;
    j = rand() % 20;

    if (procRank == 0)
        matrix = getRandMatrix(i, j);

    int matSumParal = matrixSumParal(matrix, i, j);

    if (procRank == 0) {
        int matSumSequential = 0;
        for (int sz = 0; sz < i; sz++) {
            matSumSequential += matrixSumSequential(matrix[sz]);
        }
        ASSERT_EQ(matSumSequential, matSumParal);
    }
}

TEST(Parrallel_Operations_MPI, Test_sum_sqr_matrix) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<std::vector<int>> matrix;
    int i = 8, j = 8;

    if (procRank == 0)
        matrix = getRandMatrix(i, j);

    int matSumParal = matrixSumParal(matrix, i, j);

    if (procRank == 0) {
        int matSumSequential = 0;
        for (int sz = 0; sz < i; sz++) {
            matSumSequential += matrixSumSequential(matrix[sz]);
        }
        ASSERT_EQ(matSumSequential, matSumParal);
    }
}

TEST(Parrallel_Operations_MPI, Test_sum_sqr_matrix_with_rand_size) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<std::vector<int>> matrix;

    int i, j;
    srand(time(0));
    i = rand() % 20;
    j = i;

    if (procRank == 0) matrix = getRandMatrix(i, j);

    int matSumParal = matrixSumParal(matrix, i, j);

    if (procRank == 0) {
        int matSumSequential = 0;
        for (int sz = 0; sz < i; sz++) {
            matSumSequential += matrixSumSequential(matrix[sz]);
        }
        ASSERT_EQ(matSumSequential, matSumParal);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listener =
        ::testing::UnitTest::GetInstance()->listeners();

    listener.Release(listener.default_result_printer());
    listener.Release(listener.default_xml_generator());

    listener.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
