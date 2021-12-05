// Copyright 2021 Zaytsev Alexander
#include "../../../modules/task_1/zaytsev_a_min_elem_of_vector/min_elem_of_vector.h"

#include <mpi.h>

#include <random>
#include <vector>

int* RandomVector(int size) {
  std::random_device dev;
  std::mt19937 gen(dev());
  int* our_vector = new int[size];
  for (int a = 0; a < size; a++) {
    our_vector[a] = gen() % 100;
  }
  return our_vector;
}
int SequentialMin(int* our_vector, const int count_size_vector) {
  int min_elem;
  min_elem = our_vector[0];
  for (int i = 1; i < count_size_vector; i++)
    if (min_elem > our_vector[i]) min_elem = our_vector[i];
  return min_elem;
}

int ParallelMin(int* global_our_vector, const int count_size_vector) {
  int *Send = nullptr, *local_vector = nullptr;
  int our_size, our_rank, TotalMin, SeqMin, Buffer_Size;
  MPI_Comm_size(MPI_COMM_WORLD, &our_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &our_rank);
  if (our_rank == 0) {
    local_vector = new int[our_size];
    Send = new int[our_size];
    int delta = count_size_vector % our_size;
    int summ = 0;
    for (int i = 0; i < our_size; i++) {
      Send[i] = (count_size_vector / our_size);
      if (delta > 0) {
        Send[i] += 1;
        delta--;
      }
      local_vector[i] = summ;
      summ += Send[i];
    }
  }
  MPI_Scatter(Send, 1, MPI_INT, &Buffer_Size, 1, MPI_INT, 0, MPI_COMM_WORLD);
  int* Buffer = new int[Buffer_Size];
  MPI_Scatterv(global_our_vector, Send, local_vector, MPI_INT, Buffer,
               Buffer_Size, MPI_INT, 0, MPI_COMM_WORLD);
  SeqMin = SequentialMin(Buffer, Buffer_Size);
  MPI_Reduce(&SeqMin, &TotalMin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
  if (our_rank == 0) {
    delete[] local_vector;
    delete[] Send;
  }
  delete[] Buffer;
  return TotalMin;
}
