// Copyright 2021 Kutuev Roman
#include "../../../modules/task_1/kutuev_r_col_sum/col_sum.h"

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

int* sequentialSum(int* matrix, int n, int m) {
  if (n <= 0 || m <= 0) throw -1;
  int* answer = new int[m];
  for (int i = 0; i < m; i++) answer[i] = 0;

  for (int j = 0; j < m; j++)
    for (int i = 0; i < n; i++) answer[j] += matrix[j + i * m];

  return answer;
}

int* parallelSum(int* global_matrix, int n, int m) {
  if (n <= 0 || m <= 0) throw -1;

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int* local_matrix;
  int *local_sum, *global_sum;

  const int delta = n / world_size;

  if (delta) {
    local_matrix = new int[delta * m];

    MPI_Scatter(global_matrix, delta * m, MPI_INT, local_matrix, delta * m,
                MPI_INT, 0, MPI_COMM_WORLD);

    local_sum = sequentialSum(local_matrix, delta, m);

    global_sum = new int[m];

    MPI_Reduce(local_sum, global_sum, m, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  } else {
    if (world_rank == 0) {
      return sequentialSum(global_matrix, n, m);
    } else {
      return nullptr;
    }
  }

  if (n % world_size) {
    if (world_rank == 0) {
      for (int j = 0; j < m; j++)
        for (int i = delta * world_size; i < n; i++)
          global_sum[j] += global_matrix[j + i * m];
    }
  }

  return global_sum;
}
