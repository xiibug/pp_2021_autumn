// Copyright 2021 Brazhnik Dmitry
#ifndef MODULES_TASK_1_BRAZHNIK_D_VECTOR_FIND_MIN_FIND_MIN_ELEMENT_VECTOR_H_
#define MODULES_TASK_1_BRAZHNIK_D_VECTOR_FIND_MIN_FIND_MIN_ELEMENT_VECTOR_H_

#include <string>
#include <vector>

std::vector<int> fillRandomValToVector(const int size);

int defaultFindingMinVal(const std::vector<int>& vector);
int parallelFindingMinVal(const std::vector<int>& vector, const int size);

#endif  // MODULES_TASK_1_BRAZHNIK_D_VECTOR_FIND_MIN_FIND_MIN_ELEMENT_VECTOR_H_