// Copyright 2021 Zaitseva Ksenia
#ifndef MODULES_TASK_2_ZAITSEVA_K_DINING_PHILOSOPHERS_H_
#define MODULES_TASK_2_ZAITSEVA_K_DINING_PHILOSOPHERS_H_

#include <mpi.h>
#include <stdio.h>

#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#define _PHOLISOPHERS_COUNT_ 3
#define THINK 0
#define HUNGRY 1
#define EAT 2
#define IN 4
#define OUT 1
#define KEY 3

void DiningPholisophers(int rank, int size, int run);

#endif  // MODULES_TASK_2_ZAITSEVA_K_DINING_PHILOSOPHERS_H_