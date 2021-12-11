// Copyright 2021 Lakhov Kirill
#ifndef MODULES_TASK_1_LAKHOV_K_MATRIX_COL_SUM_MATRIX_COL_SUM_H_
#define MODULES_TASK_1_LAKHOV_K_MATRIX_COL_SUM_MATRIX_COL_SUM_H_
#include <mpi.h>
#include <vector>
#include <random>

std::vector<int> getRandomVector(int sz);

std::vector<std::vector<int>> getRandomMatrix(int rows, int cols);

int sequentialCalc(std::vector<std::vector<int>> vect, int rows, int cols);

int parallelCalc(std::vector<std::vector<int>> vect, int rows, int cols);

#endif  // MODULES_TASK_1_LAKHOV_K_MATRIX_COL_SUM_MATRIX_COL_SUM_H_
