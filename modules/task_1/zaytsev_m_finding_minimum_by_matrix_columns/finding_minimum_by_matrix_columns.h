// Copyright 2021 Zaytsev Mikhail
#ifndef MODULES_TASK_1_ZAYTSEV_M_FINDING_MINIMUM_BY_MATRIX_COLUMNS_FINDING_MINIMUM_BY_MATRIX_COLUMNS_H_
#define MODULES_TASK_1_ZAYTSEV_M_FINDING_MINIMUM_BY_MATRIX_COLUMNS_FINDING_MINIMUM_BY_MATRIX_COLUMNS_H_

#include <vector>

void getRandomMatrix(std::vector<int>* matrix, std::vector<int>::size_type matrixSize);

std::vector<int> getSequentialOperations(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                                                      std::vector<int>::size_type matrixColumns);
std::vector<int> getParallelOperations(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                                                    std::vector<int>::size_type matrixColumns);

#endif  // MODULES_TASK_1_ZAYTSEV_M_FINDING_MINIMUM_BY_MATRIX_COLUMNS_FINDING_MINIMUM_BY_MATRIX_COLUMNS_H_
