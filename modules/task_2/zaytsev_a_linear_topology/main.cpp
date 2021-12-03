// Copyright 2021 Zaytsev Alexander
#include <gtest/gtest.h>
#include "./linear_topology.h"
#include <gtest-mpi-listener.hpp>
TEST(Linar_Topology, 1) {
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  ASSERT_NO_THROW(Linar(MPI_COMM_WORLD, size));
}
TEST(Linar_Topology, 2) {
  int size, neghbors_count;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm Line = Linar(MPI_COMM_WORLD, size);
  MPI_Graph_neighbors_count(Line, 0, &neghbors_count);
  ASSERT_EQ(1, neghbors_count);
}
TEST(Linar_Topology, 3) {
  int size, neghbors_count;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size == 1) {
    ASSERT_TRUE(true);
    return;
  }
  MPI_Comm Line = Linar(MPI_COMM_WORLD, size);
  MPI_Graph_neighbors_count(Line, size - 1, &neghbors_count);
  ASSERT_EQ(1, neghbors_count);
}
TEST(Linar_Topology, 4) {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (size < 5) {
    ASSERT_TRUE(true);
    return;
  }
  MPI_Comm Line = Linar(MPI_COMM_WORLD, size);
  if (rank == 0) {
    int object = 260;
    MPI_Send(&object, 1, MPI_INT, 4, 0, Line);
  }
  if (rank == 4) {
    int data;
    MPI_Status our_status;
    MPI_Recv(&data, 1, MPI_INT, 0, MPI_ANY_TAG, Line, &our_status);
    ASSERT_EQ(data, 260);
  }
}
TEST(Linar_Topology, 5) {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (size < 5) {
    ASSERT_TRUE(true);
    return;
  }
  MPI_Comm Line = Linar(MPI_COMM_WORLD, size);
  if (rank == 4) {
    int object = 260;
    MPI_Send(&object, 1, MPI_INT, 0, 0, Line);
  }
  if (rank == 0) {
    int data;
    MPI_Status our_status;
    MPI_Recv(&data, 1, MPI_INT, 4, MPI_ANY_TAG, Line, &our_status);
    ASSERT_EQ(data, 260);
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
