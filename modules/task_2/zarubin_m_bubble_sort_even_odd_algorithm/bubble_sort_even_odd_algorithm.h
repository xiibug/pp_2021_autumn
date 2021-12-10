// Copyright 2021 Zarubin Mikhail
#ifndef MODULES_TASK_2_ZARUBIN_M_BUBBLE_SORT_EVEN_ODD_ALGORITHM_BUBBLE_SORT_EVEN_ODD_ALGORITHM_H_
#define MODULES_TASK_2_ZARUBIN_M_BUBBLE_SORT_EVEN_ODD_ALGORITHM_BUBBLE_SORT_EVEN_ODD_ALGORITHM_H_
#include <vector>

void generateRandomVector(std::vector<int>* vector,
    std::vector<int>::size_type size);
void getSequentialOperations(std::vector<int>::iterator begin,
    std::vector<int>::iterator end);
std::vector<int>::size_type calculate_begin(int rank,
    std::vector<int>::size_type local_size,
    std::vector<int>::size_type remains);
std::vector<int>::size_type calculate_end(int rank,
    std::vector<int>::size_type local_size,
    std::vector<int>::size_type remains);
std::vector<int> getParallelOperations(const std::vector<int>& vector,
    std::vector<int>::size_type size);

#endif  // MODULES_TASK_2_ZARUBIN_M_BUBBLE_SORT_EVEN_ODD_ALGORITHM_BUBBLE_SORT_EVEN_ODD_ALGORITHM_H_
