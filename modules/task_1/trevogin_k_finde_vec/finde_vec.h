// Copyright 2021 Trevogin Kirill
#include <mpi.h>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>
#include <gtest-mpi-listener.hpp>

#ifndef MODULES_TASK_1_TREVOGIN_K_FINDE_VEC_FINDE_VEC_
#define MODULES_TASK_1_TREVOGIN_K_FINDE_VEC_FINDE_VEC_

std::vector<int> getRandomVector(int size);
int getFindeOrderedElements(std::vector<int> vec);
int getFindeOrderedElementsParall(std::vector<int> vec, int v_size);

#endif  // MODULES_TASK_1_TREVOGIN_K_FINDE_VEC_FINDE_VEC_
