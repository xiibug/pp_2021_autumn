// Copyright 2021 Zaytsev Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./min_elem_of_vector.h"
#include <gtest-mpi-listener.hpp>

TEST(parallel_min, test_min_elem_12) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* g_vector = nullptr;
  const int const_size_vector = 12;
  if (rank == 0) {
    g_vector = RandomVector(const_size_vector);
  }
  int global_min = ParallelMin(g_vector, const_size_vector);
  if (rank == 0) {
    int sequential_min = SequentialMin(g_vector, const_size_vector);
    ASSERT_EQ(sequential_min, global_min);
  }
}
TEST(parallel_min, test_min_elem_40) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* g_vector = nullptr;
  const int const_size_vector = 40;
  if (rank == 0) {
    g_vector = RandomVector(const_size_vector);
  }
  int global_min = ParallelMin(g_vector, const_size_vector);
  if (rank == 0) {
    int sequential_min = SequentialMin(g_vector, const_size_vector);
    ASSERT_EQ(sequential_min, global_min);
  }
}
TEST(parallel_min, test_min_elem_160) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* g_vector = nullptr;
  const int const_size_vector = 160;
  if (rank == 0) {
    g_vector = RandomVector(const_size_vector);
  }
  int global_min = ParallelMin(g_vector, const_size_vector);
  if (rank == 0) {
    int sequential_min = SequentialMin(g_vector, const_size_vector);
    ASSERT_EQ(sequential_min, global_min);
  }
}
TEST(parallel_min, test_min_elem_2400) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* g_vector = nullptr;
  const int const_size_vector = 2400;
  if (rank == 0) {
    g_vector = RandomVector(const_size_vector);
  }
  int global_min = ParallelMin(g_vector, const_size_vector);
  if (rank == 0) {
    int sequential_min = SequentialMin(g_vector, const_size_vector);
    ASSERT_EQ(sequential_min, global_min);
  }
}
TEST(parallel_min, test_min_elem_16000) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* g_vector = nullptr;
  const int const_size_vector = 16000;
  if (rank == 0) {
    g_vector = RandomVector(const_size_vector);
  }
  int global_min = ParallelMin(g_vector, const_size_vector);
  if (rank == 0) {
    int sequential_min = SequentialMin(g_vector, const_size_vector);
    ASSERT_EQ(sequential_min, global_min);
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
