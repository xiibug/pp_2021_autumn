// Copyright 2021 Shabunin Vladislav
#include "../../../modules/task_1/shabunin_v_vector_max/vector_max.h"

#include <mpi.h>

#include <random>
#include <vector>

std::vector<int> getRandomVector(int sz) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = gen() % 100;
  }
  return vec;
}

int getSequentialMax(std::vector<int> vec) {
  const int sz = vec.size();
  int reduction_elem = vec[0];
  for (int i = 1; i < sz; i++) {
    reduction_elem = std::max(reduction_elem, vec[i]);
  }
  return reduction_elem;
}

int getParallelMax(std::vector<int> global_vec, int count_size_vector) {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  const int delta = count_size_vector / size;

  if (delta) {
    const int remnant = count_size_vector % size;

    if (rank == 0) {
      for (int proc = 1; proc < size; proc++) {
        MPI_Send(global_vec.data() + proc * delta + remnant, delta, MPI_INT,
                 proc, 0, MPI_COMM_WORLD);
      }
    }

    std::vector<int> local_vec(delta);
    if (rank == 0) {
      local_vec = std::vector<int>(global_vec.begin(),
                                   global_vec.begin() + delta + remnant);
    } else {
      MPI_Status status;
      MPI_Recv(local_vec.data(), delta, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    int global_max = 0;
    int local_max = getSequentialMax(local_vec);

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    return global_max;

  } else {
    if (rank == 0) {
      return getSequentialMax(global_vec);
    } else {
      return 0;
    }
  }
}
