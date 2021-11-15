// Copyright 2021 Petrova Polina
#ifndef MODULES_TASK_1_PETROVA_P_DOT_PRODUCT_OF_VECTORS_H_
#define MODULES_TASK_1_PETROVA_P_DOT_PRODUCT_OF_VECTORS_H_

#include <vector>

std::vector<int> fillRandomVector(int len);  // fill vectors random value
int sequentialScalMult(std::vector<int> a, std::vector<int> b, int len);  // secuential algorithm dot product of vectors
int parallelScalMult(std::vector<int> a, std::vector<int> b, int len);  // parallel algoritm dot rpoduct of vectors

#endif  // MODULES_TASK_1_PETROVA_P_DOT_PRODUCT_OF_VECTORS_H_


