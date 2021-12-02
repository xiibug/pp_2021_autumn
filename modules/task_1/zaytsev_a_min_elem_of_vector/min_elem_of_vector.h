// Copyright 2021 Zaytsev Alexander
#ifndef MODULES_TASK_1_ZAYTSEV_A_MIN_ELEM_OF_VECTOR_MIN_ELEM_OF_VECTOR_H_
#define MODULES_TASK_1_ZAYTSEV_A_MIN_ELEM_OF_VECTOR_MIN_ELEM_OF_VECTOR_H_
#include <vector>
int* RandomVector(int size);
int ParallelMin(int* global_our_vector,
                const int count_size_vector);
int SequentialMin(int* our_vector, const int count_size_vector);

#endif  // MODULES_TASK_1_ZAYTSEV_A_MIN_ELEM_OF_VECTOR_MIN_ELEM_OF_VECTOR_H_
