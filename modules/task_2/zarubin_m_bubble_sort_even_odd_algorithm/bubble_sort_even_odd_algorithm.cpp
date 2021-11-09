// Copyright 2021 Zarubin Mikhail
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_2/zarubin_m_bubble_sort_even_odd_algorithm/bubble_sort_even_odd_algorithm.h"


void generateRandomVector(std::vector<int>* vector,
    std::vector<int>::size_type size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    for (std::vector<int>::size_type i = 0; i < size; i++) {
        (*vector)[i] = gen() % 100;
    }
}

std::vector<int> getSequentialOperations(const std::vector<int>& vector,
    std::vector<int>::size_type size) {
    std::vector<int> result(vector);
    int stop_flag{ 0 }, current_iter{ 0 }, swap_flag{ 0 };
    std::vector<int>::size_type start_value{ 0 };

    while (stop_flag != 2) {
        if (current_iter % 2) {
            stop_flag = 0;
            start_value = 0;
        }
        else {
            start_value = 1;
        }

        swap_flag = 0;
        for (auto i = start_value; i + 1 < size; ++i) {
            if (result[i] > result[i + 1]) {
                std::swap(result[i], result[i + 1]);
                swap_flag = 1;
            }
        }
        
        if (swap_flag == 0)
            ++stop_flag;

        ++current_iter;
    }
    return result;
}

std::vector<int> getParallelOperations(const std::vector<int>& global_vector,
    std::vector<int>::size_type size) {
    /* */
    return std::vector<int>{};
}

