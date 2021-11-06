// Copyright 2021 Gordey  Maria
#ifndef MODULES_TASK_1_GORDEY_M_TRAPEZ_METHOD_TRAPEZ_METHOD_H_
#define MODULES_TASK_1_GORDEY_M_TRAPEZ_METHOD_TRAPEZ_METHOD_H_

double getParallelOperations(double a, double b, int n,
    const std::function<double(double)>& f);
double getSequentialOperations(double a, double b, int n,
    const std::function<double(double)>& f);

#endif  // MODULES_TASK_1_GORDEY_M_TRAPEZ_METHOD_TRAPEZ_METHOD_H_
