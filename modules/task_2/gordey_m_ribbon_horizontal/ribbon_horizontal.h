// Copyright 2021 Gordey Maria
#ifndef MODULES_TASK_2_GORDEY_M_RIBBON_HORIZONTAL_RIBBON_HORIZONTAL_H_
#define MODULES_TASK_2_GORDEY_M_RIBBON_HORIZONTAL_RIBBON_HORIZONTAL_H_

int* initEmptyMatrix(int rows, int cols);
int* getRandomMatrix(int rows, int cols);
void SequentialMatrixMultiplication(int* A, int ARows, int ACols,
    int* B, int BRows, int BCols, int* C);
void ParallelMatrixMultiplication(int* A, int ARows, int ACols,
    int* B, int BRows, int BCols, int* C);

#endif  // MODULES_TASK_2_GORDEY_M_RIBBON_HORIZONTAL_RIBBON_HORIZONTAL_H_
