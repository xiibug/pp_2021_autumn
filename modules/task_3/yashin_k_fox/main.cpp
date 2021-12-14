// Copyright 2021 Yashin Kirill

#include <gtest/gtest.h>
#include "./fox.h"
#include <cmath>
#include <gtest-mpi-listener.hpp>

TEST(fox, Test_on_Matrix_size_4) {
  int size = 4;
  double tmp;
  double* A = &tmp;
  double* B = &tmp;
  double* C = &tmp;
  double* C_fox = &tmp;
  int rank, procNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &procNum);

  int cartSize = static_cast<int>(std::sqrt(procNum));
  if (cartSize * cartSize == procNum && size % cartSize == 0) {
    if (rank == 0) {
      A = new double[size * size];
      B = new double[size * size];
      A = random_matrix(size);
      B = random_matrix(size);
      C = new double[size * size];
      C_fox = new double[size * size];
      sequential_alg(A, B, C, size);
    }
    int result = fox(A, B, C_fox, size);

    if (rank == 0) {
      for (int i = 0; i < size * size; ++i) {
        ASSERT_NEAR(C_fox[i], C[i], 0.0001);
      }
    }

    if (rank == 0) {
      delete[] A;
      delete[] B;
      delete[] C;
      delete[] C_fox;
    }
  }
}

TEST(fox, Test_on_Matrix_size_16) {
  int size = 16;
  double tmp;
  double* A = &tmp;
  double* B = &tmp;
  double* C = &tmp;
  double* C_fox = &tmp;
  int rank, procNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &procNum);

  int cartSize = static_cast<int>(std::sqrt(procNum));
  if (cartSize * cartSize == procNum && size % cartSize == 0) {
    if (rank == 0) {
      A = new double[size * size];
      B = new double[size * size];
      A = random_matrix(size);
      B = random_matrix(size);
      C = new double[size * size];
      C_fox = new double[size * size];
      sequential_alg(A, B, C, size);
    }
    int result = fox(A, B, C_fox, size);

    if (rank == 0) {
      for (int i = 0; i < size * size; ++i) {
        ASSERT_NEAR(C_fox[i], C[i], 0.0001);
      }
    }

    if (rank == 0) {
      delete[] A;
      delete[] B;
      delete[] C;
      delete[] C_fox;
    }
  }
}

TEST(fox, Test_on_Matrix_size_64) {
  int size = 64;
  double temp;
  double* A = &temp;
  double* B = &temp;
  double* C = &temp;
  double* C_fox = &temp;
  int rank, procNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &procNum);

  int cartSize = static_cast<int>(std::sqrt(procNum));
  if (cartSize * cartSize == procNum && size % cartSize == 0) {
    if (rank == 0) {
      A = new double[size * size];
      B = new double[size * size];
      A = random_matrix(size);
      B = random_matrix(size);
      C = new double[size * size];
      C_fox = new double[size * size];
      sequential_alg(A, B, C, size);
    }
    int result = fox(A, B, C_fox, size);

    if (rank == 0) {
      for (int i = 0; i < size * size; ++i) {
        ASSERT_NEAR(C_fox[i], C[i], 0.0001);
      }
    }

    if (rank == 0) {
      delete[] A;
      delete[] B;
      delete[] C;
      delete[] C_fox;
    }
  }
}

TEST(fox, Test_on_Matrix_size_100) {
  int size = 100;
  double temp;
  double* A = &temp;
  double* B = &temp;
  double* C = &temp;
  double* C_fox = &temp;
  int rank, procNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &procNum);

  int cartSize = static_cast<int>(std::sqrt(procNum));
  if (cartSize * cartSize == procNum && size % cartSize == 0) {
    if (rank == 0) {
      A = new double[size * size];
      B = new double[size * size];
      A = random_matrix(size);
      B = random_matrix(size);
      C = new double[size * size];
      C_fox = new double[size * size];
      sequential_alg(A, B, C, size);
    }
    int result = fox(A, B, C_fox, size);

    if (rank == 0) {
      for (int i = 0; i < size * size; ++i) {
        ASSERT_NEAR(C_fox[i], C[i], 0.0001);
      }
    }

    if (rank == 0) {
      delete[] A;
      delete[] B;
      delete[] C;
      delete[] C_fox;
    }
  }
}

TEST(fox, Test_on_Matrix_size_256) {
  int size = 256;
  double temp;
  double* A = &temp;
  double* B = &temp;
  double* C = &temp;
  double* C_fox = &temp;
  int rank, procNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &procNum);

  int cartSize = static_cast<int>(std::sqrt(procNum));
  if (cartSize * cartSize == procNum && size % cartSize == 0) {
    if (rank == 0) {
      A = new double[size * size];
      B = new double[size * size];
      A = random_matrix(size);
      B = random_matrix(size);
      C = new double[size * size];
      C_fox = new double[size * size];
      sequential_alg(A, B, C, size);
    }
    int result = fox(A, B, C_fox, size);

    if (rank == 0) {
      for (int i = 0; i < size * size; ++i) {
        ASSERT_NEAR(C_fox[i], C[i], 0.0001);
      }
    }

    if (rank == 0) {
      delete[] A;
      delete[] B;
      delete[] C;
      delete[] C_fox;
    }
  }
}

TEST(Fox, Throw_Matrix_size_17) {
  int size = 17;
  double tmp;
  double* matrix = &tmp;
  int procNum;
  MPI_Comm_size(MPI_COMM_WORLD, &procNum);
  if (procNum > 1) {
    ASSERT_EQ(fox(matrix, matrix, matrix, size), -1);
  }
}

TEST(fox, Throw_Matrix_size_0) {
  int size = 0;
  double tmp;
  double* matrix = &tmp;
  ASSERT_EQ(fox(matrix, matrix, matrix, size), -1);
  ASSERT_EQ(sequential_alg(matrix, matrix, matrix, size), -1);
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
