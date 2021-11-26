// Copyright 2021 TexHik620953
#include <iostream>
#ifndef MODULES_TASK_2_RODIONOV_N_BROADCAST_MESSAGE_BROADCAST_MESSAGE_H_
#define MODULES_TASK_2_RODIONOV_N_BROADCAST_MESSAGE_BROADCAST_MESSAGE_H_

int BroadcastSum(
    void* sendbuf,
    void* outSum,
    int count,
    int root,
    MPI_Op op,
    MPI_Datatype type
);
int randint(int min, int max);
#endif  // MODULES_TASK_2_RODIONOV_N_BROADCAST_MESSAGE_BROADCAST_MESSAGE_H_
