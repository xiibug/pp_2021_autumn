// Copyright 2021 Ermakov Pavel
#include <gtest/gtest.h>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <gtest-mpi-listener.hpp>

#ifndef MODULES_TASK_3_ERMAKOV_P_Q_SORT_ODD_EVEN_M_BATCHER_Q_SORT_ODD_EVEN_M_BATCHER_H_
#define MODULES_TASK_3_ERMAKOV_P_Q_SORT_ODD_EVEN_M_BATCHER_Q_SORT_ODD_EVEN_M_BATCHER_H_

std::vector<int> vec_gen(int size);
int partition(std::vector<int>& vec, int l, int r);
void q_sort(std::vector<int>& vec, int l, int r);
void _allocation(std::vector<int> vec);
void odd_even_merge(std::vector<int> l, std::vector<int> r);
void create_allocation(int _proc_num);
void q_sort_batcher_par(std::vector<int>* vec);

#endif  // MODULES_TASK_3_ERMAKOV_P_Q_SORT_ODD_EVEN_M_BATCHER_Q_SORT_ODD_EVEN_M_BATCHER_H_
