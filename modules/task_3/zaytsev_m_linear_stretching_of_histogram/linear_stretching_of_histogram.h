// Copyright 2021 Zaytsev Mikhail
#ifndef MODULES_TASK_3_ZAYTSEV_M_LINEAR_STRETCHING_OF_HISTOGRAM_LINEAR_STRETCHING_OF_HISTOGRAM_H_
#define MODULES_TASK_3_ZAYTSEV_M_LINEAR_STRETCHING_OF_HISTOGRAM_LINEAR_STRETCHING_OF_HISTOGRAM_H_

#include <vector>

void findMaxAndMinValue(const std::vector<double>& matrix, std::vector<double>::size_type matrixRows,
    std::vector<double>::size_type matrixColumns, double* maxValue, double* minValue);

void getRandomMatrix(std::vector<double>* matrix, std::vector<double>::size_type matrixSize);

std::vector<double> getSequentialOperations(const std::vector<double>& matrix,
    std::vector<double>::size_type matrixRows, std::vector<double>::size_type matrixColumns,
    const double maxValue, const double minValue);
std::vector<double> getParallelOperations(const std::vector<double>& matrix, std::vector<double>::size_type matrixRows,
    std::vector<double>::size_type matrixColumns);

#endif  // MODULES_TASK_3_ZAYTSEV_M_LINEAR_STRETCHING_OF_HISTOGRAM_LINEAR_STRETCHING_OF_HISTOGRAM_H_
