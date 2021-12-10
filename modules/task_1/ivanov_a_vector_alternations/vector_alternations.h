// Copyright 2021 Ivanov Arkadiy
#ifndef MODULES_TASK_1_IVANOV_A_VECTOR_ALTERNATIONS_VECTOR_ALTERNATIONS_H_
#define MODULES_TASK_1_IVANOV_A_VECTOR_ALTERNATIONS_VECTOR_ALTERNATIONS_H_

#define MIE "mem init error"

// standard checking for alterations
int sequentialCount_V1(const int* vec, int len);

// optimized checking for alternations
int sequentialCount_V2(const int* vec, int len);

// parallel checking for alternations
int parallelCount(const int* vec, int len);

// fill vector with random values (value != 0)
void fillVecWithRandValues(int* vec, int len);

#endif  // MODULES_TASK_1_IVANOV_A_VECTOR_ALTERNATIONS_VECTOR_ALTERNATIONS_H_
