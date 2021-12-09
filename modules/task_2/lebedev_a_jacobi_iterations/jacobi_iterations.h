// Copyright 2021 Lebedev Alexey
#ifndef MODULES_TASK_2_LEBEDEV_A_JACOBI_ITERATIONS_JACOBI_ITERATIONS_H_
#define MODULES_TASK_2_LEBEDEV_A_JACOBI_ITERATIONS_JACOBI_ITERATIONS_H_

#include <cstring>
#include <math.h>
#include <iostream>
#include "./tensor.h"


template<typename T>
class LinearSystem {
public:
    size_t n_dims;
	const Tensor<T> A;
    const Tensor<T> b;
    const Tensor<T> x0;
    LinearSystem(const size_t _n_dims): n_dims(_n_dims), A({_n_dims, _n_dims}), b({_n_dims, 1}), x0({_n_dims, 1}) {};
};

template<typename T>
double dist(Tensor<T> t1, Tensor<T> t2) {
    if (t1.get_shape() != t2.get_shape()){
        throw std::logic_error("Can't measure distance beetwen tensor with different shapes!");
    }
    double d = 0;
    for (size_t i = 0; i < t1.get_size(); i++) {
        d += std::pow(t1[i] - t2[i], 2);
    }
    return std::sqrt(d);
}

template<typename T>
Tensor<double> jacobi_iterations_sequential(const LinearSystem<T>& sys, const double accuracy) {
    auto A = sys.A, b = sys.b;
    auto shape = A.get_shape();
    auto strides = A.get_strides();
    Tensor<double> B(shape);
    for (size_t d1 = 0; d1 < shape[0]; d1++) {
        double a_ii = A[d1 * strides[0] + d1 * strides[1]];
        for (size_t d2 = 0; d2 < shape[1]; d2++) {
            size_t offset = d1 * strides[0] + d2 * strides[1];
            if (d1 == d2) {
                B[offset] = 0;
            }
            else {
                B[offset] = - A[offset] / a_ii;
            }
        }
    }
    Tensor<double> d(b.get_shape());
    for (size_t i = 0; i < b.get_size(); i++) {
        d[i] = double(b[i]) / A[i * strides[0] + i * strides[1]];
    }
    Tensor<double> x0(sys.x0.get_shape());
    std::memcpy(x0.get_data(), sys.x0.get_data(), x0.get_size() * sizeof(double)); // TODO: cast memory before copy
    Tensor<double> x(x0.get_shape());
    double diff;
    do {
        x = matmul2D(B, x0) + d;
        diff = dist(x, x0);
        x0 = x;
    } while (diff > accuracy);
    return x;
}


#endif  // MODULES_TASK_2_LEBEDEV_A_JACOBI_ITERATIONS_JACOBI_ITERATIONS_H_
