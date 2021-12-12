// Copyright 2021 Kurguzikov Kirill

#include <gtest/gtest.h>
#include "./kurguzikov_striping_signs_vector.h"
#include <./gtest-mpi-listener.hpp>

#include <iostream>

TEST(Tets_parallel_and_sequential, sequential_test) {
  int procRank;
  std::vector<int> vec;
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

  if (procRank == 0) {
    vec = { 10, 20, -30, -40, 50, -60, -70, -80, 90, 100 };

    int sequentia_res = sequentialCount(vec);
    ASSERT_EQ(sequentia_res, 4);
  }
}

TEST(Tets_parallel_and_sequential, parallel_test) {
  int procRank;
  const int vecLen = 50;
  std::vector<int> vec;

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

  if (procRank == 0) {
    vec = { 10, 20, -30, -40, 50, -60, -70, -80, 90, 100 };
  }

  int parallel_res = parallelCount(vec);

  if (procRank == 0) {
    ASSERT_EQ(4, parallel_res);
  }
}

TEST(Tets_parallel_and_sequential, vec_size_10) {
  int procRank;
  const int vecLen = 10;
  std::vector<int> vec;

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

  if (procRank == 0) {
    vec = getRandomValue(vecLen);
  }

  int parallel_res = parallelCount(vec);

  if (procRank == 0) {
    int sequentia_res = sequentialCount(vec);
    ASSERT_EQ(sequentia_res, parallel_res);
  }
}

TEST(Tets_parallel_and_sequential, vec_size_50) {
  int procRank;
  const int vecLen = 50;
  std::vector<int> vec;

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

  if (procRank == 0) {
    vec = getRandomValue(vecLen);
  }

  int parallel_res = parallelCount(vec);

  if (procRank == 0) {
    int sequentia_res = sequentialCount(vec);
    ASSERT_EQ(sequentia_res, parallel_res);
  }
}

TEST(Tets_parallel_and_sequential, vec_size_100) {
  int procRank;
  const int vecLen = 100;
  std::vector<int> vec;

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

  if (procRank == 0) {
    vec = getRandomValue(vecLen);
  }

  int parallel_res = parallelCount(vec);

  if (procRank == 0) {
    int sequentia_res = sequentialCount(vec);
    ASSERT_EQ(sequentia_res, parallel_res);
  }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);  

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
