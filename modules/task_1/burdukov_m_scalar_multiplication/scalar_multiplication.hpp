// Copyright 2021 Burdukov Mikhail
#ifndef MODULES_TASK_1_BURDUKOV_M_SCALAR_MULTIPLICATION_SCALAR_MULTIPLICATION_HPP_
#define MODULES_TASK_1_BURDUKOV_M_SCALAR_MULTIPLICATION_SCALAR_MULTIPLICATION_HPP_

#include <random>
#include <vector>

// for testing
int
non_parallel_scalar_muliply(const std::vector<int>& first ,
            const std::vector<int>& second , int vlen);

std::vector<int>
generate_random_vector(const int size);
// scalar operation
int
scalar_muliply(const std::vector<int>& first , const std::vector<int>& second ,
            const int vlen);
#endif  // MODULES_TASK_1_BURDUKOV_M_SCALAR_MULTIPLICATION_SCALAR_MULTIPLICATION_HPP_
