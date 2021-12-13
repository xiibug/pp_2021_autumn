// Copyright 2021 Lebedev Alexey
#include <mpi.h>
#include <cstring>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include "../../../modules/task_2/lebedev_a_jacobi_iterations/jacobi_iterations.h"


#if SIZE_MAX == UCHAR_MAX
   #define my_MPI_SIZE_T MPI_UNSIGNED_CHAR
#elif SIZE_MAX == USHRT_MAX
   #define my_MPI_SIZE_T MPI_UNSIGNED_SHORT
#elif SIZE_MAX == UINT_MAX
   #define my_MPI_SIZE_T MPI_UNSIGNED
#elif SIZE_MAX == ULONG_MAX
   #define my_MPI_SIZE_T MPI_UNSIGNED_LONG
#elif SIZE_MAX == ULLONG_MAX
   #define my_MPI_SIZE_T MPI_UNSIGNED_LONG_LONG
#endif


float dist(Tensor<float> t1, Tensor<float> t2) {
    if (t1.get_shape() != t2.get_shape()){
        throw std::logic_error("Can't measure distance beetwen tensor with different shapes!");
    }
    float d = 0;
    for (size_t i = 0; i < t1.get_size(); i++) {
        d += std::pow(t1[i] - t2[i], 2);
    }
    return std::sqrt(d);
}


Tensor<float> LinearSystem::solve(const float accuracy) {
    auto shape = A.get_shape();
    auto strides = A.get_strides();
    Tensor<float> B(shape);
    for (size_t d1 = 0; d1 < shape[0]; d1++) {
        float a_ii = A[d1 * strides[0] + d1 * strides[1]];
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
    Tensor<float> d(b.get_shape());
    for (size_t i = 0; i < b.get_size(); i++) {
        d[i] = b[i] / A[i * strides[0] + i * strides[1]];
    }

    Tensor<float> _x0(x0.get_shape());
    std::memcpy(_x0.get_data(), x0.get_data(), x0.get_size() * sizeof(float));
    Tensor<float> x(_x0.get_shape());
    float diff;
    do {
        x = matmul2D(B, _x0) + d;
        diff = dist(x, _x0);
        _x0 = x;
    } while (diff > accuracy);
    return x;
}


Tensor<float> solve_parallel(const LinearSystem& sys, const float accuracy) {
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        size = std::min(size, int(sys.n_dims));
    }

    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Comm NEW_WORLD;
    int color = (rank < size) ? 0 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &NEW_WORLD);
    if (NEW_WORLD == MPI_COMM_NULL) {
        return Tensor<float>();
    }

    size_t d1, d2 = sys.A.get_shape()[1];
    MPI_Bcast(&d2, 1, my_MPI_SIZE_T, 0, NEW_WORLD);

    Tensor<float> B_local({0});
    Tensor<float> d_local({0});
    Tensor<float> x0({d2, 1});
    int diag = 0;

    if (rank == 0) {
        size_t row_per_process = sys.n_dims / size;
        int last_rows = sys.n_dims % size;

        d1 = (last_rows == 0) ? row_per_process : row_per_process + 1;
        size_t _diag_idx = d1;
        B_local = Tensor<float>({d1, d2});
        d_local = Tensor<float>({d1, 1});

        float* buffer_A = sys.A.get_data();
        float* buffer_b = sys.b.get_data();
        float* buffer_x0 = sys.x0.get_data();
        std::memcpy(B_local.get_data(), buffer_A, B_local.get_size() * sizeof(float));
        std::memcpy(d_local.get_data(), buffer_b, d_local.get_size() * sizeof(float));
        std::memcpy(x0.get_data(), buffer_x0, x0.get_size() * sizeof(float));

        buffer_A += B_local.get_size();
        buffer_b += d_local.get_size();

        int count;
        for (int pid = 1; pid < size; pid++) {
            size_t _d1 = (pid < last_rows) ? row_per_process + 1 : row_per_process;
            count = _d1 * d2;
            MPI_Send(&_d1, 1, my_MPI_SIZE_T, pid, 0, NEW_WORLD);
            MPI_Send(buffer_A, count, MPI_FLOAT, pid, 1, NEW_WORLD);
            MPI_Send(buffer_b, _d1, MPI_FLOAT, pid, 2, NEW_WORLD);
            MPI_Send(buffer_x0, d2, MPI_FLOAT, pid, 3, NEW_WORLD);
            MPI_Send(&_diag_idx, 1, my_MPI_SIZE_T, pid, 4, NEW_WORLD);
            buffer_A += count;
            buffer_b += _d1;
            _diag_idx += _d1;
        }
    }
    else {
        MPI_Status status;
        MPI_Recv(&d1, 1, my_MPI_SIZE_T, 0, 0, NEW_WORLD, &status);
        B_local = Tensor<float>({d1, d2});
        d_local = Tensor<float>({d1, 1});
        MPI_Recv(B_local.get_data(), B_local.get_size(), MPI_FLOAT, 0, 1, NEW_WORLD, &status);
        MPI_Recv(d_local.get_data(), d_local.get_size(), MPI_FLOAT, 0, 2, NEW_WORLD, &status);
        MPI_Recv(x0.get_data(), x0.get_size(), MPI_FLOAT, 0, 3, NEW_WORLD, &status);
        MPI_Recv(&diag, 1, my_MPI_SIZE_T, 0, 4, NEW_WORLD, &status);
    }

    size_t stride1 = B_local.get_strides()[0], stride2 = B_local.get_strides()[1];
    for (size_t i = 0; i < d1; i++) {
        size_t diag_idx = i * stride1 + i * stride2 + diag;
        float a_ii = B_local[diag_idx];
        d_local[i] /= a_ii;
        B_local[diag_idx] = 0;
        for (size_t j = 0; j < d2; j++) {
            B_local[i * stride1 + j * stride2] *= - 1 / a_ii;
        }
    }


    Tensor<float> x(x0.get_shape());
    bool solved = false;
    while (!solved) {
        Tensor<float> x_local = matmul2D(B_local, x0) + d_local;
        MPI_Send(x_local.get_data(), x_local.get_size(), MPI_FLOAT, 0, 0, NEW_WORLD);
        if (rank == 0) {
            size_t offset = 0;
            int count;
            for (int i = 0; i < size; i++) {
                MPI_Status status;
                MPI_Probe(i, 0, NEW_WORLD, &status);
                MPI_Get_count(&status, MPI_FLOAT, &count);
                MPI_Recv(x.get_data() + offset, count, MPI_FLOAT, i, 0, NEW_WORLD, &status);
                offset += count;
            }
            float diff = dist(x, x0);
            if (diff <= accuracy) {
                solved = true;
            }
        }
        MPI_Barrier(NEW_WORLD);
        MPI_Bcast(&solved, 1, MPI_CXX_BOOL, 0, NEW_WORLD);
        MPI_Bcast(x.get_data(), x.get_size(), MPI_FLOAT, 0, NEW_WORLD);
        std::memcpy(x0.get_data(), x.get_data(), x.get_size() * sizeof(float));
   }
   MPI_Comm_free(&NEW_WORLD);
   return x;
}
