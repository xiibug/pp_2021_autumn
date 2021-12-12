// Copyright 2021 Kirillov Nikita
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./min_value_in_line_matrix.h"

TEST(Parallel_Operations_MPI, test_sequential) {
  int rank;
  int n = 0;
  int h = 6;
  int w = 3;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int realResult[10] = {0, 3, 6, 9, 12, 15};
  int* result = new int[h];
  int** matrix = getRandomMatrix(w, h);
  if (rank == 0) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        matrix[i][j] = n;
        n += 1;
      }
    }
  }
  if (rank == 0) {
    result = getSequentialOperations(matrix, w, h);
    for (int i = 0; i < h; i++) {
      ASSERT_EQ(result[i], realResult[i]);
    }
  }
}

TEST(Parallel_Operations_MPI, test_parallel) {
  int rank;
  int n = 0;
  int h = 6;
  int w = 3;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int realResult[10] = {0, 3, 6, 9, 12, 15};
  int* result = new int[h];
  int* _matrix = new int[h * w];
  int** matrix = getRandomMatrix(w, h);
  if (rank == 0) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        matrix[i][j] = n;
        n += 1;
      }
    }
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        _matrix[i * w + j] = matrix[i][j];
      }
    }
  }
  result = getParallelOperations(_matrix, w, h);
  if (rank == 0) {
    for (int i = 0; i < h; i++) {
      ASSERT_EQ(result[i], realResult[i]);
    }
  }
}

TEST(Parallel_Operations_MPI, test_sequential_and_parallel) {
  int rank;
  int h = 50;
  int w = 50;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* parallelResult = new int[h];
  int* sequentialResult = new int[h];
  int** matrix;
  int* _matrix = new int[h * w];
  if (rank == 0) {
    matrix = getRandomMatrix(w, h);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        _matrix[j + i * w] = matrix[i][j];
      }
    }
  }
  parallelResult = getParallelOperations(_matrix, w, h);
  if (rank == 0) {
    sequentialResult = getSequentialOperations(matrix, w, h);
    for (int i = 0; i < h; i++) {
      ASSERT_EQ(sequentialResult[i], parallelResult[i]);
    }
  }
}

TEST(Parallel_Operations_MPI, test_big_height) {
  int rank;
  int h = 1000;
  int w = 50;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* parallelResult = new int[h];
  int* sequentialResult = new int[h];
  int** matrix;
  int* _matrix = new int[h * w];
  if (rank == 0) {
    matrix = getRandomMatrix(w, h);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        _matrix[j + i * w] = matrix[i][j];
      }
    }
  }
  parallelResult = getParallelOperations(_matrix, w, h);
  if (rank == 0) {
    sequentialResult = getSequentialOperations(matrix, w, h);
    for (int i = 0; i < h; i++) {
      ASSERT_EQ(sequentialResult[i], parallelResult[i]);
    }
  }
}

TEST(Parallel_Operations_MPI, test_big_width) {
  int rank;
  int h = 50;
  int w = 1000;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int* parallelResult = new int[h];
  int* sequentialResult = new int[h];
  int** matrix;
  int* _matrix = new int[h * w];
  if (rank == 0) {
    matrix = getRandomMatrix(w, h);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        _matrix[j + i * w] = matrix[i][j];
      }
    }
  }
  parallelResult = getParallelOperations(_matrix, w, h);
  if (rank == 0) {
    sequentialResult = getSequentialOperations(matrix, w, h);
    for (int i = 0; i < h; i++) {
      ASSERT_EQ(sequentialResult[i], parallelResult[i]);
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
