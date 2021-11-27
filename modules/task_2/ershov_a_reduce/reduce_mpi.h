// Copyright 2021 Ershov Alexey
#ifndef MODULES_TASK_2_MPI_H_
#define MODULES_TASK_2_MPI_H_

#include <mpi.h>

template <typename T>
T* getRandomVector(size_t size);

int reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype type,
           MPI_Op op, int root, MPI_Comm comm);

#endif  // MODULES_TASK_2_MPI_H_
