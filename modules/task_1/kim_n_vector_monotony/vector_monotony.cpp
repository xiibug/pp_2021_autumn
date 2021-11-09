// Copyright 2021 Kim Nikita
#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_1/kim_n_vector_monotony/vector_monotony.h"


std::vector<int> getRandomVector(int size) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> res(size);
  for (int i = 0; i < size; i++)
    res[i] = gen() % 100;
  return res;
}

int getNumNonMonotonyElems(std::vector<int> input_vec, int size, int direction) {
  int count = 0;
  for (int i = 1; i < size; i++)
    if ((input_vec[i] - input_vec[i - 1]) * direction < 0)
      count++;
  return count;
}

int getNumNonMonotonyElemsParall(std::vector<int> input_vec, int size, int direction) {
  int proc_num, proc_rank;
  int global_count = 0, local_count = 0;
  std::vector<int> local_vec(size);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
  int range = size / proc_num + 1;
  int start = proc_rank * (range - 1) + 1;
  int end;
  if (proc_rank == proc_num - 1)
    end = size;
  else
    end = proc_rank * (range - 1) + range;
  if (proc_rank == 0) {
    for (int i = 1; i < proc_num; i++)
      MPI_Send(input_vec.data(), size, MPI_INT, i, 0, MPI_COMM_WORLD);
    local_vec = input_vec;
  } else {
    MPI_Status status;
    MPI_Recv(local_vec.data(), size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  }
  for (int i = start; i < end; i++)
    if ((local_vec[i] - local_vec[i - 1]) * direction < 0)
      local_count++;
  MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  return global_count;
}
