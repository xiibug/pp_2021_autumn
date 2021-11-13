// Copyright 2021 Novozhilov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./star_topology.h"
#include <gtest-mpi-listener.hpp>

TEST(star_topology, create_star_topology_works) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    ASSERT_NO_THROW(createStarTopology(MPI_COMM_WORLD, size));
}

TEST(star_topology, check_0_proc_neighbords) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm star_comm = createStarTopology(MPI_COMM_WORLD, size);
    int neighbors_count;
    MPI_Graph_neighbors_count(star_comm, 0, &neighbors_count);
    ASSERT_EQ(size - 1, neighbors_count);
}

TEST(star_topology, check_1_proc_neighbords) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_TRUE(true);
        return;
    }
    MPI_Comm star_comm = createStarTopology(MPI_COMM_WORLD, size);
    int neighbors_count;
    MPI_Graph_neighbors_count(star_comm, 1, &neighbors_count);
    ASSERT_EQ(1, neighbors_count);
}

TEST(star_topology, 0_proc_sends_data_to_1) {
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (size == 1) {
        ASSERT_TRUE(true);
        return;
    }
    MPI_Comm star_comm = createStarTopology(MPI_COMM_WORLD, size);
    if (rank == 0) {
        int send_data = 5;
        MPI_Send(&send_data, 1, MPI_INT, 1, 0, star_comm);
    }
    if (rank == 1) {
        int recive_data;
        MPI_Status status;
        MPI_Recv(&recive_data, 1, MPI_INT, 0, MPI_ANY_TAG, star_comm, &status);
        ASSERT_EQ(recive_data, 5);
    }
    
}

TEST(star_topology, 1_proc_sends_data_to_2) {
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (size < 3) {
        ASSERT_TRUE(true);
        return;
    }
    MPI_Comm star_comm = createStarTopology(MPI_COMM_WORLD, size);
    if (rank == 1) {
        int send_data = 5;
        MPI_Send(&send_data, 1, MPI_INT, 2, 0, star_comm);
    }
    if (rank == 2) {
        int recive_data;
        MPI_Status status;
        MPI_Recv(&recive_data, 1, MPI_INT, 1, MPI_ANY_TAG, star_comm, &status);
        ASSERT_EQ(recive_data, 5);
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
