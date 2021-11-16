// Copyright 2021 Lakhov Kirill
#ifndef MODULES_TASK_2_LAKHOV_K_SIMPLE_ITERATION_SIMPLE_ITERATION_H_
#define MODULES_TASK_2_LAKHOV_K_SIMPLE_ITERATION_SIMPLE_ITERATION_H_
#include <mpi.h>
#include <vector>
#include <random>

std::vector<double> getRandomVector(int sz, int min, int max);

std::vector<std::vector<double>> getRandomMatrix(int size);

std::vector<double> sequentialCalc(
                                std::vector<std::vector<double>> coefficients,
                                std::vector<double> free_members, int size);

std::vector<double> parallelCalc(std::vector<std::vector<double>> matrix,
                                 std::vector<double> free_members, int size);

#endif  // MODULES_TASK_2_LAKHOV_K_SIMPLE_ITERATION_SIMPLE_ITERATION_H_
