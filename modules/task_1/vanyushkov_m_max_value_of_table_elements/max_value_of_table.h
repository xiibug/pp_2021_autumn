// Copyright 2021 Vanyushkov Maxim
// #ifndef MODULES_TASK_1_VANYUSHKOV_M_MAX_VALUE_OF_TABLE_ELEMENTS_MAX_VALUE_OF_TABLE_H_
// #define MODULES_TASK_1_VANYUSHKOV_M_MAX_VALUE_OF_TABLE_ELEMENTS_MAX_VALUE_OF_TABLE_H_

// fill matrix with random values
void fillMatrixRandValue(int* matrix, int len);

// standard search for max element
int sequentialMax(const int* matrix, int len);

// parallel search for max element
int parallelMax(const int* matrix, int len);

// #endif  // MODULES_TASK_1_VANYUSHKOV_M_MAX_VALUE_OF_TABLE_ELEMENTS_MAX_VALUE_OF_TABLE_H_