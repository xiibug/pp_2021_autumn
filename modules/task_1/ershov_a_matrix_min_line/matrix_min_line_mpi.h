// Copyright 2021 Ershov Alexey
#ifndef MODULES_TASK_1_ERSHOV_A_MATRIX_MIN_LINE_MATRIX_MIN_LINE_MPI_H_
#define MODULES_TASK_1_ERSHOV_A_MATRIX_MIN_LINE_MATRIX_MIN_LINE_MPI_H_

#include <vector>

struct Matrix {
	double* data;
	size_t weight;
	size_t height;
	Matrix(double* data, size_t weight, size_t height);
	Matrix(const Matrix& a);
	~Matrix();
	Matrix& operator=(const Matrix& right);
};

Matrix getRandomMatrix(const size_t m, const size_t n);
std::vector<double> getSequentialMatrixMinLine(const Matrix& matrix);
std::vector<double> getParallelMatrixMinLine(const Matrix& matrix);

#endif  // MODULES_TASK_1_ERSHOV_A_MATRIX_MIN_LINE_MATRIX_MIN_LINE_MPI_H_
