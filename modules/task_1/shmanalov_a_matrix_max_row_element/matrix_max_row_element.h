// Copyright 2021 Shmanalov Alexander
#ifndef MODULES_TASK_1_SHMANALOV_A_MATRIX_MAX_ROW_ELEMENT_MATRIX_MAX_ROW_ELEMENT_H_
#define MODULES_TASK_1_SHMANALOV_A_MATRIX_MAX_ROW_ELEMENT_MATRIX_MAX_ROW_ELEMENT_H_

void generationRandomMatrix(int** matrix, int rows, int columns);
int* matrixToVector(int** matrix, int rows, int columns);
void sequentialSearchMaxElements(int** matrix, int* result,
    int rows, int columns);
void parallelSearchMaxElements(int** matrix, int* result,
    int rows, int columns);

#endif  // MODULES_TASK_1_SHMANALOV_A_MATRIX_MAX_ROW_ELEMENT_MATRIX_MAX_ROW_ELEMENT_H_
