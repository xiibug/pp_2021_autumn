// Copyright 2021 Zaitseva Ksenia
#ifndef MODULES_TASK_1_ZAITSEVA_K_INTEGRAL_RECTANGLE_METHOD_RECTANGLEMETHOD_H_
#define MODULES_TASK_1_ZAITSEVA_K_INTEGRAL_RECTANGLE_METHOD_RECTANGLEMETHOD_H_
#include <mpi.h>

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

double IntegralSequential(double a, double b, int n, int foo_index);
double IntegralParallel(double a, double b, int n, int foo_index);

#endif  // MODULES_TASK_1_ZAITSEVA_K_INTEGRAL_RECTANGLE_METHOD_RECTANGLEMETHOD_H_