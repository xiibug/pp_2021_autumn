// Copyright 2021 Nazarov Nikita
#ifndef MODULES_TASK_1_NAZAROV_N_SUM_OF_VEC_ELEM_SUM_OF_VEC_ELEM_H_
#define MODULES_TASK_1_NAZAROV_N_SUM_OF_VEC_ELEM_SUM_OF_VEC_ELEM_H_

#include <time.h>
#include <mpi.h>
#include <random>
#include <algorithm>
#include <vector>
#include <string>


double getParallelOperations(std::vector<double> vec, int n, const std::string& ops);
double getSequentialOperations(std::vector<double> vec, int n, const std::string& ops);
std::vector<double> getRandomVector(int n);

#endif  // MODULES_TASK_1_NAZAROV_N_SUM_OF_VEC_ELEM_SUM_OF_VEC_ELEM_H_
