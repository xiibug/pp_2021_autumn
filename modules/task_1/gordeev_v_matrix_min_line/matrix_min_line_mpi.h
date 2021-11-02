// Copyright 2021 Gordeev Viktor
#ifndef MODULES_TASK_1_GORDEEV_V_MATRIX_MIN_LINE_MATRIX_MIN_LINE_MPI_H_
#define MODULES_TASK_1_GORDEEV_V_MATRIX_MIN_LINE_MATRIX_MIN_LINE_MPI_H_

#include <vector>
#include <string>

int* getRandomVector(int rows, int columns);
int* getSequentialMatrixMinLine(int* vec,
    int count_rows_vector, int count_columns_vector);
int* getParallelMatrixMinLine(int* global_vec,
    int count_rows_vector, int count_columns_vector);
int minSearch(int a, int b);

#endif  // MODULES_TASK_1_GORDEEV_V_MATRIX_MIN_LINE_MATRIX_MIN_LINE_MPI_H_
