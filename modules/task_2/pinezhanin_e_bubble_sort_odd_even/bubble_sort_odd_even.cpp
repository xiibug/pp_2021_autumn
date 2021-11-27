// Copyright 2021 Pinezhanin Evgeny
#include <mpi.h>
#include <random>
#include <vector>
#include <algorithm>
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
    
    return vec;
}

std::vector<int> BubbleSortOddEvenSequential(std::vector<int> vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        if (i % 2) {
            for (int j = 1; j < n - 1; j += 2) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        } else {
            for (int j = 0; j < n - 2; j += 2) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }
    return vec;
}
