// Copyright 2021 Utyugov Denis
#include "../../../modules/task_1/utyugov_d_avarage_of_el_of_vec/avarage_of_el_of_vec.h"

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

int getSequentialOperations(std::vector<int> vec) {
  const int sz = vec.size();
  int reduction_elem = 0;
  for (int i = 0; i < sz; i++) {
    reduction_elem += vec[i];
  }
  return reduction_elem;
}

int getParallelOperations(std::vector<int> global_vec, int count_size_vector) {
  if (count_size_vector == 0) {
    throw "Error";
  }
  int size, rank;
  int sum = 0;
  int global_sum = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // This funcs is int - they return result of work

  /* MPI_Send - send data. (buff, count of data, Type of data, rank of
     proccess-recipient, Tag, comm) first 3 parametrs is deffualt MPI_Recv -
     reception of data. (Buff for rec. data, Count, Type, root-proc, Tag, Comm,
     Status).

     MPI_Bcast (3 standarts, root, comm) - efficient data transfer (full data).
     MPI_Reduce - take reuslts from all proc (Buff with msg, Buff for new
     msg, Count of msg, Type el, Operation, root, comm).

     MPI_Scatter - sending chunks of data (Data, Count, Type,
     Reduce data: Data, Count, Type, root, Comm).
  */

  int count_zeros = 0;
  if (count_size_vector % size) {
    count_zeros = size - count_size_vector % size;
    for (int i = 0; i < count_zeros; i++) {
      global_vec.push_back(0);
      count_size_vector++;
    }
  }
  const int delta = count_size_vector / size;
  int *proc_counts = new int(size);
  if (rank == 0) {
    for (int i = 0; i < size; i++) {
      proc_counts[i] = delta;
    }
    proc_counts[size - 1] += size - count_size_vector % size;
  }
  std::vector<int> proc_el(delta);

  MPI_Scatter(global_vec.data(), delta, MPI_INT, proc_el.data(), delta, MPI_INT,
              0, MPI_COMM_WORLD);

  sum = getSequentialOperations(proc_el);
  MPI_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  return global_sum;
}

double getAvarage(int Sum, int count_size_vector) {
  double Avarage = Sum;
  Avarage = Avarage / count_size_vector;
  return Avarage;
}
