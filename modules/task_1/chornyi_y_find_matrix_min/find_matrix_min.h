#pragma once

#ifndef FIND_MINIMUM_IN_MATRIX
#define FIND_MINIMUM_IN_MATRIX

#include <vector>

std::vector<std::vector<int>> fillMatrixWithRandom(const int numberOfRows, const int numberOfColumns);
int singleFindMinimum(std::vector<std::vector<int>> matrix);

int parallelFindMinimum(std::vector<std::vector<int>> matrix);

#endif //FIND_MINIMUM_IN_MATRIX
