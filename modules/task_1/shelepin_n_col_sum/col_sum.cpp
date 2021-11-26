// Copyright 2021 Shelepin Nikita
#include "../../../modules/task_1/shelepin_n_col_sum/col_sum.h"
#include <mpi.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

int* randomMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        throw - 1;

    int* a = new int[rows * cols];

    for (int i = 0; i < rows * cols; i++)
        a[i] = (static_cast<double>(std::rand()) / RAND_MAX) * 10 + 1;

    return a;
}

int* sequentialSum(int* matrix, int rows, int cols) {
    int* answer = new int[cols];
    for (int i = 0; i < cols; i++)
        answer[i] = 0;

    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            answer[j] += matrix[j + i * cols];

    return answer;
}

int* parallelSum(int* initial_matrix, int n, int m) {
    if (n <= 0 || m <= 0)
        throw - 1;

    int rows = 0, cols = 0;
    int* matrix = nullptr;
    int* buffer;
    int* sum, * sum_all;

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        int empty = 0;
        if (n % world_size != 0)
            empty = (n / world_size + 1) * world_size - n;

        matrix = new int[(n + empty) * m];

        for (int i = 0; i < n * m; i++)
            matrix[i] = initial_matrix[i];
        for (int i = n * m; i < (n + empty) * m; i++)
            matrix[i] = 0;

        rows = n + empty;
        cols = m;
    }

    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);

    rows = rows / world_size;
    buffer = new int[rows * cols];

    MPI_Scatter(matrix, rows * cols, MPI_INT,
        buffer, rows * cols, MPI_INT, 0, MPI_COMM_WORLD);

    sum_all = new int[cols];
    sum = sequentialSum(buffer, rows, cols);

    MPI_Reduce(sum, sum_all, cols, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return sum_all;
}
