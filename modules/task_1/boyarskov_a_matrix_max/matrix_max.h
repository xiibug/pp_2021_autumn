// Copyright 2021 Boyarskov Anton
#ifndef MODULES_TASK_1_NESTEROV_A_TEST_TASK_1_OPS_MPI_H_
#define MODULES_TASK_1_NESTEROV_A_TEST_TASK_1_OPS_MPI_H_

int* getRandomMatrix(int n, int m);
int getSequentialMax(int* matrix, int n, int m);
int getParallelMax(int* matrix, int n, int m);

#endif  // MODULES_TASK_1_NESTEROV_A_TEST_TASK_1_OPS_MPI_H_
