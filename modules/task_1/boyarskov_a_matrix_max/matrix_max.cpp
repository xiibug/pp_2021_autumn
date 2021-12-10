// Copyright 2021 Boyarskov Anton
#include <mpi.h>
#include <random>
#include "../../../modules/task_1/boyarskov_a_matrix_max/matrix_max.h"


int* getRandomMatrix(int n, int m) {
    std::random_device dev;
    std::mt19937 gen(dev());
    int* matrix = new int[n * m];
    for (int i = 0; i < n * m; i++) { matrix[i] = gen() % 100; }
    return matrix;
}

int getSequentialMax(int* matrix, int n, int m) {
    int max = matrix[0];
    for (int i = 0; i < n * m; i++)
        if (max < matrix[i]) {
            max = matrix[i];
        }

    return max;
}

int getParallelMax(int* global_matrix, int n, int m) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int elem_count = n * m / size;
    const int delta = n * m % size;

    int* local_matrix = new int[elem_count];

    MPI_Scatter(global_matrix + delta, elem_count, MPI_INT,
        local_matrix, elem_count, MPI_INT, 0, MPI_COMM_WORLD);

    int local_max = getSequentialMax(local_matrix, 1, elem_count);
    int global_max = local_matrix[0];
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < delta; i++) {
            if (global_max < global_matrix[i]) {
                global_max = global_matrix[i];
            }
        }
    }

    return global_max;
}
