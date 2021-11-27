// Copyright 2021 Pinezhanin Evgeny
#include <mpi.h>
#include <random>
#include <vector>
#include "../../../modules/task_2/pinezhanin_e_bubble_sort_odd_even/bubble_sort_odd_even.h"

std::vector<int> getRandomVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int  i = 0; i < size; i++) {
        vec[i] = gen() % 1000;
    }
    return vec;
}

std::vector<int> BubbleSortOddEvenParallel(std::vector<int> vec) {
    return std::vector<int>();
}

std::vector<int> BubbleSortOddEvenSequential(std::vector<int> vec) {
    return std::vector<int>();
}
