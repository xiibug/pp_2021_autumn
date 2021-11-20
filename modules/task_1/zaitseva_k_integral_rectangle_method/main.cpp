// Copyright 2021 Zaitseva Ksenia
#include <mpi.h>
#include "RectangleMethod.h"
#include <iostream>
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>

TEST(Parallel_MPI, Test_Sin) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a = 0.0, b = 5.5;
    int n = 1000;
    double res_seq, res_par;
    res_par = IntegralParallel(a, b, n, 0);
    if (rank == 0) {
        res_seq = IntegralSequential(a, b, n, 0);
        EXPECT_NEAR(res_seq, res_par, std::numeric_limits<double>::epsilon() * std::max(res_par, res_seq) * 16 * 1000);
    }
}

TEST(Parallel_MPI, Test_Polinom1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a = 0.0, b = 5.5;
    int n = 1000;
    double res_seq, res_par;
    res_par = IntegralParallel(a, b, n, 1);
    if (rank == 0) {
        res_seq = IntegralSequential(a, b, n, 1);
        EXPECT_NEAR(res_seq, res_par, std::numeric_limits<double>::epsilon() * std::max(res_par, res_seq) * 16 * 1000);
    }
}

TEST(Parallel_MPI, Test_Polinom2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a = 0.0, b = 5.5;
    int n = 1000;
    double res_seq, res_par;
    res_par = IntegralParallel(a, b, n, 2);
    if (rank == 0) {
        res_seq = IntegralSequential(a, b, n, 2);
        EXPECT_NEAR(res_seq, res_par, std::numeric_limits<double>::epsilon() * std::max(res_par, res_seq) * 16 * 1000);
    }
}

TEST(Parallel_MPI, Test_Polinom3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a = 0.0, b = 5.5;
    int n = 1000;
    double res_seq, res_par;
    res_par = IntegralParallel(a, b, n, 3);
    if (rank == 0) {
        res_seq = IntegralSequential(a, b, n, 3);
        EXPECT_NEAR(res_seq, res_par, std::numeric_limits<double>::epsilon() * std::max(res_par, res_seq) * 16 * 1000);
    }
}

TEST(Parallel_MPI, Test_Cos) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a = 0.0, b = 5.5;
    int n = 1000;
    double res_seq, res_par;
    res_par = IntegralParallel(a, b, n, 4);
    if (rank == 0) {
        res_seq = IntegralSequential(a, b, n, 4);
        EXPECT_NEAR(res_seq, res_par, std::numeric_limits<double>::epsilon() * 16 * 1000);
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
    MPI_Finalize();
}
