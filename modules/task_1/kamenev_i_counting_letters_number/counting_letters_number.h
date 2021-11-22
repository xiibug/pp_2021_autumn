// Copyright 2021 Kamenev Ilya
#ifndef MODULES_TASK_1_KAMENEV_I_COUNTING_LETTERS_NUMBER_COUNTING_LETTERS_NUMBER_H_
#define MODULES_TASK_1_KAMENEV_I_COUNTING_LETTERS_NUMBER_COUNTING_LETTERS_NUMBER_H_

#include <mpi.h>
#include <string>
#include <random>
#include <iostream>

std::string CreateRandomStr(size_t size);
std::string CreateOnlyLettersStr(size_t size);
int CountingLettersParallel(const std::string& str);
int CountingLettersSequential(const std::string& str);

#endif  // MODULES_TASK_1_KAMENEV_I_COUNTING_LETTERS_NUMBER_COUNTING_LETTERS_NUMBER_H_
