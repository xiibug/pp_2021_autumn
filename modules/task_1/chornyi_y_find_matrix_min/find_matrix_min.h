#pragma once

#ifndef FIND_MATRIX_MIN
#define FIND_MATRIX_MIN

#include <vector>

std::vector<std::vector<int>> fillMatrixWithRandom(const int numberOfRows, const int numberOfColumns);
int singleFindMinimum(std::vector<std::vector<int>> matrix);

int parallelFindMinimum(std::vector<std::vector<int>> matrix);

#endif //FIND_MATRIX_MIN
