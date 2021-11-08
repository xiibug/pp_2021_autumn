// Copyright 2021 Denisova Julia
#include <iostream>
#include <gtest/gtest.h>
#include "../../../modules/task_1/denisova_max_column_matrix/max_column_matrix.h"
#include <gtest-mpi-listener.hpp>

TEST(func_max_column_matrix, check_with_static_matrix) {
    int str = 5;
    int col = 5;
    int flag = 0;
    int procRank = 0;
    int mas[5 * 5] = { 1, 2, 3, 4, 5,
                       6, 7, 8, 9, 1,
                       2, 3, 4, 5, 6,
                       7, 8, 9, 1, 2,
                       3, 4, 5, 6, 7 };
    int* bigmas = nullptr;
    int* resbuf = nullptr;
    int proverka[5] = { 7,8,9,9,7 };
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
    bigmas = new int[str * col];
        resbuf = new int[col];
        swap_matrix(str, col, mas, bigmas);
    }
    max_from_columns(str, col, bigmas, resbuf);
    if (procRank == 0) {
    for (int i = 0; i < col; i++) {
         if (proverka[i] != resbuf[i]) {
            flag = 1;
         }
    }
    delete[] bigmas;
    delete[] resbuf;
    ASSERT_EQ(flag, 0);
    }
}

TEST(func_max_column_matrix, check_with_random_matrix) {
    int str = 5;
    int col = 5;
    int flag = 0;
    int procRank = 0;
    int* bigmas = 0;
    int* resbuf = 0;
    int mas[5 * 5];
    int proverka[5];
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        bigmas = new int[str * col];
        resbuf = new int[col];
        swap_matrix(str, col, mas, bigmas);
        random_matrix(str, col, mas);
        findmax(bigmas, col, str, proverka);
    }
    max_from_columns(str, col, bigmas, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i])
               flag = 1;
        }
        delete[] bigmas;
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

TEST(func_max_column_matrix, check_with_static_matrix_with_findmax) {
    int str = 5;
    int col = 5;
    int flag = 0;
    int procRank = 0;
    int* bigmas = 0;
    int* resbuf = 0;
    int mas[5 * 5] = { 1, 2, 3, 4, 5,
                       6, 7, 8, 9, 1,
                       2, 3, 4, 5, 6,
                       7, 8, 9, 1, 2,
                       3, 4, 5, 6, 7 };
    int proverka[5];
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        bigmas = new int[str * col];
        resbuf = new int[col];
        swap_matrix(str, col, mas, bigmas);
        findmax(bigmas, col, str, proverka);
    }
    max_from_columns(str, col, bigmas, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
                flag = 1;
            }
        }
        delete[] bigmas;
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

TEST(func_max_column_matrix, check_with_negative_matrix) {
    int str = 5;
    int col = 5;
    int flag = 0;
    int procRank = 0;
    int* bigmas = 0;
    int* resbuf = 0;
    int mas[5 * 5] = { -1, -2, -3, -4, -5,
                       -6, -7, -8, -9, -1,
                       -2, -3, -4, -5, -6,
                       -7, -8, -9, -1, -2,
                       -3, -4, -5, -6, -7 };
    int proverka[5];
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        bigmas = new int[str * col];
        resbuf = new int[col];
        swap_matrix(str, col, mas, bigmas);
        findmax(bigmas, col, str, proverka);
    }
    max_from_columns(str, col, bigmas, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
                flag = 1;
            }
        }
        delete[] bigmas;
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

TEST(func_max_column_matrix, check_with_negative_positive_matrix) {
    int str = 5;
    int col = 5;
    int flag = 0;
    int procRank = 0;
    int* bigmas = 0;
    int* resbuf = 0;
    int mas[5 * 5] = { 1, 2,-3, 4, -5,
                      -6, -7, -8, -9, 1,
                       2, -3, 0, -5, -6,
                       0, -8, 9, -1, -2,
                      -3, -4, 5, -6, 7 };
    int proverka[5];
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        bigmas = new int[str * col];
        resbuf = new int[col];
        swap_matrix(str, col, mas, bigmas);
        findmax(bigmas, col, str, proverka);
    }
    max_from_columns(str, col, bigmas, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
                flag = 1;
            }
        }
        delete[] bigmas;
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);  // check for MPI_SUCCESS?

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
