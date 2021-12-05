// Copyright 2021 Burdukov Mikhail
#include <gtest/gtest.h>
#include <numeric>
#include <gtest-mpi-listener.hpp>
#include "./topology_star.hpp"


TEST(topoloy_star, simple_test) {
  int prank, pcount;
  MPI_Comm_size(MPI_COMM_WORLD, &pcount);
  MPI_Comm_rank(MPI_COMM_WORLD, &prank);
  create_graph_star();
  ASSERT_EQ(1, 1);
}

TEST(topoloy_star, check_vertex_degree) {
  int prank, pcount;
  MPI_Comm_size(MPI_COMM_WORLD, &pcount);
  MPI_Comm_rank(MPI_COMM_WORLD, &prank);

  MPI_Comm star = create_graph_star();
  if (prank == 0) {
    for (int i = 0; i < pcount; i++) {
      int count;
      MPI_Graph_neighbors_count(star, i, &count);
      if (i == 0)
        ASSERT_EQ(count, pcount - 1);
      else
        ASSERT_EQ(count, 1);
    }
  }
}

TEST(topoloy_star, from_leafs_to_root) {
  int pcount, prank;
  MPI_Comm star = create_graph_star();
  MPI_Comm_size(MPI_COMM_WORLD, &pcount);
  MPI_Comm_rank(MPI_COMM_WORLD, &prank);
  if (prank == 0) {
    for (int i = 1; i < pcount; i++) {
      int value = 0;
      MPI_Status status;
      MPI_Recv(&value, 1, MPI_INT, i, 0, star, &status);
      ASSERT_EQ(1, value);
    }
  } else {
    int neighbours = 1;
    MPI_Graph_neighbors(star, prank, 1, &neighbours);
    int value = 1;
    MPI_Send(&value, 1, MPI_INT, neighbours, 0, star);
  }
}

TEST(topoloy_star, from_root_to_leafs) {
  int prank, pcount;
  MPI_Comm star = create_graph_star();
  MPI_Comm_size(MPI_COMM_WORLD, &pcount);
  MPI_Comm_rank(MPI_COMM_WORLD, &prank);
  if (prank == 0) {
    int* neighbours = new int[pcount - 1];
    MPI_Graph_neighbors(star, prank, pcount, neighbours);
    for (int i = 0; i < pcount - 1; i++) {
      int value = 1;
      MPI_Send(&value, value, MPI_INT, neighbours[i], 0, star);
    }
    delete[] neighbours;
  } else {
    int value = 0;
    MPI_Status status;
    MPI_Recv(&value, 1, MPI_INT, 0, 0, star, &status);
    ASSERT_EQ(1, value);
  }
}

TEST(topoloy_star, double_check) {
  int pcount, prank;
  MPI_Comm star = create_graph_star();
  MPI_Comm_size(MPI_COMM_WORLD, &pcount);
  MPI_Comm_rank(MPI_COMM_WORLD, &prank);

  if (prank == 0) {
    for (int i = 1; i < pcount; i++) {
      int value = 0;
      MPI_Status status;
      MPI_Recv(&value, 1, MPI_INT, i, 0, star, &status);
      ASSERT_EQ(1, value);
    }
  } else {
    int neighbours = 1;
    MPI_Graph_neighbors(star, prank, 1, &neighbours);
    int value = 1;
    MPI_Send(&value, 1, MPI_INT, neighbours, 0, star);
  }

  if (prank == 0) {
    int* neighbours = new int[pcount - 1];
    MPI_Graph_neighbors(star, prank, pcount, neighbours);
    for (int i = 0; i < pcount - 1; i++) {
      int value = 1;
      MPI_Send(&value, value, MPI_INT, neighbours[i], 0, star);
    }
    delete[] neighbours;
  } else {
    int value = 0;
    MPI_Status status;
    MPI_Recv(&value, 1, MPI_INT, 0, 0, star, &status);
    ASSERT_EQ(1, value);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  if (MPI_SUCCESS != MPI_Init(&argc, &argv)) {
    std::cout << "init error" << std::endl;
    exit(0);
  }
  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();
  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());
  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
