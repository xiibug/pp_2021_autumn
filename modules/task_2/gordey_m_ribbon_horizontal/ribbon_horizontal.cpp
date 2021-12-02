// Copyright 2021 Gordey Maria
#include <mpi.h>
#include <random>
#include "../../../modules/task_2/gordey_m_ribbon_horizontal/ribbon_horizontal.h"


int* initEmptyMatrix(int rows, int cols) {
    int* matrix = new int[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = 0;
    }
    return matrix;
}

int* getRandomMatrix(int rows, int cols) {
    std::random_device dev;
    std::mt19937 gen(dev());
    int* matrix = new int[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = gen() % 20;
    }
    return matrix;
}

void SequentialMatrixMultiplication(int* A, int ARows, int ACols,
    int* B, int BRows, int BCols, int* C) {
    int tmp;
    for (int i = 0; i < ARows; i++) {
        for (int j = 0; j < BCols; j++) {
            C[i * BCols + j] = 0;
            tmp = 0;
            for (int k = 0; k < ACols; k++) {
                tmp += A[i * ACols + k] * B[k * BCols + j];
                C[i * BCols + j] = tmp;
            }
        }
    }
}

void ParallelMatrixMultiplication(int* A, int ARows, int ACols,
    int* B, int BRows, int BCols, int* C) {

    if (ACols != BRows) {
        throw - 1;
    }

    int world_size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int ribbon_width = ARows / world_size;
    const int remainder = ARows % world_size;
    int* ribbon = nullptr;
    int* local_product = nullptr;

    int* Bt = new int[BCols * BRows];

    if (rank == 0) {
        for (int n = 0; n < BRows * BCols; n++) {
            int i = n / BRows;
            int j = n % BRows;
            Bt[n] = B[BCols * j + i];
        }
    }

    MPI_Bcast(Bt, BCols * BRows, MPI_INT, 0, MPI_COMM_WORLD);

    ribbon = new int[ACols * ribbon_width];
    local_product = new int[BCols * ribbon_width];

    MPI_Scatter(A, ribbon_width * ACols, MPI_INT,
        ribbon, ribbon_width * ACols, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < ribbon_width; i++) {
        for (int j = 0; j < BCols; j++) {
            int tmp = 0;
            for (int k = 0; k < ACols; k++) {
                tmp += ribbon[i * ACols + k] * Bt[j * BRows + k];
            }
            local_product[i * BCols + j] = tmp;
        }
    }

    MPI_Gather(local_product, BCols * ribbon_width, MPI_INT,
        C, BCols * ribbon_width, MPI_INT, 0, MPI_COMM_WORLD);

    if (remainder) {
        if (rank == 0) {
            for (int i = ribbon_width * world_size;
                i < ribbon_width * world_size + remainder; i++) {
                for (int j = 0; j < BCols; j++) {
                    int tmp = 0;
                    for (int k = 0; k < ACols; k++) {
                        tmp += A[i * ACols + k] * Bt[j * BRows + k];
                    }
                    C[i * BCols + j] = tmp;
                }
            }
        }
    }
}
