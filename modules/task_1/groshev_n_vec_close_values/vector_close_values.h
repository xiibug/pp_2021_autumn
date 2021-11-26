// Copyright 2021 Groshev Nickolay
#ifndef MODULES_TASK_1_GROSHEV_N_VEC_CLOSE_VALUES_VECTOR_CLOSE_VALUES_H_
#define MODULES_TASK_1_GROSHEV_N_VEC_CLOSE_VALUES_VECTOR_CLOSE_VALUES_H_

#include <vector>

int getMinDiffByOneProc(std::vector<int> someVector);
int getMinDiffParallel(std::vector <int> someVector);
std::vector<int> getRandomVector(int vecSize);

#endif  // MODULES_TASK_1_GROSHEV_N_VEC_CLOSE_VALUES_VECTOR_CLOSE_VALUES_H_
