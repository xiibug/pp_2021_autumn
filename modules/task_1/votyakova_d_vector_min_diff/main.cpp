// Copyright 2021 Votyakova Darya
#include <gtest/gtest.h>
#include <vector>
#include "./vector_min_diff.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Min_Difference_MPI, Size_10) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int vector_size = 10;

  if (rank == 0) {
    global_vec = getRandomVector(vector_size);
  }

  int* pdiff = getParallelMinDiff(global_vec);

  if (rank == 0) {
    int* sdiff = getSequentialMinDiff(global_vec);

    ASSERT_EQ(sdiff[0], pdiff[0]);
    ASSERT_EQ(sdiff[1], pdiff[1]);
    ASSERT_EQ(sdiff[2], pdiff[2]);
  }
}

TEST(Parallel_Min_Difference_MPI, Size_20) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int vector_size = 20;

  if (rank == 0) {
    global_vec = getRandomVector(vector_size);
  }

  int* pdiff = getParallelMinDiff(global_vec);

  if (rank == 0) {
    int* sdiff = getSequentialMinDiff(global_vec);

    ASSERT_EQ(sdiff[0], pdiff[0]);
    ASSERT_EQ(sdiff[1], pdiff[1]);
    ASSERT_EQ(sdiff[2], pdiff[2]);
  }
}

TEST(Parallel_Min_Difference_MPI, Size_50) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int vector_size = 50;

  if (rank == 0) {
    global_vec = getRandomVector(vector_size);
  }

  int* pdiff = getParallelMinDiff(global_vec);

  if (rank == 0) {
    int* sdiff = getSequentialMinDiff(global_vec);

    ASSERT_EQ(sdiff[0], pdiff[0]);
    ASSERT_EQ(sdiff[1], pdiff[1]);
    ASSERT_EQ(sdiff[2], pdiff[2]);
  }
}

TEST(Parallel_Min_Difference_MPI, Size_100) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int vector_size = 100;

  if (rank == 0) {
    global_vec = getRandomVector(vector_size);
  }

  int* pdiff = getParallelMinDiff(global_vec);

  if (rank == 0) {
    int* sdiff = getSequentialMinDiff(global_vec);

    ASSERT_EQ(sdiff[0], pdiff[0]);
    ASSERT_EQ(sdiff[1], pdiff[1]);
    ASSERT_EQ(sdiff[2], pdiff[2]);
  }
}

TEST(Parallel_Min_Difference_MPI, Size_200) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int vector_size = 200;

  if (rank == 0) {
    global_vec = getRandomVector(vector_size);
  }

  int* pdiff = getParallelMinDiff(global_vec);

  if (rank == 0) {
    int* sdiff = getSequentialMinDiff(global_vec);

    ASSERT_EQ(sdiff[0], pdiff[0]);
    ASSERT_EQ(sdiff[1], pdiff[1]);
    ASSERT_EQ(sdiff[2], pdiff[2]);
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
