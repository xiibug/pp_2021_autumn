// Copyright 2021 Shelepin Nikita
#include <gtest/gtest.h>
#include "./sleeping_hairdresser.h"
#include <gtest-mpi-listener.hpp>

TEST(Sleepeing_hairdresser, No_Customers) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, 1, 0));
    }
}

TEST(Sleepeing_hairdresser, Five_Customers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 5;

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, 4, runs*(size-1)));
    } else {
        ASSERT_NO_THROW(customer(rank, runs));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Sleepeing_hairdresser, Ten_Customers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 10;

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, size, runs));
    } else {
        ASSERT_NO_THROW(customer(rank, runs));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Sleepeing_hairdresser, Twenty_Customers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 20;

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, size, runs));
    } else {
        ASSERT_NO_THROW(customer(rank, runs));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Sleepeing_hairdresser, Forty_Customers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int runs = 40;

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, size, runs));
    } else {
        ASSERT_NO_THROW(customer(rank, runs));
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
