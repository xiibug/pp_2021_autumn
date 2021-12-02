// Copyright 2021 Dydykin Pavel
#ifndef MODULES_TASK_1_DYDYKIN_P_INTEGRATION_MONTECARLO_INTEGRATION_MONTECARLO_H_
#define MODULES_TASK_1_DYDYKIN_P_INTEGRATION_MONTECARLO_INTEGRATION_MONTECARLO_H_

double func1(double x);
double func2(double x);
double func3(double x);

double MonteCarloWithOutMPI(int N, int a, int b, double(*func)(double));
double MonteCarloMPI(int N, int a, int b, double(*func)(double));

#endif  // MODULES_TASK_1_DYDYKIN_P_INTEGRATION_MONTECARLO_INTEGRATION_MONTECARLO_H_
