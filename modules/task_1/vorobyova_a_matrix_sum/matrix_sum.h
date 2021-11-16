// Copyright 2018 Nesterov Alexander
#ifndef MODULES_TASK_1_NESTEROV_A_TEST_TASK_1_OPS_MPI_H_
#define MODULES_TASK_1_NESTEROV_A_TEST_TASK_1_OPS_MPI_H_

int* getRandomMatrix(int size);
int getSequentialSum(int* matrix, int size);
int getParallelSum(int* matrix, int msize);

#endif  // MODULES_TASK_1_NESTEROV_A_TEST_TASK_1_OPS_MPI_H_
