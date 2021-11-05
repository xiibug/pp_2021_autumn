// Copyright 2021 Chornyi Yurii
#include <mpi.h>
#include <cstdio>
#include <random>
#include <ctime>
#include <vector>

#include "../../../modules/task_1/chornyi_y_find_matrix_min/find_matrix_min.h"

std::vector<std::vector<int>> fillMatrixWithRandom(const int numberOfRows, const int numberOfColumns) {
    std::srand(std::time(0));  // Set the seed depending on the current time
    std::vector<std::vector<int>> matrix(numberOfRows);

    for (int i = 0; i < numberOfRows; ++i) {  // Filling the matrix with random values
        matrix[i] = std::vector<int>(numberOfColumns);
        for (int j = 0; j < numberOfColumns; ++j) {
            matrix[i][j] = std::rand();
        }
    }

    return matrix;
}
int singleFindMinimum(std::vector<std::vector<int>> matrix) {
    const int numberOfRows = matrix.size(), numberOfColumns = matrix[0].size();  // Main information about matrix
    int minimum = matrix[0][0];  // First assigment minimum

    for (int i = 0; i < numberOfRows; ++i) {  // Find minimum in the whole matrix
        for (int j = 0; j < numberOfColumns; ++j) {
            if (minimum > matrix[i][j]) minimum = matrix[i][j];
        }
    }

    return minimum;
}

int parallelFindMinimum(std::vector<std::vector<int>> matrix) {
    int numberOfRows = 0, numberOfColumns = 0;  // Main information about matrix
    int excessData = 0, dataPackage = 0;  // Necessary variables to send data between processes
    int globalMinimum = 0, localMinimum = 0;  // Interprocess minimum and process minimum

    int numberOfProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    if (currentRank == 0) {
        // Receving main information about matrix
        numberOfRows = matrix.size(), numberOfColumns = matrix[0].size();

        // Calculating the amount of data that the root process will leave
        excessData = numberOfRows % numberOfProcess;
        // Calculating the amount of data that is distributed between the process
        dataPackage = numberOfRows / numberOfProcess;

        // Sending data packages
        for (int i = 1; i < numberOfProcess; ++i) {
            int counterOfRows = excessData + (dataPackage * i);
            for (int j = counterOfRows; j < (counterOfRows + dataPackage); ++j) {
                MPI_Send(matrix[j].data(), numberOfColumns, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    MPI_Bcast(&numberOfRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numberOfColumns, 1, MPI_INT, 0, MPI_COMM_WORLD);

    dataPackage = numberOfRows / numberOfProcess;

    // Allocating memory for the local matrix at each process
    std::vector<std::vector<int>> localMatrix(dataPackage);

    if (currentRank != 0) {
        for (int i = 0; i < dataPackage; ++i) {
            localMatrix[i] = std::vector<int>(numberOfColumns);
        }

        // Receving data packages
        MPI_Status status;
        for (int i = 0; i < dataPackage; ++i) {
            MPI_Recv(localMatrix[i].data(), numberOfColumns, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
                     &status);
        }
    } else {
        // Re-allocate memory for the local matrix,
        // if there are additional data packets on root process
        if (excessData) {
            localMatrix.resize(dataPackage + excessData);
        }
        localMatrix = std::vector<std::vector<int>>(matrix.begin(), matrix.begin() + dataPackage + excessData);
    }

    localMinimum = singleFindMinimum(localMatrix);  // Calculating minimum at each process

    // Collect the result for each process in the root process
    MPI_Reduce(&localMinimum, &globalMinimum, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    return globalMinimum;
}
