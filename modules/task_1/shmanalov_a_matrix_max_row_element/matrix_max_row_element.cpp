// Copyright 2021 Shmanalov Alexander
#include <mpi.h>
#include <random>
#include <climits>
#include "../../../modules/task_1/shmanalov_a_matrix_max_row_element/matrix_max_row_element.h"

void generationRandomMatrix(int** matrix, int rows, int columns) {
    std::random_device random;
    std::mt19937 generate(random());
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = generate() % 1000;
        }
    }
}

int* matrixToVector(int** matrix, int rows, int columns) {
    int* vector = new int[rows * columns];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            vector[i * columns + j] = matrix[i][j];
        }
    }
    return vector;
}

void sequentialSearchMaxElements(int** matrix, int* result,
    int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        int max = matrix[i][0];
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
        result[i] = max;
    }
}

void parallelSearchMaxElements(int** matrix, int* result,
    int rows, int columns) {
    // MPI information
    int processRank, numberOfProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    // convert matrix to vector
    int* sendBuffer = matrixToVector(matrix, rows, columns);
    // data separation
    int possibleDivision = rows % numberOfProcess;
    if (possibleDivision == 0) {
        int partData = rows / numberOfProcess;
        int* recvBuffer = new int[columns * partData];
        MPI_Scatter(sendBuffer, columns * partData, MPI_INT,
            recvBuffer, columns * partData, MPI_INT, 0, MPI_COMM_WORLD);
        // finding the maximum in the data part
        int* maxPartData = new int[partData];
        for (int i = 0; i < partData; i++) {
            int max = INT_MIN;
            for (int j = 0; j < columns; j++) {
                if (recvBuffer[i * columns + j] > max) {
                    max = recvBuffer[i * columns + j];
                }
            }
            maxPartData[i] = max;
        }
        MPI_Gather(maxPartData, partData, MPI_INT,
            result, partData, MPI_INT, 0, MPI_COMM_WORLD);
        // clearing intermediate data
        delete[] sendBuffer;
        delete[] recvBuffer;
        delete[] maxPartData;
    } else {
        if (processRank == 0) {
            sequentialSearchMaxElements(matrix, result, rows, columns);
        }
    }
}

