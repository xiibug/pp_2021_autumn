// Copyright 2021 Shabunin Vladislav
#ifndef MODULES_TASK_1_SHABUNIN_V_VECTOR_MAX_VECTOR_MAX_H_
#define MODULES_TASK_1_SHABUNIN_V_VECTOR_MAX_VECTOR_MAX_H_

#include <vector>

std::vector<int> getRandomVector(int sz);
int getParallelMax(std::vector<int> global_vec, int count_size_vector);
int getSequentialMax(std::vector<int> vec);

#endif  // MODULES_TASK_1_SHABUNIN_V_VECTOR_MAX_VECTOR_MAX_H_
