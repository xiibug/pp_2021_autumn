#ifndef SCALAR_VECTOR_PRODUCT_H
#define SCALAR_VECTOR_PRODUCT_H
#include <vector>

int sequential_product(const std::vector<int>& vector_a, const std::vector<int>&  vector_b);

int sequential_product_std(const std::vector<int>& vector_a, const std::vector<int>&  vector_b);

int parallel_product(const std::vector<int>& vector_a, const std::vector<int>&  vector_b);

std::vector<int> get_random_vector(int size);

#endif 
