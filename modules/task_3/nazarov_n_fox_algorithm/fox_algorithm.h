// Copyright 2021 Nazarov Nikita
#ifndef MODULES_TASK_3_NAZAROV_N_FOX_ALGORITHM_FOX_ALGORITHM_H_
#define MODULES_TASK_3_NAZAROV_N_FOX_ALGORITHM_FOX_ALGORITHM_H_

#include <mpi.h>

#include <iostream>
#include <random>
#include <vector>

std::vector<double> GetRandomMatrix(int n);
void Multiplication(std::vector<double> A, std::vector<double> B,
                    std::vector<double> C, int data);
void FoxAlgorithm(std::vector<double> A, std::vector<double> B,
                  std::vector<double> C, int data);

#endif  //  MODULES_TASK_3_NAZAROV_N_FOX_ALGORITHM_FOX_ALGORITHM_H_
