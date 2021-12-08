// Copyright 2021 Zaytsev Alexander
#include "../../../modules/task_2/zaytsev_a_linear_topology/linear_topology.h"

#include <mpi.h>
MPI_Comm Linar(const MPI_Comm comm, int size) {
  int size_index, *index, size_enges, *enges, step = 0;
  MPI_Comm LineComm;
  size_index = size;
  index = new int[size_index];
  size_enges = 2 * size_index - 2;
  for (int i = 0; i < size_index; i++) {
    if (i == 0)
      index[i] = 1;
    else if (i == size_index - 1)
      index[i] = index[size_index - 2] + 1;
    else
      index[i] = index[i - 1] + 2;
  }
  enges = new int[size_enges];
  enges[0] = 1;
  for (int i = 1; i < size_enges; i++) {
    enges[i] = step;
    if (i % 2 != 0)
      step += 2;
    else
      step -= 1;
  }
  MPI_Graph_create(comm, size, index, enges, 0, &LineComm);
  return LineComm;
}
