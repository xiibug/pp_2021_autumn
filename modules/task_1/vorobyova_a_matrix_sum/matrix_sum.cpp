// Copyright 2021 Vorobyova Anna
#include <mpi.h>
#include <random>
#include "../../../modules/task_1/vorobyova_a_matrix_sum/matrix_sum.h"


int* getRandomMatrix(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    int* matrix = new int[size];
    for (int  i = 0; i < size; i++) {
        matrix[i] = gen() % 100;
    }
    return matrix;
}

int getSequentialSum(int* matrix, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += matrix[i];
    }
    return sum;
}

int getParallelSum(int* matrix, int msize) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta  = msize / size;
    const int remainder = msize % size;

    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            MPI_Send(matrix + proc * delta + remainder, delta,
                        MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }

    int* local_matrix = nullptr;

    if (rank == 0) {
        local_matrix = new int[delta + remainder];
    } else {
        local_matrix = new int[delta];
    }

    if (rank == 0) {
        for (int i = 0; i < delta + remainder; i++) {
            local_matrix[i] = matrix[i];
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_matrix, delta, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    int global_sum = 0;
    int local_sum = 0;

    if (rank == 0) {
        local_sum = getSequentialSum(local_matrix, delta + remainder);
    } else {
        local_sum = getSequentialSum(local_matrix, delta);
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT,
        MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum;
}
