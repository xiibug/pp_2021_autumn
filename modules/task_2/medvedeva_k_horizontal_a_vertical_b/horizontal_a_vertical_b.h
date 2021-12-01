// Copyright 2021 Medvedeva Karina
#ifndef MODULES_TASK_2_MEDVEDEVA_K_HORIZONTAL_A_VERTICAL_B_HORIZONTAL_A_VERTICAL_B_H_
#define MODULES_TASK_2_MEDVEDEVA_K_HORIZONTAL_A_VERTICAL_B_HORIZONTAL_A_VERTICAL_B_H_

#include <vector>

std::vector<int> getRandomMatrix(std::vector<int>::size_type row_count, std::vector<int>::size_type column_count);
std::vector<int> getParallelOperations(std::vector<int> matrix1, std::vector<int> matrix2,
    std::vector<int>::size_type row_count_matrix1, std::vector<int>::size_type column_count_matrix1);
std::vector<int> getSequentialOperations(std::vector<int> matrix1, std::vector<int> matrix2,
    std::vector<int>::size_type row_count_matrix1, std::vector<int>::size_type column_count_matrix1,
    std::vector<int>::size_type column_count_matrix2);

#endif  // MODULES_TASK_2_MEDVEDEVA_K_HORIZONTAL_A_VERTICAL_B_HORIZONTAL_A_VERTICAL_B_H_
