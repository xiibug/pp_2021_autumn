// "Copyright [2021] <Borisov Maxim>"

#ifndef MODULES_TASK_1_BORISOV_M_SCALAR_VECTOR_PRODUCT_SCALAR_VECTOR_PRODUCT_H_
#define MODULES_TASK_1_BORISOV_M_SCALAR_VECTOR_PRODUCT_SCALAR_VECTOR_PRODUCT_H_
#include <vector>

int sequential_product(const std::vector<int>& vector_a,
        const std::vector<int>&  vector_b);

int sequential_product_std(const std::vector<int>& vector_a,
        const std::vector<int>&  vector_b);

int parallel_product(std::vector<int> vector_a, std::vector<int>  vector_b);

std::vector<int> get_random_vector(int size);

#endif  // MODULES_TASK_1_BORISOV_M_SCALAR_VECTOR_PRODUCT_SCALAR_VECTOR_PRODUCT_H_
