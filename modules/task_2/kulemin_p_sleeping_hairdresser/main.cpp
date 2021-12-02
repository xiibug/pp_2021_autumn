// Copyright 2021 Shelepin Nikita
#include <gtest/gtest.h>
#include "./sleeping_hairdresser.h"
#include <gtest-mpi-listener.hpp>

TEST(Sleepeing_hairdresser, two_Chairs) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, 2, size-2));
    }
    else if (rank == 1) {
        ASSERT_NO_THROW(line(2, size - 2));
    }
    else {
        ASSERT_NO_THROW(customer(rank));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Sleepeing_hairdresser, Five_chairs) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        ASSERT_NO_THROW( barber(rank, 5, size-2));
    } else if(rank==1){
        ASSERT_NO_THROW(line(5, size-2));
    }
    else {
        ASSERT_NO_THROW(customer(rank));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Sleepeing_hairdresser, Ten_chairs) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, 10, size - 2));
    }
    else if (rank == 1) {
        ASSERT_NO_THROW(line(10, size - 2));
    }
    else {
        ASSERT_NO_THROW(customer(rank));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Sleepeing_hairdresser, Fifteen_chairs) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, 15, size - 2));
    }
    else if (rank == 1) {
        ASSERT_NO_THROW(line(15, size - 2));
    }
    else {
        ASSERT_NO_THROW(customer(rank));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Sleepeing_hairdresser, one_chair) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        ASSERT_NO_THROW(barber(rank, 1, size - 2));
    }
    else if (rank == 1) {
        ASSERT_NO_THROW(line(1, size - 2));
    }
    else {
        ASSERT_NO_THROW(customer(rank));
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
