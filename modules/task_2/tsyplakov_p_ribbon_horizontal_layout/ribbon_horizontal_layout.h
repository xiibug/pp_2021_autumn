// Copyright 2021 Tsyplakov Pavel
#ifndef MODULES_TASK_2_TSYPLAKOV_P_RIBBON_HORIZONTAL_LAYOUT_RIBBON_HORIZONTAL_LAYOUT_H_
#define MODULES_TASK_2_TSYPLAKOV_P_RIBBON_HORIZONTAL_LAYOUT_RIBBON_HORIZONTAL_LAYOUT_H_

#include <vector>

using std::vector;

vector<int> getRandomVector(vector<int>::size_type size);
vector<int> getRandomMatrix(vector<int>::size_type size);

vector<int> getSequentialOperations(const vector<int>& globalMatrix, vector<int>::size_type numberOfRows,
                                    vector<int>::size_type numberOfCols, const vector<int>& globalVector);
vector<int> getParallelOperations(const vector<int>& globalMatrix, vector<int>::size_type numberOfRows,
                                  vector<int>::size_type numberOfCols, const vector<int>& globalVector);

#endif  // MODULES_TASK_2_TSYPLAKOV_P_RIBBON_HORIZONTAL_LAYOUT_RIBBON_HORIZONTAL_LAYOUT_H_