// Copyright 2021 Troegubova Alexandra
#ifndef MODULES_TASK_1_TROEGUBOVA_A_MAX_MATRIX_VAL_MAX_MATRIX_VAL_H_
#define MODULES_TASK_1_TROEGUBOVA_A_MAX_MATRIX_VAL_MAX_MATRIX_VAL_H_

#include <vector>

std::vector<int> getRandomMatrix(int lines, int columns);
int getSequentialMax(const std::vector<int> &matrix);
int getParallelMax(const std::vector<int> &matrix, const int matrix_size);

#endif  //MODULES_TASK_1_TROEGUBOVA_A_MAX_MATRIX_VAL_MAX_MATRIX_VAL_H_


