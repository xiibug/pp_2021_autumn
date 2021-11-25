// Copyright 2021 Chornyi Yurii
#ifndef MODULES_TASK_3_CHORNYI_Y_RADIX_SORT_WITH_SIMPLE_MERGE_RADIX_SORT_WITH_SIMPLE_MERGE_H_
#define MODULES_TASK_3_CHORNYI_Y_RADIX_SORT_WITH_SIMPLE_MERGE_RADIX_SORT_WITH_SIMPLE_MERGE_H_

#include <vector>

using std::vector;
typedef vector<int>::size_type v_size_t;

void generateRandomVector(vector<int>* vectorOfValue, v_size_t vectorSize);

void sequentialRadixSort(vector<int>* vectorOfValue);
vector<int> parallelRadixSort(const vector<int>& vectorOfValue, const v_size_t vectorSize);

#endif  // CHORNYI_Y_RADIX_SORT_WITH_SIMPLE_MERGE_RADIX_SORT_WITH_SIMPLE_MERGE_H_
