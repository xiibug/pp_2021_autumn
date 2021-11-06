// Copyright 2021 Gordeev Viktor
#include <mpi.h>
#include <string>
#include <random>
#include <algorithm>
#include "./matrix_min_line_mpi.h"

void getRandomVector(int* vec, int rows, int columns) {
    std::random_device dev;
    std::mt19937 gen(dev());
    int size = rows * columns;
    for (int i = 0; i < size; i++) {
        vec[i] = gen() % 100;
    }
}

void getSequentialMatrixMinLine(const int* vec, int* res,
    int count_rows_vector, int count_columns_vector) {
    for (int i = 0; i < count_rows_vector; i++) {
        int min = 101;
        for (int j = 0; j < count_columns_vector; j++) {
            if (vec[i * count_columns_vector + j] < min)
                min = vec[i * count_columns_vector + j];
        }
        res[i] = min;
    }
}

void getParallelMatrixMinLine(const int* global_vec, int* res_vec,
    int count_rows_vector, int count_columns_vector) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta = count_rows_vector / size;
    int* vec = new int[count_columns_vector * delta];
    MPI_Scatter(global_vec, count_columns_vector * delta, MPI_INT,
        vec, count_columns_vector * delta, MPI_INT, 0, MPI_COMM_WORLD);
    int* localMin = new int[delta];
    for (int i = 0; i < delta; i++) {
        int min = 101;
        for (int j = 0; j < count_columns_vector; j++) {
            if (vec[i * count_columns_vector + j] < min) {
                min = vec[i * count_columns_vector + j];
            }
        }
        localMin[i] = min;
    }
    MPI_Gather(localMin, delta, MPI_INT, res_vec,
        delta, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        int tail = count_rows_vector - size * delta;
        for (int i = tail + 1; i < count_rows_vector; i++) {
            int min = 101;
            for (int j = 0; j < count_columns_vector; j++) {
                min = minSearch(global_vec[i * count_columns_vector + j], min);
            }
            res_vec[i] = min;
        }
    }
    delete[] localMin;
    delete[] vec;
}

int minSearch(int a, int b) {
    if (a <= b)
        return a;
    else
        return b;
}
