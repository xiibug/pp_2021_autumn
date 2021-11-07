// Copyright 2021 Zharkov Andrey
#ifndef MODULES_TASK_1_ZHARKOV_A_VEC_MIN_VEC_MIN_H_
#define MODULES_TASK_1_ZHARKOV_A_VEC_MIN_VEC_MIN_H_

#include <vector>
#include <string>

std::vector<int> getRandomVector(int  sz);
int getParallelOperations(std::vector<int> global_vec, int count_size_vector);
int getSequentialOperations(std::vector<int> vec);

#endif  // MODULES_TASK_1_ZHARKOV_A_VEC_MIN_VEC_MIN_H_
