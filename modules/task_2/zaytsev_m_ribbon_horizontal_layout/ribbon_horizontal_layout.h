// Copyright 2021 Zaytsev Mikhail
#ifndef MODULES_TASK_2_ZAYTSEV_M_RIBBON_HORIZONTAL_LAYOUT_RIBBON_HORIZONTAL_LAYOUT_H_
#define MODULES_TASK_2_ZAYTSEV_M_RIBBON_HORIZONTAL_LAYOUT_RIBBON_HORIZONTAL_LAYOUT_H_

#include <vector>

void getRandomVector(std::vector<int>* vector, std::vector<int>::size_type vectorSize);
void getRandomMatrix(std::vector<int>* matrix, std::vector<int>::size_type matrixSize);

std::vector<int> getSequentialOperations(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                             std::vector<int>::size_type matrixColumns, std::vector<int> vector);
std::vector<int> getParallelOperations(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                           std::vector<int>::size_type matrixColumns, std::vector<int> vector);

#endif  // MODULES_TASK_2_ZAYTSEV_M_RIBBON_HORIZONTAL_LAYOUT_RIBBON_HORIZONTAL_LAYOUT_H_
