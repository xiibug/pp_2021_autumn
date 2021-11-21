//Copyright 2021 Kuklin Andrey
#ifndef MODULES_TASK_1_KUKLIN_A_MATRIX_SUM_MATRIX_SUM_H_
#define MODULES_TASK_1_KUKLIN_A_MATRIX_SUM_MATRIX_SUM_H_

#include <vector>

std::vector<std::vector<int>> getRandMatrix(int sizei, int sizej);
int matrixSumSequential(std::vector<int> vec);
int matrixSumParal(std::vector<std::vector<int>> mat, int sizei, int sizej);

#endif // MODULES_TASK_1_KUKLIN_A_MATRIX_SUM_MATRIX_SUM_H_