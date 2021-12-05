//Copyright 2021 Abuyassen Albara

#ifndef FIRST_TASK_MPI
#define FIRST_TASK_MPI

#include <vector>

std::vector<int> getRandomVector(int  sz);
int getParallelOperations(std::vector<int> global_vec,
    int count_size_vector);
int getSequentialOperations(std::vector<int> vec);

#endif