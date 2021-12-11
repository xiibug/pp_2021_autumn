// Copyright 2021 Lakhov Kirill
#ifndef MODULES_TASK_3_LAKHOV_K_OPTIMIZATION_PARAMS_OPTIMIZATION_PARAMS_H_
#define MODULES_TASK_3_LAKHOV_K_OPTIMIZATION_PARAMS_OPTIMIZATION_PARAMS_H_
#include <mpi.h>
#include <math.h>
#include <set>
#include <limits>
#include <vector>

struct point {
    double x;
    double y;
    double z;
};

double f1(double x, double y);

// std::vector<double> getRandomVector(int sz, int min, int max);

// std::vector<std::vector<double>> getRandomMatrix(int size);

point sequentialCalc(double left_x, double right_x,
                     double left_y, double right_y,
                     double(*func)(double x, double y));

// std::vector<double> parallelCalc(std::vector<std::vector<double>> matrix,
//                                  std::vector<double> free_members, int size);

class singleDimensionChar {
 public:
    const double x;
    const double functionValue;
    singleDimensionChar(double x_value, double f_value) : x(x_value), functionValue(f_value) {}
    friend bool operator<(const singleDimensionChar& left, const singleDimensionChar& right) {return left.x < right.x;}
};

class pointSender {
 public:
    const double variable;
    const double functionValue;
    pointSender(double variable_value, double f_value) : variable(variable_value), functionValue(f_value) {}
    friend bool operator<(const pointSender& left, const pointSender& right) {return left.variable < right.variable;}
};

class singleDimensionR {
 public:
    const double r;
    const double variable;
    const double functionValue;
    singleDimensionR(double r_value, double variable_value, double f_value) : r(r_value), variable(variable_value), functionValue(f_value) {}
    friend bool operator<(const singleDimensionR& left, const singleDimensionR& right) {return left.r > right.r;}
};

class doubleDimensionChar {
 public:
    const double x;
    const double y;
    const double functionValue;
    doubleDimensionChar(double x_value, double y_value, double f_value) : x(x_value), y(y_value), functionValue(f_value) {}
    friend bool operator<(const doubleDimensionChar& left, const doubleDimensionChar& right) {return left.y < right.y;}
};

class DimensionChar{
    public:
        double variable();
        double functionValue();
}

point singleDimensionMin(double left_x, double right_x, double const_y, double(*func)(double x, double y));

point singleDimensionMinParallel(double left_x, double right_x, double const_y, double(*func)(double x, double y), int proc_count);



#endif  // MODULES_TASK_3_LAKHOV_K_OPTIMIZATION_PARAMS_OPTIMIZATION_PARAMS_H_