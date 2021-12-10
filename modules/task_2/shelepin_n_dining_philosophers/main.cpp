// Copyright 2021 Shelepin Nikita
#include <gtest/gtest.h>
#include "./dining_philosophers.h"
#include <gtest-mpi-listener.hpp>

TEST(Dining_philosophers_MPI, One_pizza) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 1;

    if (rank == 0) {
        table(rank, size, runs);
    } else {
        philosopher(rank, runs);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(Dining_philosophers_MPI, Three_pizzas) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 3;

    if (rank == 0) {
        table(rank, size, runs);
    } else {
        philosopher(rank, runs);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(Dining_philosophers_MPI, Five_pizzas) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 5;

    if (rank == 0) {
        ASSERT_NO_THROW(table(rank, size, runs));
    } else {
        ASSERT_NO_THROW(philosopher(rank, runs));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Dining_philosophers_MPI, Ten_pizzas) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 10;

    if (rank == 0) {
        ASSERT_NO_THROW(table(rank, size, runs));
    } else {
        ASSERT_NO_THROW(philosopher(rank, runs));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Dining_philosophers_MPI, Twenty_pizzas) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 20;

    if (rank == 0) {
        ASSERT_NO_THROW(table(rank, size, runs));
    } else {
        ASSERT_NO_THROW(philosopher(rank, runs));
    }
    MPI_Barrier(MPI_COMM_WORLD);
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
