// Copyright 2021 Lazarev Alexey
#ifndef MODULES_TASK_1_LAZAREV_A_WORD_COUNT_WORD_COUNT_H_
#define MODULES_TASK_1_LAZAREV_A_WORD_COUNT_WORD_COUNT_H_
#include <mpi.h>

#include <ctime>
#include <random>
#include <string>
#include <vector>

int Count(std::string);           // параллельный
int GetCountString(std::string);  // последовательный

#endif  // MODULES_TASK_1_LAZAREV_A_WORD_COUNT_WORD_COUNT_H_
