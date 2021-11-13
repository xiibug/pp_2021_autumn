// Copyright 2021 Denisova Julia

#include <gtest/gtest.h>
#include "../../../modules/task_2/denisova_ribbon_horizont_scheme/ribbon_horizont_scheme.h"
#include <gtest-mpi-listener.hpp>

TEST(func_pharal_alg, check_with_static_matrix_and_vector) {
    int str = 3;
    int col = 3;
    int procRank = 0;
    int flag = 0;
    int matr[3 * 3] = { 1, 1, 1,
                       2, 2, 2,
                       3, 3, 3 };
    int vector[3] = { 1, 1, 1 };
    int* resbuf = nullptr;
    int proverka[3] = { 3, 6, 9 };
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
       resbuf = new int[str];
    }
    pharal_alg(str, col, matr, vector, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
                flag = 1;
            }
        }
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

TEST(func_pharal_alg, compare_pharal_and_lin_alg) {
    int str = 3;
    int col = 3;
    int procRank = 0;
    int flag = 0;
    int matr[3 * 3] = { 1, 1, 1,
                        2, 2, 2,
                        3, 3, 3 };
    int vector[3] = { 1, 1, 1 };
    int* resbuf = nullptr;
    int proverka[3];
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        resbuf = new int[str];
        multipl(matr, vector, str, col, proverka);
    }
    pharal_alg(str, col, matr, vector, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
               flag = 1;
            }
        }
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

TEST(func_pharal_alg, check_with_negative_matrix) {
    int str = 3;
    int col = 3;
    int procRank = 0;
    int flag = 0;
    int matr[3 * 3] = { -1, -1, -1,
                        -2, -2, -2,
                        -3, -3, -3 };
    int vector[3] = { 1, 1, 1 };
    int* resbuf = nullptr;
    int proverka[3] = { -3, -6, -9 };
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
       resbuf = new int[str];
    }
    pharal_alg(str, col, matr, vector, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
               flag = 1;
            }
        }
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

TEST(func_pharal_alg, check_with_different_matrix_and_vector) {
    int str = 3;
    int col = 3;
    int procRank = 0;
    int flag = 0;
    int matr[3 * 3] = { -1, 1, -1,
                        -2, 0, -2,
                         3, -3, -3 };
    int vector[3] = { -1, 0, 1 };
    int* resbuf = nullptr;
    int proverka[3] = { 0, 0, -6 };
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
       resbuf = new int[str];
    }
    pharal_alg(str, col, matr, vector, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
               flag = 1;
            }
        }
        delete[] resbuf;
        ASSERT_EQ(flag, 0);
    }
}

TEST(func_pharal_alg, check_with_random_matrix_and_vector) {
    int str = 3;
    int col = 3;
    int procRank = 0;
    int flag = 0;
    int matr[3 * 3];
    int vector[3];
    int* resbuf = nullptr;
    int proverka[3];
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        resbuf = new int[str];
        random_vector(str, vector);
        random_matrix(str, col, matr);
        multipl(matr, vector, str, col, proverka);
    }
    pharal_alg(str, col, matr, vector, resbuf);
    if (procRank == 0) {
        for (int i = 0; i < col; i++) {
            if (proverka[i] != resbuf[i]) {
               flag = 1;
            }
        }
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