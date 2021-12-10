// Copyright 2021 Yashina Darya
#include "../../../modules/task_2/yashina_d_ribbon_vertical/ribbon_vertical.h"

#include <mpi.h>

#include <random>

int* initEmptyMatrix(int rows) {
  int* matrix = new int[rows];
  for (int i = 0; i < rows; i++) {
    matrix[i] = 0;
  }
  return matrix;
}

int* getRandomMatrix(int rows, int cols) {
  std::random_device dev;
  std::mt19937 gen(dev());
  int* matrix = new int[rows * cols];
  for (int i = 0; i < rows * cols; i++) {
    matrix[i] = gen() % 20;
  }
  return matrix;
}

void SequentialMatrixMultiplication(const int* A, const int ARows,
                                    const int ACols, const int* B,
                                    const int BRows, int* C) {
  for (int i = 0; i < ARows; i++) {
    C[i] = 0;
    int tmp = 0;
    for (int k = 0; k < ACols; k++) {
      tmp += A[i * ACols + k] * B[k];
      C[i] = tmp;
    }
  }
}

void ParallelMatrixMultiplication(const int* A, const int ARows,
                                  const int ACols, const int* B,
                                  const int BRows, int* C) {
  if (ACols != BRows) {
    throw -1;
  }

  int world_size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const int ribbon_width = ACols / world_size;
  const int remainder = ACols % world_size;
  int* ribbon = nullptr;
  int* local_vector = nullptr;

  int temp = 0;
  if (rank == 0) {
    temp = remainder;
  }

  ribbon = new int[ARows * (ribbon_width + temp)];
  local_vector = initEmptyMatrix(ARows);

  for (int i = 0; i < ARows; i++) {
    MPI_Scatter(A + remainder + i * ACols, ribbon_width, MPI_INT,
                ribbon + temp + i * (ribbon_width + temp), ribbon_width,
                MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
      for (int j = 0; j < remainder; j++) {
        ribbon[j + i * (ribbon_width + temp)] = A[j + i * ACols];
      }
    }
  }

  // printf("Rank %d\n", rank);
  // for (int i = 0; i < ARows; i++) {
  //  for (int j = 0; j < ribbon_width + temp; j++) {
  //    printf("%d ", ribbon[j + i * (ribbon_width + temp)]);
  //  }
  //  printf("\n");
  //}
  // fflush(stdout);

  for (int i = 0; i < ribbon_width + temp; i++) {
    for (int j = 0; j < ARows; j++) {
      if (rank == 0) {
        local_vector[j] +=
            ribbon[i + j * (ribbon_width + temp)] * B[i + ribbon_width * rank];
      } else {
        local_vector[j] += ribbon[i + j * (ribbon_width + temp)] *
                           B[i + ribbon_width * rank + remainder];
      }
    }
  }

  // printf("Result: Rank %d\n", rank);
  // for (int i = 0; i < ARows; i++) {
  //    printf("%d ", local_vector[i]);
  //  printf("\n");
  //}
  // fflush(stdout);

  MPI_Reduce(local_vector, C, ARows, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}
