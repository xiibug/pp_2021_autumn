// Copyright 2021 Kruglov Aleksei
#ifndef MODULES_TASK_3_KRUGLOV_ALGORITHM_STRASSEN_STRASSEN_ALGORITHM_H_
#define MODULES_TASK_3_KRUGLOV_ALGORITHM_STRASSEN_STRASSEN_ALGORITHM_H_

#include <vector>
#include <string>

typedef std::vector<std::vector<double>> Matrix;

Matrix get_random_matrix(int height, int width, double max_number);

Matrix reference_multiply(const Matrix& a, const Matrix& b);

Matrix parallel_multiply(const Matrix& a, const Matrix& b);

std::vector<Matrix> split(const Matrix& a);

Matrix matrix_sum(const Matrix& a, const Matrix& b);
Matrix matrix_sub(const Matrix& a, const Matrix& b);
Matrix merge(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d);

bool is_equal(const Matrix& m1, const Matrix& m2, double threshold);

#endif  // MODULES_TASK_3_KRUGLOV_ALGORITHM_STRASSEN_STRASSEN_ALGORITHM_H_
