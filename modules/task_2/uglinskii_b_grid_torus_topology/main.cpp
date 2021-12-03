// Copyright 2021 Uglinskii Bogdan
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "./grid_torus_topology.h"

TEST(Correct_Topology, Creating_Grid_Torus) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int dims[2] = {0, 0};
  MPI_Dims_create(ProcNum, 2, dims);
  MPI_Comm grid_torus_comm = CreateGridTorusTopology(dims[0], dims[1]);

  if (ProcRank == 0) {
        ASSERT_TRUE(IsExpectedGridTorus(grid_torus_comm, 2, dims));
  }
}

TEST(Correct_Topology, Correct_Position) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int dims[2] = {0, 0};
  MPI_Dims_create(ProcNum, 2, dims);
  MPI_Comm grid_torus_comm = CreateGridTorusTopology(dims[0], dims[1]);

  int exp_pos[2] = {ProcRank / dims[1],
                    ProcRank - (ProcRank / dims[1]) * dims[1]};

  int my_coords[2];

  MPI_Cart_coords(grid_torus_comm, ProcRank, 2, my_coords);

  ASSERT_EQ(exp_pos[0], my_coords[0]);
  ASSERT_EQ(exp_pos[1], my_coords[1]);
}

TEST(Correct_Topology, Correct_size) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int dims[2] = {0, 0};
  MPI_Dims_create(ProcNum, 2, dims);
  MPI_Comm grid_torus_comm = CreateGridTorusTopology(dims[0] + 1, dims[1] + 1);

  if (ProcRank == 0) {
    ASSERT_EQ(grid_torus_comm, MPI_COMM_NULL);
  }
}

TEST(Correct_Massage_Sending, 2_sending_point_to_point) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int dims[2] = {0, 0};
  MPI_Dims_create(ProcNum, 2, dims);
  MPI_Comm grid_torus_comm = CreateGridTorusTopology(dims[0], dims[1]);

  if (ProcNum == 1) {
    ASSERT_TRUE(true);
  } else {
    int data = 0, expected_data = 58;
    int distinations[2] = {ProcNum - 1, ProcNum / 2};
    if (ProcRank == 0) {
      data = 58;
      MPI_Send(&data, 1, MPI_INT, distinations[0], 1, grid_torus_comm);
      if (distinations[0] != distinations[1]) {
        MPI_Send(&data, 1, MPI_INT, distinations[1], 1, grid_torus_comm);
      }
    } else if ((ProcRank == distinations[0]) || (ProcRank == distinations[1])) {
      MPI_Status status;
      MPI_Recv(&data, 1, MPI_INT, 0, 1, grid_torus_comm, &status);
      ASSERT_EQ(data, expected_data);
    }
  }
}

TEST(Correct_Massage_Sending, collective_sending) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int dims[2] = {0, 0};
  MPI_Dims_create(ProcNum, 2, dims);
  MPI_Comm grid_torus_comm = CreateGridTorusTopology(dims[0], dims[1]);

  if (ProcNum == 1) {
    ASSERT_TRUE(true);
  } else {
    int koeff = 0;
    if (ProcRank == 0) {
      koeff = 10;
    }
    MPI_Bcast(&koeff, 1, MPI_INT, 0, grid_torus_comm);
    int answer = koeff * (ProcRank + 1);
    int result = 0;
    MPI_Reduce(&answer, &result, 1, MPI_INT, MPI_SUM, 0, grid_torus_comm);
    if (ProcRank == 0) {
      int exp_result = 0;
      for (int i = 0; i < ProcNum; i++) {
        exp_result += koeff * (i + 1);
      }
      ASSERT_EQ(result, exp_result);
    }
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
