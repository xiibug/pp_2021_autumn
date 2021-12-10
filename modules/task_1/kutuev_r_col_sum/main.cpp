// Copyright 2021 Kutuev Roman
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./col_sum.h"

TEST(Columns_sums_MPI, Invalid_size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 0, m = 0;

  if (rank == 0) {
    ASSERT_ANY_THROW(randomMatrix(n, m));
  }
}

TEST(Columns_sums_MPI, Matrix_5x5) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 5, m = 5;
  int* matrix = nullptr;

  if (rank == 0) matrix = randomMatrix(n, m);

  int* sum = parallelSum(matrix, n, m);

  if (rank == 0) {
    int* reference_sum = sequentialSum(matrix, n, m);

    for (int i = 0; i < m; i++) {
      ASSERT_EQ(reference_sum[i], sum[i]);
    }
  }
}

TEST(Columns_sums_MPI, Matrix_12x36) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 12, m = 36;
  int* matrix = nullptr;

  if (rank == 0) matrix = randomMatrix(n, m);

  int* sum = parallelSum(matrix, n, m);

  if (rank == 0) {
    int* reference_sum = sequentialSum(matrix, n, m);

    for (int i = 0; i < m; i++) {
      ASSERT_EQ(reference_sum[i], sum[i]);
    }
  }
}

TEST(Columns_sums_MPI, Matrix_50x70) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 50, m = 70;
  int* matrix = nullptr;

  if (rank == 0) matrix = randomMatrix(n, m);

  int* sum = parallelSum(matrix, n, m);

  if (rank == 0) {
    int* reference_sum = sequentialSum(matrix, n, m);

    for (int i = 0; i < m; i++) {
      ASSERT_EQ(reference_sum[i], sum[i]);
    }
  }
}

TEST(Columns_sums_MPI, Matrix_200x300) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 200, m = 300;
  int* matrix = nullptr;

  if (rank == 0) matrix = randomMatrix(n, m);

  int* sum = parallelSum(matrix, n, m);

  if (rank == 0) {
    int* reference_sum = sequentialSum(matrix, n, m);

    for (int i = 0; i < m; i++) {
      ASSERT_EQ(reference_sum[i], sum[i]);
    }
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  std::srand(std::time(nullptr));

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
