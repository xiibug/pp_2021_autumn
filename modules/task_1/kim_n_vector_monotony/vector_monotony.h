// Copyright 2021 Kim Nikita
#ifndef MODULES_TASK_1_KIM_N_VECTOR_MONOTONY_VECTOR_MONOTONY_H_
#define MODULES_TASK_1_KIM_N_VECTOR_MONOTONY_VECTOR_MONOTONY_H_

#include <vector>

std::vector<int> getRandomVector(int size);

int getNumNonMonotonyElems(std::vector<int> input_vec, int size, int direction);

int getNumNonMonotonyElemsParall(std::vector<int> input_vec, int size, int direction);

#endif  // MODULES_TASK_1_KIM_N_VECTOR_MONOTONY_VECTOR_MONOTONY_H_
