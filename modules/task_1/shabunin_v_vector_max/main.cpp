// Copyright 2021 Shabunin Vladislav
#include <gtest/gtest.h>
#include <vector>
#include "./vector_max.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Max_MPI, Test_Size_10) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 10;

    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }

    int global_max;
    global_max = getParallelMax(global_vec, count_size_vector);

    if (rank == 0) {
        int reference_max = getSequentialMax(global_vec);
        ASSERT_EQ(reference_max, global_max);
    }
}

TEST(Parallel_Max_MPI, Test_Size_20) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 20;

    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }

    int global_max;
    global_max = getParallelMax(global_vec, count_size_vector);

    if (rank == 0) {
      int reference_max = getSequentialMax(global_vec);
        ASSERT_EQ(reference_max, global_max);
    }
}

TEST(Parallel_Max_MPI, Test_Size_30) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 30;

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int global_max;
  global_max = getParallelMax(global_vec, count_size_vector);

  if (rank == 0) {
    int reference_max = getSequentialMax(global_vec);
    ASSERT_EQ(reference_max, global_max);
  }
}

TEST(Parallel_Max_MPI, Test_Size_50) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 50;

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int global_max;
  global_max = getParallelMax(global_vec, count_size_vector);

  if (rank == 0) {
    int reference_max = getSequentialMax(global_vec);
    ASSERT_EQ(reference_max, global_max);
  }
}

TEST(Parallel_Max_MPI, Test_Size_100) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 100;

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int global_max;
  global_max = getParallelMax(global_vec, count_size_vector);

  if (rank == 0) {
    int reference_max = getSequentialMax(global_vec);
    ASSERT_EQ(reference_max, global_max);
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
