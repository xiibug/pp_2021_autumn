// Copyright 2021 Zarubin Mikhail
#ifndef MODULES_TASK_3_ZARUBIN_M_DENSE_MATRIX_CANNON_ALGORITHM_DENSE_MATRIX_CANNON_ALGORITHM_H_
#define MODULES_TASK_3_ZARUBIN_M_DENSE_MATRIX_CANNON_ALGORITHM_DENSE_MATRIX_CANNON_ALGORITHM_H_
#include <vector>

void generateRandomMatrix(std::vector<double>* matrix,
    std::vector<double>::size_type size,
    int left_dorder, int right_border);
void getSequentialOperations(const std::vector<double>& first_matrix,
    const std::vector<double>& second_matrix,
    std::vector<double>* answer,
    std::vector<double>::size_type size);
std::vector<double> getParallelOperations(const std::vector<double>& first_matrix,
    const std::vector<double>& second_matrix,
    std::vector<double>::size_type size);
int calculateActualSize(int old_size,
    std::vector<double>::size_type matrix_size);

#endif  // MODULES_TASK_3_ZARUBIN_M_DENSE_MATRIX_CANNON_ALGORITHM_DENSE_MATRIX_CANNON_ALGORITHM_H_
