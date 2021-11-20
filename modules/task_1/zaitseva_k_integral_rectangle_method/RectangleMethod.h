// Copyright 2021 Zaitseva Ksenia
#ifndef MODULES_TASK_1_
#define MODULES_TASK_1_
#include <functional>
#include <mpi.h>

double IntegralSequential(double a, double b, int n, int foo_index);
double IntegralParallel(double a, double b, int n, int foo_index);

#endif  // MODULES_TASK_1_