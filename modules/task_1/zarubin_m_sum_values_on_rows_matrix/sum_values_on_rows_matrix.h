// Copyright 2021 Zarubin Mikhail
#ifndef MODULES_TEST_TASKS_TEST_MPI_OPS_MPI_H_
#define MODULES_TEST_TASKS_TEST_MPI_OPS_MPI_H_

#include <vector>

void generateRandomMatrix(std::vector<int>& matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column);
std::vector<int> transposeMatrix(const std::vector<int>& matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column);
std::vector<int> getParallelOperations(const std::vector<int>& matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column);
std::vector<int> getSequentialOperations(const std::vector<int>& matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column);

#endif  // MODULES_TEST_TASKS_TEST_MPI_OPS_MPI_H_
