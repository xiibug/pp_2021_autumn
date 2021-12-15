// Copyright 2021 Lebedev Alexey
#include "../../../modules/task_3/lebedev_a_lsd_sort/lsd_sort.h"

#include <mpi.h>
#include <math.h>

#include <cstring>
#include <string>


size_t get_max_digits(const std::vector<int>& v) {
    size_t max_digit = 0;
    for(const int& num: v) {
        size_t digit = (num < 0) ? std::to_string(num).size() - 1 : std::to_string(num).size();
        if (digit > max_digit) {
            max_digit = digit;
        }
    }
    return max_digit;
}

void lsd_sort(std::vector<int>& v) {
    const static size_t range = 19;
    std::vector<int> containers[range];
    size_t max_digits = get_max_digits(v);
    int ten_pow_dig = 1;
    for (size_t cur_dig = 0; cur_dig < max_digits; cur_dig++) {
        for (int& num: v) {
            containers[num / ten_pow_dig % 10 + 9].push_back(num);
        }
        ten_pow_dig *= 10;
        int* write_it = v.data();
        for (size_t i = 0; i < range; i++) {
            std::memcpy(write_it, containers[i].data(), containers[i].size() * sizeof(int));
            write_it += containers[i].size();
            containers[i].clear();
        }
    }
}