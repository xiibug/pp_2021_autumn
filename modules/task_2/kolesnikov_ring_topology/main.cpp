// Copyright 2021 Kolesnikov Ilya
#include <gtest/gtest.h>
#include <mpi.h>
#include <string>
#include "./kolesnikov_ring_topology.h"
#include <gtest-mpi-listener.hpp>

TEST(find_symbol, left_neighbour_of_0_process) {
    int rank = 0, size = 0;
    int neighbours[2];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm ring = topology_ring(MPI_COMM_WORLD);

    if (rank == 0) {
        MPI_Cart_shift(ring, 0, 1, &neighbours[0], &neighbours[1]);
        ASSERT_EQ(size-1, neighbours[0]);
    }
}

TEST(find_symbol, right_neighbour_of_0_process) {
    int rank = 0, size = 0;
    int neighbours[2];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm ring = topology_ring(MPI_COMM_WORLD);
    if (rank == 0 && size > 1) {
        MPI_Cart_shift(ring, 0, 1, &neighbours[0], &neighbours[1]);
        ASSERT_EQ(1, neighbours[1]);
    }
}

TEST(find_symbol, send_from_3_to_5) {
    int rank = 0, size = 0;
    int to_send = 12, to_get = 0;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm ring = topology_ring(MPI_COMM_WORLD);
    if (size > 5) {
        if (rank == 3) {
            MPI_Send(&to_send, 1, MPI_INT, 5, 1, ring);
        }
        if (rank == 5) {
            MPI_Recv(&to_get, 1, MPI_INT, 3, 1, ring, &status);
            ASSERT_EQ(to_send, to_get);
        }
    }
}

TEST(find_symbol, send_from_5_to_3) {
    int rank = 0, size = 0;
    int to_send = 150, to_get = 0;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm ring = topology_ring(MPI_COMM_WORLD);
    if (size > 5) {
        if (rank == 5) {
            MPI_Send(&to_send, 1, MPI_INT, 3, 1, ring);
        }
        if (rank == 3) {
            MPI_Recv(&to_get, 1, MPI_INT, 5, 1, ring, &status);
            ASSERT_EQ(to_send, to_get);
        }
    }
}

TEST(find_symbol, right_neighbour_of_last_process) {
    int rank = 0, size = 0;
    int neighbours[2];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm ring = topology_ring(MPI_COMM_WORLD);
    if (rank == size - 1) {
        MPI_Cart_shift(ring, 0, 1, &neighbours[0], &neighbours[1]);
        ASSERT_EQ(0, neighbours[1]);
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
