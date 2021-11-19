// Copyright 2021 Ermakov Pavel
#include <string>
#include <mpi.h>
#include <numeric>
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>

#ifndef MODULES_TASK_1_ERMAKOV_P_LETTERS_COUNT_LETTERS_COUNT_H_
#define MODULES_TASK_1_ERMAKOV_P_LETTERS_COUNT_LETTERS_COUNT_H_

std::string random_str_gen(int size);
int letters_count_seq(std::string str);
int letters_count_par(std::string str);


#endif  // MODULES_TASK_1_ERMAKOV_P_LETTERS_COUNT_LETTERS_COUNT_
