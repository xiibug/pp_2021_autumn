// Copyright 2021 Kamenev Ilya

#include <gtest/gtest.h>
#include "../../../modules/task_2/kamenev_i_broadcast/broadcast.h"
#include <gtest-mpi-listener.hpp>

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

TEST(BroadcastTest, IntSum) {
  int length = 100;
  int root = 0;
  int mpi_result = 0;
  int seq_sum = 0;
  int* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<int>(length*size, 50);
    for (int i = 0; i < length * size; i++) {
      seq_sum += arr[i];
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_INT, root, MPI_SUM,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_sum, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, IntProd) {
  int length = 100;
  int root = 0;
  int mpi_result = 1;
  int seq_prod = 1;
  int* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<int>(length * size, 3);
    for (int i = 0; i < length * size; i++) {
      seq_prod *= arr[i];
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_INT, root, MPI_PROD,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_prod, 1e-2);
    delete [] arr;
  }
}


TEST(BroadcastTest, IntMin) {
  int length = 100;
  int root = 0;
  int mpi_result = 0;
  int seq_min = INT_MAX;
  int* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<int>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      if (arr[i] < seq_min) {
        seq_min = arr[i];
      }
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_INT, root, MPI_MIN,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_min, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, IntMax) {
  int length = 100;
  int root = 0;
  int mpi_result = 0;
  int seq_max = INT_MIN;
  int* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<int>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      if (arr[i] > seq_max) {
        seq_max = arr[i];
      }
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_INT, root, MPI_MAX,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_max, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, DoubleSum) {
  int length = 100;
  int root = 0;
  double mpi_result = 0;
  double seq_sum = 0;
  double* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<double>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      seq_sum += arr[i];
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_DOUBLE, root, MPI_SUM,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_sum, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, DoubleProd) {
  int length = 100;
  int root = 0;
  double mpi_result = 0;
  double seq_prod = 1;
  double* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<double>(length * size, 3);
    for (int i = 0; i < length * size; i++) {
      seq_prod *= arr[i];
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_DOUBLE, root, MPI_PROD,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_prod, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, DoubleMin) {
  int length = 100;
  int root = 0;
  double mpi_result = 0;
  double seq_min = DBL_MAX;
  double* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<double>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      if (arr[i] < seq_min) {
        seq_min = arr[i];
      }
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_DOUBLE, root, MPI_MIN,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_min, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, DoubleMax) {
  int length = 100;
  int root = 0;
  double mpi_result = 0;
  double seq_max = DBL_MIN;
  double* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<double>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      if (arr[i] > seq_max) {
        seq_max = arr[i];
      }
    }
  }
  Bcast(arr, &mpi_result, length, MPI_DOUBLE, root, MPI_MAX,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_max, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, FloatSum) {
  int length = 100;
  int root = 0;
  float mpi_result = 0;
  float seq_sum = 0;
  float* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<float>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      seq_sum += arr[i];
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_FLOAT, root, MPI_SUM,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_sum, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, FloatProd) {
  int length = 100;
  int root = 0;
  float mpi_result = 0;
  float seq_prod = 1;
  float* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<float>(length * size, 3);
    for (int i = 0; i < length * size; i++) {
      seq_prod *= arr[i];
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_FLOAT, root, MPI_PROD,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_prod, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, FloatMin) {
  int length = 100;
  int root = 0;
  float mpi_result = 0;
  float seq_min = FLT_MAX;
  float* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<float>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      if (arr[i] < seq_min) {
        seq_min = arr[i];
      }
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_FLOAT, root, MPI_MIN,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_min, 1e-2);
    delete[] arr;
  }
}

TEST(BroadcastTest, FloatMax) {
  int length = 100;
  int root = 0;
  float mpi_result = 0;
  float seq_max = FLT_MIN;
  float* arr = nullptr;
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == root) {
    arr = getRandomArray<float>(length * size, 50);
    for (int i = 0; i < length * size; i++) {
      if (arr[i] > seq_max) {
        seq_max = arr[i];
      }
    }
  }
  Bcast(arr, &mpi_result, length * size, MPI_FLOAT, root, MPI_MAX,
        MPI_COMM_WORLD);
  if (rank == root) {
    EXPECT_NEAR(mpi_result, seq_max, 1e-2);
    delete[] arr;
  }
}
