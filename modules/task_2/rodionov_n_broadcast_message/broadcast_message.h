// Copyright 2021 TexHik620953
#include <iostream>
#ifndef MODULES_TASK_1_RODIONOV_N_CHECKING_LEXICOGRAPHIC_ORDERING_LEX_ORDERING_H_
#define MODULES_TASK_1_RODIONOV_N_CHECKING_LEXICOGRAPHIC_ORDERING_LEX_ORDERING_H_

int BroadcastSum(
    void* sendbuf,
    void* outSum,
    int count,
    int root,
    MPI_Op op,
    MPI_Datatype type
);

#endif  // MODULES_TASK_1_RODIONOV_N_CHECKING_LEXICOGRAPHIC_ORDERING_LEX_ORDERING_H_
