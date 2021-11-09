// Copyright 2021 Zarubin Mikhail
#ifndef MODULES_TASK_2_ZARUBIN_M_BUBBLE_SORT_EVEN_ODD_ALGORITHM_H_
#define MODULES_TASK_2_ZARUBIN_M_BUBBLE_SORT_EVEN_ODD_ALGORITHM_H_

#include <vector>

void generateRandomVector(std::vector<int>* vector,
    std::vector<int>::size_type size);
std::vector<int> getParallelOperations(const std::vector<int>& vector,
    std::vector<int>::size_type size);
std::vector<int> getSequentialOperations(const std::vector<int>& vector,
    std::vector<int>::size_type size); 

#endif  // MODULES_TASK_2_ZARUBIN_M_BUBBLE_SORT_EVEN_ODD_ALGORITHM_H_
