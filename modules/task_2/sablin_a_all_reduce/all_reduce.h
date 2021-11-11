// Copyright 2021 Sablin Alexander
#ifndef MODULES_TASK_1_SABLIN_A_ALL_REDUCE_ALL_REDUCE_H_
#define MODULES_TASK_1_SABLIN_A_ALL_REDUCE_ALL_REDUCE_H_

#include <mpi.h>

template<typename T>
T* getRandomVector(T* rand_vec, int n, int dia, bool flag);

int Allreduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype type,
    MPI_Op Op, MPI_Comm Comm);

#endif  //MODULES_TASK_1_SABLIN_A_ALL_REDUCE_ALL_REDUCE_H_
