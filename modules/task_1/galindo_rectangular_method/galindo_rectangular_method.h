#ifndef MODULES_TASK_1_GALINDO_RECTANGULAR_METHOD_RECTANGULAR_METHOD_H_
#define MODULES_TASK_1_GALINDO_RECTANGULAR_METHOD_RECTANGULAR_METHOD_H_
#include <functional>

double def_int(std::function<double(double)> funct, double a, double b, int count);
double parallel_int(std::function<double(double)> funct, double a, double b, int count);

double func(double x);

#endif // !MODULES_TASK_1_GALINDO_RECTANGULAR_METHOD_RECTANGULAR_METHOD_H_

