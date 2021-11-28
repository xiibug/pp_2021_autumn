// Copyright 2021 Utyugov Denis
#ifndef MODULES_TASK_1_UTYUGOV_D_AVARAGE_OF_EL_OF_VEC_AVARAGE_OF_EL_OF_VEC_H_
#define MODULES_TASK_1_UTYUGOV_D_AVARAGE_OF_EL_OF_VEC_AVARAGE_OF_EL_OF_VEC_H_

#include <string>
#include <vector>

std::vector<int> getRandomVector(int sz);
int getParallelOperations(std::vector<int> global_vec, int count_size_vector);
int getSequentialOperations(std::vector<int> vec);
double getAvarage(int Sum, int count_size_vector);

#endif  // MODULES_TASK_1_UTYUGOV_D_AVARAGE_OF_EL_OF_VEC_AVARAGE_OF_EL_OF_VEC_H_
