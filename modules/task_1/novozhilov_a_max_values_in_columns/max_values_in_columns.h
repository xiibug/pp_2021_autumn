// Copyright 2021 Novozhilov Alexander
#ifndef MODULES_TASK_1_NOVOZHILOV_A_MAX_VALUES_IN_COLUMNS_MAX_VALUES_IN_COLUMNS_H
#define MODULES_TASK_1_NOVOZHILOV_A_MAX_VALUES_IN_COLUMNS_MAX_VALUES_IN_COLUMNS_H

#include <vector>
#include <string>
#include <iostream>

std::vector<int> getRandomVector(int sz);

std::vector<std::vector<int>> getRandomMatrix(int rows, int cols);

std::vector<int> maxValuesInColumnsSequential(std::vector<std::vector<int>> matrix);

std::vector<int> maxValuesInColumnsParallel(std::vector<std::vector<int>> matrix, int rows, int cols);

void printVector(std::vector<int> vector);

void printMatrix(std::vector<std::vector<int>> matrix);

#endif  // MODULES_TASK_1_NOVOZHILOV_A_MAX_VALUES_IN_COLUMNS_MAX_VALUES_IN_COLUMNS_H
