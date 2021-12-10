// Copyright 2021 Preobrazhenskaya Yuliya
#include <gtest/gtest.h>
#include "./ring_topology.h"
#include <gtest-mpi-listener.hpp>

TEST(Ring_Topology_MPI, create_ring_topology) {
    ASSERT_NO_THROW(getRingTopology(MPI_COMM_WORLD));
}

TEST(Ring_Topology_MPI, get_the_number_of_neighbors_for_process_0) {
    MPI_Comm ring = getRingTopology(MPI_COMM_WORLD);
    int neighbors_count;
    MPI_Graph_neighbors_count(ring, 0, &neighbors_count);
    ASSERT_EQ(1, neighbors_count);
}

TEST(Ring_Topology_MPI, get_the_rank_of_neighbor_for_process_0) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_TRUE(true);
        return;
    }
    MPI_Comm ring = getRingTopology(MPI_COMM_WORLD);
    int neighbor_count = 1;
    int neighbor;
    MPI_Graph_neighbors(ring, 0, neighbor_count, &neighbor);
    ASSERT_EQ(1, neighbor);
}

TEST(Ring_Topology_MPI, send_data_from_process_0_to_process_2) {
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 3) {
        ASSERT_TRUE(true);
        return;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm ring = getRingTopology(MPI_COMM_WORLD);
    if (rank == 0) {
        char data = '+';
        MPI_Send(&data, 1, MPI_CHAR, 2, 0, ring);
    }
    if (rank == 2) {
        char recv_data;
        MPI_Status status;
        MPI_Recv(&recv_data, 1, MPI_CHAR, 0, 0, ring, &status);
        ASSERT_EQ(recv_data, '+');
    }
}

TEST(Ring_Topology_MPI, send_data_from_the_last_process_to_process_0) {
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_TRUE(true);
        return;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm ring = getRingTopology(MPI_COMM_WORLD);
    if (rank == size - 1) {
        int data = 9;
        MPI_Send(&data, 1, MPI_INT, 0, 0, ring);
    }

    if (rank == 0) {
        int recv_data;
        MPI_Status status;
        MPI_Recv(&recv_data, 1, MPI_INT, size - 1, 0, ring, &status);
        ASSERT_EQ(recv_data, 9);
    }
}

TEST(Ring_Topology_MPI, check_whether_this_topology_is_a_ring) {
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm ring = getRingTopology(MPI_COMM_WORLD);
    int neighbors_count;
    MPI_Graph_neighbors_count(ring, rank, &neighbors_count);
    int* neighbors = new int[neighbors_count];
    MPI_Graph_neighbors(ring, rank, neighbors_count, neighbors);
    ASSERT_EQ(neighbors_count, 1);
    ASSERT_EQ(neighbors[0], (rank + 1) % size);
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
