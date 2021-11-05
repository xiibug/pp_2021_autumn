// Copyright 2021 Zaytsev Mikhail

#pragma once

#ifndef FINDING_MINIMUM_BY_MATRIX_COLUMNS_
#define FINDING_MINIMUM_BY_MATRIX_COLUMNS_

#include <vector>

std::vector<std::vector<int>> fillMatrix(const int rows, const int columns);
std::vector<std::vector<int>> transponseMatrix(const std::vector<std::vector<int>>& matrix);

void printMatrix(const std::vector<std::vector<int>>& matrix);

std::vector<int> singleFindingMinimum(const std::vector<std::vector<int>>& matrix);

std::vector<int> parallelFindingMinimum(const std::vector<std::vector<int>>& matrix);

#endif  // FINDING_MINIMUM_BY_MATRIX_COLUMNS_
