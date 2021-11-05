#include <mpi.h>
#include <cstdio>
#include <random>
#include <ctime>
#include "../../../modules/task_1/chornyi_y_find_matrix_min/find_matrix_min.h"

std::vector<std::vector<int>> fillMatrixWithRandom(const int numberOfRows, const int numberOfColumns) {
    std::srand(std::time(0));
    std::vector<std::vector<int>> matrix(numberOfRows);

    for (int i = 0; i < numberOfRows; ++i) {
        matrix[i] = std::vector<int>(numberOfColumns);
        for (int j = 0; j < numberOfColumns; ++j)
            matrix[i][j] = std::rand();
    }

    return matrix;
}
int singleFindMinimum(std::vector<std::vector<int>> matrix) {
    const int numberOfRows = matrix.size(), numberOfColumns = matrix[0].size();
    int minimum = matrix[0][0];

    for (int i = 0; i < numberOfRows; ++i)
        for (int j = 1; j < numberOfColumns; ++j)
            if (minimum > matrix[i][j]) minimum = matrix[i][j];

    return minimum;
}

int parallelFindMinimum(std::vector<std::vector<int>> matrix) {
    int numberOfRows = 0, numberOfColumns = 0;
    int excessData = 0, dataPackage = 0;
    int globalMinimum = 0, localMinimum = 0;

    int numberOfProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    if (currentRank == 0) {
        numberOfRows = matrix.size(), numberOfColumns = matrix[0].size();

        excessData = numberOfRows % numberOfProcess;
        dataPackage = numberOfRows / numberOfProcess;

        for (int i = 1; i < numberOfProcess; ++i) {
            int counterOfRows = excessData + (dataPackage * i);
            for (int j = counterOfRows; j < (counterOfRows + dataPackage); ++j)
                MPI_Send(matrix[j].data(), numberOfColumns, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Bcast(&numberOfRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numberOfColumns, 1, MPI_INT, 0, MPI_COMM_WORLD);

    dataPackage = numberOfRows / numberOfProcess;
    std::vector<std::vector<int>> localMatrix(dataPackage);

    if (currentRank != 0) {
        for (int i = 0; i < dataPackage; ++i)
            localMatrix[i] = std::vector<int>(numberOfColumns);

        MPI_Status status;
        for (int i = 0; i < dataPackage; ++i)
            MPI_Recv(localMatrix[i].data(), numberOfColumns, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }
    else {
        if (excessData) localMatrix.resize(dataPackage + excessData);
        localMatrix = std::vector<std::vector<int>>(matrix.begin(), matrix.begin() + dataPackage + excessData);
    }

    localMinimum = singleFindMinimum(localMatrix);

    MPI_Reduce(&localMinimum, &globalMinimum, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    return globalMinimum;
}