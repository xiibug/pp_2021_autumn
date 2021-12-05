// Copyright 2021 Barysheva Maria
#include "../../../modules/task_1/barysheva_m_matrix_max_row_elem/matrix_max_row_elem.h"

#include <mpi.h>

#include <random>

int* randomMatrix(int n, int m) {
  if (n <= 0 || m <= 0) throw -1;
  std::random_device dev;
  std::mt19937 gen(dev());
  int* a = new int[n * m];
  for (int i = 0; i < n * m; i++) a[i] = gen() % 100;

  return a;
}

int* sequentialMax(int* matrix, int n, int m) {
  if (n <= 0 || m <= 0) throw -1;

  int* max = new int[n];
  for (int i = 0; i < n; i++) {
    max[i] = matrix[i * m];
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (matrix[j + i * m] > max[i]) {
        max[i] = matrix[j + i * m];
      }
    }

  return max;
}

int* parallelMax(int* global_matrix, int n, int m) {
  if (n <= 0 || m <= 0) throw -1;

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  const int delta = n / world_size;

  if (delta) {
    int* local_matrix = new int[delta * m];

    MPI_Scatter(global_matrix, delta * m, MPI_INT, local_matrix, delta * m,
                MPI_INT, 0, MPI_COMM_WORLD);

    int* local_max = sequentialMax(local_matrix, delta, m);

    int* global_max = new int[n];

    MPI_Gather(local_max, delta, MPI_INT, global_max, delta, MPI_INT, 0,
               MPI_COMM_WORLD);

    if (n % world_size) {
      if (world_rank == 0) {
        for (int i = delta * world_size; i < n; i++) {
          global_max[i] = global_matrix[i * m];
          for (int j = 0; j < m; j++)
            if (global_matrix[j + i * m] > global_max[i]) {
              global_max[i] = global_matrix[j + i * m];
            }
        }
      }
    }

    return global_max;

  } else {
    if (world_rank == 0) {
      return sequentialMax(global_matrix, n, m);
    } else {
      return nullptr;
    }
  }
}
