// Copyright 2021 Mironova Ekaterina
#ifndef MODULES_TASK_1_MIRONOVA_E_MAX_IN_MATRIX_ROWS_MAX_IN_MATRIX_ROWS_H_
#define MODULES_TASK_1_MIRONOVA_E_MAX_IN_MATRIX_ROWS_MAX_IN_MATRIX_ROWS_H_

#include <vector>
#include "mpi.h"

std::vector<int> fillRandomMatrix(const int rows, const int columns);
std::vector<int> findMaxesInMatrixRows(std::vector<int> matrix, const int columns);
std::vector<int> parallelFindMaxesInMatrixRows(std::vector<int> matrix, const int rows, const int columns);

#endif //MODULES_TASK_1_MIRONOVA_E_MAX_IN_MATRIX_ROWS_MAX_IN_MATRIX_ROWS_H_
