// Copyright 2021 Gordeev Viktor
#include <gtest/gtest.h>
#include "./strongin_mpi.h"
#include <gtest-mpi-listener.hpp>

TEST(strongin_MPI, Minimal_Example) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double left_x = 1.;
    double right_x = 8.;
    int N = 10;
    double Epsilon = 0.001;
    double k = StronginParallel(left_x, right_x, N, Epsilon, size, rank);
    MPI_Barrier(MPI_COMM_WORLD);
    ASSERT_NO_THROW();
}

TEST(strongin_MPI, More_left_right_interval) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double left_x = 20.;
    double right_x = 45.;
    int N = 10;
    double Epsilon = 0.001;
    double k = StronginParallel(left_x, right_x, N, Epsilon, size, rank);
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(strongin_MPI, More_accuracy) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double left_x = 20.;
    double right_x = 45.;
    int N = 10;
    double Epsilon = 0.0001;
    double k = StronginParallel(left_x, right_x, N, Epsilon, size, rank);
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(strongin_MPI, Big_left_right) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double left_x = 10000.;
    double right_x = 20000.;
    int N = 10;
    double Epsilon = 0.001;
    double k = StronginParallel(left_x, right_x, N, Epsilon, size, rank);
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(strongin_MPI, Big_Nearly_Equal_left_right) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double left_x = 10000.;
    double right_x = 10002.;
    int N = 10;
    double Epsilon = 0.001;
    double k = StronginParallel(left_x, right_x, N, Epsilon, size, rank);
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
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
