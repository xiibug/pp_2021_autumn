#pragma once
#include <functional>
#include <mpi.h>

double IntegralSequential(double a, double b, int n, int foo_index);
double IntegralParallel(double a, double b, int n, int foo_index);
