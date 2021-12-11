// Copyright 2021 Utyugov Denis
#ifndef MODULES_TASK_2_UTYUGOV_D_TRANSFER_ALL_TO_ONE_TRANSFER_ALL_TO_ONE_H_
#define MODULES_TASK_2_UTYUGOV_D_TRANSFER_ALL_TO_ONE_TRANSFER_ALL_TO_ONE_H_

#include <mpi.h>

#include <string>
#include <vector>

std::vector<int> getRandomVector(int sz);
int MY_Reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype,
              MPI_Op op, int root, MPI_Comm comm);
#endif  // MODULES_TASK_2_UTYUGOV_D_TRANSFER_ALL_TO_ONE_TRANSFER_ALL_TO_ONE_H_
