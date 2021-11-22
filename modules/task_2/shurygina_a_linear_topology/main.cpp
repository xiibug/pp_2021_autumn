// Copyright 2021 Shurygina Anna
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_2/shurygina_a_linear_topology/linear_topology.h"

TEST(Linear_Topology_MPI, Test_Creating_Linear_Graph) {
    int size;
    int nodes, edges;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    MPI_Comm communicator = createGraphComm(MPI_COMM_WORLD);
    MPI_Graphdims_get(communicator, &nodes, &edges);
    ASSERT_EQ(nodes, size);
    ASSERT_EQ(edges, 2 * (size - 1));
}

TEST(Linear_Topology_MPI, Test_Graph_Neighbors) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    MPI_Comm communicator = createGraphComm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);
    int count_neighbors;
    if ((rank == 0) || (rank == size - 1)) {
        MPI_Graph_neighbors_count(communicator, rank, &count_neighbors);
        ASSERT_EQ(count_neighbors, 1);
    } else {
        MPI_Graph_neighbors_count(communicator, rank, &count_neighbors);
        ASSERT_EQ(count_neighbors, 2);
    }
}

TEST(Linear_Topology_MPI, Test_Send_Recv_From_First_To_Last) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // if only one process
    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    MPI_Status status;
    MPI_Comm communicator = createGraphComm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rankFirst = 0;
    int rankLast = size - 1;

    int dataSize = 10;
    int* data = new int[dataSize];

    if (rank == rankFirst) {
        data = getRandomSequence(dataSize);
        MPI_Send(&data[0], dataSize, MPI_INT, rankLast, 0, MPI_COMM_WORLD);
    }
    if (rank == rankLast) {
        MPI_Recv(&data[0], dataSize, MPI_INT,
            rankFirst, 0, MPI_COMM_WORLD, &status);
    }

    int* r = sendData(&data[0], dataSize, MPI_INT,
        rankLast, 0, communicator, rankFirst, rank);
    if (rank == rankLast) {
        std::vector<int> message(data, data + dataSize);
        std::vector<int> result_message(r, r + dataSize);
        ASSERT_EQ(message, result_message);
    }
}

TEST(Linear_Topology_MPI, Test_Send_Recv_From_First_To_Last_Large_Size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    MPI_Status status;
    MPI_Comm communicator = createGraphComm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rank_s = 0;
    int rank_r = size - 1;

    int size_vec = 1000;
    int* m = new int[size_vec];
    if (rank == rank_s) {
        m = getRandomSequence(size_vec);
        MPI_Send(&m[0], size_vec, MPI_INT, rank_r, 0, MPI_COMM_WORLD);
    }
    if (rank == rank_r) {
        MPI_Recv(&m[0], size_vec, MPI_INT,
            rank_s, 0, MPI_COMM_WORLD, &status);
    }

    int* r = sendData(&m[0], size_vec, MPI_INT,
        rank_r, 0, communicator, rank_s, rank);
    if (rank == rank_r) {
        std::vector<int> message(m, m + size_vec);
        std::vector<int> result_message(r, r + size_vec);
        ASSERT_EQ(message, result_message);
    }
}

TEST(Linear_Topology_MPI, Test_Send_Recv_From_Last_To_First) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    MPI_Status status;
    MPI_Comm communicator = createGraphComm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rank_s = size - 1;
    int rank_r = 0;

    int size_vec = 10;
    int* m = new int[size_vec];
    if (rank == rank_s) {
        m = getRandomSequence(size_vec);
        MPI_Send(&m[0], size_vec, MPI_INT,
            rank_r, 0, MPI_COMM_WORLD);
    }
    if (rank == rank_r) {
        MPI_Recv(&m[0], size_vec, MPI_INT,
            rank_s, 0, MPI_COMM_WORLD, &status);
    }

    int* r = sendData(&m[0], size_vec, MPI_INT,
        rank_r, 0, communicator, rank_s, rank);
    if (rank == rank_r) {
        std::vector<int> message(m, m + size_vec);
        std::vector<int> result_message(r, r + size_vec);
        ASSERT_EQ(message, result_message);
    }
}

TEST(Linear_Topology_MPI, Test_Send_Recv_From_Last_To_First_Large_Size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    MPI_Status status;
    MPI_Comm communicator = createGraphComm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rankFirst = size - 1;
    int rankLast = 0;

    int size_vec = 1000;
    int* m = new int[size_vec];

    if (rank == rankFirst) {
        m = getRandomSequence(size_vec);
        MPI_Send(&m[0], size_vec, MPI_INT,
            rankLast, 0, MPI_COMM_WORLD);
    }
    if (rank == rankLast) {
        MPI_Recv(&m[0], size_vec, MPI_INT,
            rankFirst, 0, MPI_COMM_WORLD, &status);
    }

    int* r = sendData(&m[0], size_vec, MPI_INT,
        rankLast, 0, communicator, rankFirst, rank);
    if (rank == rankLast) {
        std::vector<int> message(m, m + size_vec);
        std::vector<int> result_message(r, r + size_vec);
        ASSERT_EQ(message, result_message);
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
