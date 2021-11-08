// Copyright 2021 Lakhov Kirill
#ifndef MODULES_TASK_1_LAKHOV_K_MATRIX_COL_SUM_MATRIX_COL_SUM_H_
#define MODULES_TASK_1_LAKHOV_K_MATRIX_COL_SUM_MATRIX_COL_SUM_H_
#include <mpi.h>
#include <vector>
#include <random>

std::vector<double> getRandomVector(int sz, int min, int max);

std::vector<std::vector<double>> getRandomMatrix(int size);

void printMatrix(std::vector<std::vector<double>> m, int size);

void printVector(std::vector<double> m, int size);

std::vector<double> sequentialCalc(std::vector<std::vector<double>> coefficients,
                                   std::vector<double> free_members, int size);

int parallelCalc(std::vector<std::vector<double>> matrix, std::vector<double> free_members, int size);

#endif  // MODULES_TASK_1_LAKHOV_K_MATRIX_COL_SUM_MATRIX_COL_SUM_H_
