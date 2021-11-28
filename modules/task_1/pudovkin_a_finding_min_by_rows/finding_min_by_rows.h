// Copyright 2021 Pudovkin Artem
#ifndef MODULES_TASK_1_PUDOVKIN_A_FINDING_MIN_BY_ROWS_FINDING_MIN_BY_ROWS_H_
#define MODULES_TASK_1_PUDOVKIN_A_FINDING_MIN_BY_ROWS_FINDING_MIN_BY_ROWS_H_

#include <vector>

using std::vector;

vector<int> getRandomMatrix(const vector<int>::size_type size);

vector<int> sequentialFindingMinimumByRows(vector<int> matrix, const vector<int>::size_type rows,
                                                               const vector<int>::size_type cols);
vector<int> parallelFindingMinimumByRows(vector<int> matrix, const vector<int>::size_type rows,
                                                              const vector<int>::size_type cols);

#endif  // MODULES_TASK_1_PUDOVKIN_A_FINDING_MIN_BY_ROWS_FINDING_MIN_BY_ROWS_H_
