// Copyright 2021 Lakhov Kirill
#ifndef MODULES_TASK_3_LAKHOV_K_OPTIMIZATION_PARAMS_OPTIMIZATION_PARAMS_H_
#define MODULES_TASK_3_LAKHOV_K_OPTIMIZATION_PARAMS_OPTIMIZATION_PARAMS_H_
#include <mpi.h>
#include <math.h>
#include <set>
#include <limits>
#include <vector>

double f1(double x, double y);
double f2(double x, double y);
double f3(double x, double y);
double f4(double x, double y);
double f5(double x, double y);


class Point {
 public:
    double x;
    double y;
    double z;
    explicit Point(double x_value = 0, double y_value = 0, double z_value = 0)
    : x(x_value), y(y_value), z(z_value) {}
    friend bool operator==(const Point& left, const Point& right) {
        const double eps = 0.01;
        double dx = std::abs(left.x - right.x) <= eps;
        double dy = std::abs(left.y - right.y) <= eps;
        double dz = std::abs(left.z - right.z) <= eps;
        return dx && dy && dz;
    }
};

Point sequentialCalc(double left_x, double right_x,
                     double left_y, double right_y,
                     double(*func)(double x, double y));

Point parralelCalc(double left_x, double right_x,
                   double left_y, double right_y,
                   double(*func)(double x, double y));

class Interval {
 public:
    const double r;
    const double variableFirst;
    const double functionValueFirst;
    const double variableSecond;
    const double functionValueSecond;
    Interval(double r_value, double variable_f,
             double f_f, double variable_s, double f_s)
    : r(r_value), variableFirst(variable_f), functionValueFirst(f_f),
      variableSecond(variable_s),  functionValueSecond(f_s) {}
    friend bool operator<(const Interval& left, const Interval& right) {
        return left.r > right.r;
    }
};

class doubleDimensionChar {
 public:
    const double x;
    const double y;
    const double functionValue;
    doubleDimensionChar(double x_value, double y_value, double f_value)
    : x(x_value), y(y_value), functionValue(f_value) {}
    friend bool operator<(const doubleDimensionChar& left,
                          const doubleDimensionChar& right) {
        return left.y < right.y;
    }
};

class singleDimensionChar {
 public:
    const double x;
    const double functionValue;
    singleDimensionChar(double x_value, double f_value)
    : x(x_value), functionValue(f_value) {}
    friend bool operator<(const singleDimensionChar& left,
                          const singleDimensionChar& right) {
         return left.x < right.x;
    }
};

Point singleDimensionMin(double left_x, double right_x, double const_y,
                         double(*func)(double x, double y));

#endif  // MODULES_TASK_3_LAKHOV_K_OPTIMIZATION_PARAMS_OPTIMIZATION_PARAMS_H_
