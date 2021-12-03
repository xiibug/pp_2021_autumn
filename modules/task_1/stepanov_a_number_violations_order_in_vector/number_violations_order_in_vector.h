// Copyright 2021 Stepanov Alexander
#ifndef MODULES_TASK_1_STEPANOV_A_NUMBER_VIOLATIONS_ORDER_IN_VECTOR_NUMBER_VIOLATIONS_ORDER_IN_VECTOR_H_
#define MODULES_TASK_1_STEPANOV_A_NUMBER_VIOLATIONS_ORDER_IN_VECTOR_NUMBER_VIOLATIONS_ORDER_IN_VECTOR_H_

#include <vector>

void generateRandomVector(std::vector<int>* vector);
int getSequentialOperations(const std::vector<int>& vector);
int getParallelOperations(const std::vector<int>& vector,
    std::vector<int>::size_type size);

#endif  // MODULES_TASK_1_STEPANOV_A_NUMBER_VIOLATIONS_ORDER_IN_VECTOR_NUMBER_VIOLATIONS_ORDER_IN_VECTOR_H_
