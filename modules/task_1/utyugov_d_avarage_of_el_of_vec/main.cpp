// Copyright 2021 Utyugov Denis
#include <gtest/gtest.h>
#include <vector>
#include "./avarage_of_el_of_vec.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Create_vector) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 120;

  if (rank == 0) {
    ASSERT_NO_THROW(global_vec = getRandomVector(count_size_vector));
  }
}

TEST(Parallel_Operations_MPI, Size_of_vector_eq_zero) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 0;

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  if (rank == 0) {
    ASSERT_ANY_THROW(getParallelOperations(global_vec, count_size_vector));
  }
}

TEST(Parallel_Operations_MPI, Test_Sum) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 120;

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int global_sum = getParallelOperations(global_vec, count_size_vector);

  if (rank == 0) {
    int reference_sum = getSequentialOperations(global_vec);
    ASSERT_EQ(reference_sum, global_sum);
  }
}

TEST(Parallel_Operations_MPI, Test_Avarage) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 120;

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int global_sum = getParallelOperations(global_vec, count_size_vector);

  if (rank == 0) {
    int reference_sum = getSequentialOperations(global_vec);
    ASSERT_EQ(getAvarage(reference_sum, count_size_vector),
              getAvarage(global_sum, count_size_vector));
  }
}

TEST(Parallel_Operations_MPI, Big_Vector) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int count_size_vector = 100000;

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int global_sum = getParallelOperations(global_vec, count_size_vector);

  if (rank == 0) {
    int reference_sum = getSequentialOperations(global_vec);
    ASSERT_EQ(reference_sum, global_sum);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);

  // MPI_Finalize();
  return RUN_ALL_TESTS();
}
