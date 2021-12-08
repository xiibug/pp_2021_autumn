// Copyright 2021 Barysheva Maria
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./matrix_max_row_elem.h"

TEST(Matrix_row_max_elem_MPI, Matrix_2x3) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 2, m = 3;
  int* matrix = nullptr;

  if (rank == 0) {
    matrix = randomMatrix(n, m);
  }

  int* max = parallelMax(matrix, n, m);

  if (rank == 0) {
    int* reference_max = sequentialMax(matrix, n, m);

    for (int i = 0; i < n; i++) {
      ASSERT_EQ(reference_max[i], max[i]);
    }
  }
}

TEST(Matrix_row_max_elem_MPI, Matrix_10x30) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 10, m = 30;
  int* matrix = nullptr;

  if (rank == 0) {
    matrix = randomMatrix(n, m);
  }

  int* max = parallelMax(matrix, n, m);

  if (rank == 0) {
    int* reference_max = sequentialMax(matrix, n, m);

    for (int i = 0; i < n; i++) {
      ASSERT_EQ(reference_max[i], max[i]);
    }
  }
}

TEST(Matrix_row_max_elem_MPI, Matrix_50x40) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 50, m = 40;
  int* matrix = nullptr;

  if (rank == 0) {
    matrix = randomMatrix(n, m);
  }

  int* max = parallelMax(matrix, n, m);

  if (rank == 0) {
    int* reference_max = sequentialMax(matrix, n, m);

    for (int i = 0; i < n; i++) {
      ASSERT_EQ(reference_max[i], max[i]);
    }
  }
}

TEST(Matrix_row_max_elem_MPI, Matrix_100x100) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 100, m = 100;
  int* matrix = nullptr;

  if (rank == 0) {
    matrix = randomMatrix(n, m);
  }

  int* max = parallelMax(matrix, n, m);

  if (rank == 0) {
    int* reference_max = sequentialMax(matrix, n, m);

    for (int i = 0; i < n; i++) {
      ASSERT_EQ(reference_max[i], max[i]);
    }
  }
}

TEST(Matrix_row_max_elem_MPI, Matrix_200x100) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int n = 200, m = 100;
  int* matrix = nullptr;

  if (rank == 0) {
    matrix = randomMatrix(n, m);
  }

  int* max = parallelMax(matrix, n, m);

  if (rank == 0) {
    int* reference_max = sequentialMax(matrix, n, m);

    for (int i = 0; i < n; i++) {
      ASSERT_EQ(reference_max[i], max[i]);
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
