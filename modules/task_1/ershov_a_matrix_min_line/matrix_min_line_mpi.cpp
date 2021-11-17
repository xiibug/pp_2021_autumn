// Copyright 2021 Ershov Alexey
#include <mpi.h>
#include <vector>
#include <climits>
#include "./matrix_min_line_mpi.h"

Matrix getRandomMatrix(const size_t m, const size_t n) {
    double* tmp = new double[m * n];
	for (size_t i = 0; i < m*n; ++i) {
		tmp[i] = rand() % 100;
	}
	Matrix matrix(tmp, m, n);
	delete[] tmp;
	tmp = nullptr;
	return matrix;
}

std::vector<double> getSequentialMatrixMinLine(const Matrix& matrix) {
    int min;
    std::vector<double> result(matrix.height, 0);
    for (int i = 0; i < matrix.height; ++i) {
        min = INT_MAX;

        for (int j = 0; j < matrix.weight; ++j) {
            if (matrix.data[i * matrix.weight + j] < min) {
                min = matrix.data[i * matrix.weight + j];
            }
        }
        result[i] = min;
    }
    return result;
}

std::vector<double> getParallelMatrixMinLine(const Matrix& matrix) { 
    int min;
    int world_size;
    int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int operation_per_process = matrix.height / world_size;
    double* vec = new double[matrix.weight * operation_per_process];
    double* res_vec = new double[matrix.height];
    std::vector<double> min_value(matrix.height, 0);
    MPI_Scatter(matrix.data, matrix.weight * operation_per_process, MPI_DOUBLE, vec,
        matrix.weight * operation_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    double* local_min = new double[operation_per_process];
    for (size_t i = 0; i < operation_per_process; ++i) {
    	min = INT_MAX;
    	for (size_t j = 0; j < matrix.weight; ++j) {
    		if (vec[i * matrix.weight + j] < min) {
    			min = vec[i * matrix.weight + j];
    		}
    	}
    	local_min[i] = min;
    }
    MPI_Gather(local_min, operation_per_process, MPI_DOUBLE, res_vec, operation_per_process,
        MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (world_rank == 0) {
        for (size_t i = world_size * operation_per_process; i < matrix.height; ++i) {
            min = INT_MAX;
            for (size_t j = 0; j < matrix.weight; ++j) {
                if (matrix.data[i * matrix.weight + j] < min)
                {
                    min = matrix.data[i * matrix.weight + j];
                }
            }
            res_vec[i] = min;
        }
    }
    for (size_t i = 0; i < (matrix.height); ++i) {
    	min_value[i] = res_vec[i];
    }
    delete[] local_min;
    delete[] vec;
    delete[] res_vec;
    local_min = nullptr;
    vec = nullptr;
    res_vec = nullptr;
    return min_value;
}

Matrix::Matrix(double* data, size_t weight, size_t height) {
	this->weight = weight;
	this->height = height;
	this->data = new double[this->height * this->weight];
	for (size_t i = 0; i < (this->height * this->weight); ++i) {
		this->data[i] = data[i];
	}
}

Matrix::Matrix(const Matrix& a) {
	this->height = a.height;
	this->weight = a.weight;
	this->data = new double[this->height * this->weight];
	for (size_t i = 0; i < (this->weight * this->height); ++i) {
		this->data[i] = a.data[i];
	}
}

Matrix::~Matrix() {
	delete[] this->data;
	this->data = nullptr;
}
