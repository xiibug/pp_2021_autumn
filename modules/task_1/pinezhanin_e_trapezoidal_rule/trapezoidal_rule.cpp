// Copyright 2021 Pinezhanin Evgeny
#include <mpi.h>
#include <stdexcept>
#include "trapezoidal_rule.h"
#include "../../../modules/task_1/pinezhanin_e_trapezoidal_rule/trapezoidal_rule.h"

double getIntegralTrapezoidalRuleParallel(double (*f)(double), double a, double b, int n) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double sum = 0.0;
    if (n > 0) {
        //double h = (b - a) / n;
        //for (int i = rank + 1; i <= n; i += size){
        //    x = h * ((double)i - 0.5);
        //    sum += f(x);
        //}
        //mypi = h * sum;
        //MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    return sum;
}

double getIntegralTrapezoidalRuleSequential(double (*f)(double), double a, double b, int n) {
    double sum = 0.0;
    if (n > 0) {
        bool minus = (a > b);
        if (minus) std::swap(a, b);
        double h = (b - a) / n;
        for (int i = 0; i < n; i++) {
            sum += (f(a + i * h) + f(a + (i + 1) * h)) / 2 * h;
        }
        if (minus) sum = -sum;
    }
    return sum;
}