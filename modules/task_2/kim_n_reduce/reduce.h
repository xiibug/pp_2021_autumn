// Copyright 2021 Kim Nikita
#ifndef MODULES_TASK_2_KIM_N_REDUCE_REDUCE_H_
#define MODULES_TASK_2_KIM_N_REDUCE_REDUCE_H_

#include <mpi.h>
#include <vector>

template <class T>
std::vector<T> getRandomVector(int size);

int Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype type, MPI_Op op, int root, MPI_Comm comm);

#endif  // MODULES_TASK_2_KIM_N_REDUCE_REDUCE_H_
