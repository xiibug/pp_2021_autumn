// Copyright 2021 Zaitseva Ksenia
#ifndef MODULES_TASK_2_ZAITSEVA_K_DINING_PHILOSOPHERS_DININGPHILOSOPHERS_H_
#define MODULES_TASK_2_ZAITSEVA_K_DINING_PHILOSOPHERS_DININGPHILOSOPHERS_H_

#include <mpi.h>
#include <stdio.h>
#include <random>
#include <chrono> // NOLINT [build/c++11]
#include <iostream>
#include <random>
#include <thread> // NOLINT [build/c++11]

#define _PHOLISOPHERS_COUNT_ 3
#define THINK 0
#define HUNGRY 1
#define EAT 2
#define IN 4
#define OUT 1
#define KEY 3

void DiningPholisophers(int rank, int size, int run);

#endif  // MODULES_TASK_2_ZAITSEVA_K_DINING_PHILOSOPHERS_DININGPHILOSOPHERS_H_
