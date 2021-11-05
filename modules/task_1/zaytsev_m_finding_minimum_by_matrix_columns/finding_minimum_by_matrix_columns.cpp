// Copyright 2021 Zaytsev Mikhail

#include <mpi.h>
#include "../../../modules/task_1/zaytsev_m_finding_minimum_by_matrix_columns/finding_minimum_by_matrix_columns.h"

std::vector<std::vector<int>> fillMatrix(const int rows, const int columns) {
    std::vector<std::vector<int>> matrix(rows);

    for (int i = 0; i < rows; ++i) {
        matrix[i] = std::vector<int>(columns);
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = (columns - j) * (rows - i);
        }
    }

    return matrix;
}

// Print matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size(), columns = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Transponse matrix
std::vector<std::vector<int>> transponseMatrix(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size(), columns = matrix[0].size();
    std::vector<std::vector<int>> buff(columns);

    for (int i = 0; i < columns; ++i) {
        buff[i] = std::vector<int>(rows);
        for (int j = 0; j < rows; ++j) {
            buff[i][j] = matrix[j][i];
        }
    }

    return buff;
}

// One process find minimum fucntion
std::vector<int> singleFindingMinimum(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size(), columns = matrix[0].size();
    std::vector<int> minimum(columns);

    for (int i = 0; i < columns; ++i) {
        minimum[i] = matrix[0][i];
        for (int j = 1; j < rows; ++j) {
            if (minimum[i] > matrix[j][i]) minimum[i] = matrix[j][i];
        }
    }

    return minimum;
}

std::vector<int> parallelFindingMinimum(const std::vector<std::vector<int>>& matrix) {
    int rows = 0, columns = 0, lossElement = 0, portionData = 0;
    std::vector<std::vector<int>> localMatrix;
    std::vector<int> globalMin, localMin;

    int countProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &countProcess);
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    if (currentRank == 0) {
        localMatrix = matrix;
        rows = matrix.size(), columns = matrix[0].size();

        localMatrix = transponseMatrix(localMatrix);
        if (rows != columns) {
            std::swap(rows, columns);
        }

        globalMin.resize(rows);

        lossElement = rows % countProcess;
        portionData = rows / countProcess;

        for (int i = 1; i < countProcess; ++i) {
            int counterRows = lossElement + portionData * i;
            for (int j = counterRows; j < (counterRows + portionData); ++j) {
                MPI_Send(localMatrix[j].data(), columns, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&columns, 1, MPI_INT, 0, MPI_COMM_WORLD);

    portionData = rows / countProcess;
    if (currentRank != 0) {
        localMatrix.resize(portionData);

        for (int i = 0; i < portionData; ++i) {
            localMatrix[i] = std::vector<int>(columns);
        }

        MPI_Status status;
        for (int i = 0; i < portionData; ++i) {
            MPI_Recv(localMatrix[i].data(), columns, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }

        localMin.resize(portionData);

        for (int i = 0; i < portionData; ++i) {
            localMin[i] = localMatrix[i][0];
            for (int j = 1; j < columns; ++j) {
                if (localMin[i] > localMatrix[i][j]) localMin[i] = localMatrix[i][j];
            }
            MPI_Send(&localMin[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    } else {
        localMin.resize(portionData + lossElement);

        for (int i = 0; i < (portionData + lossElement); ++i) {
            localMin[i] = localMatrix[i][0];
            for (int j = 0; j < columns; ++j) {
                if (localMin[i] > localMatrix[i][j]) localMin[i] = localMatrix[i][j];
            }
            globalMin[i] = localMin[i];
        }
    }



    if (currentRank == 0) {
        MPI_Status status;
        for (int i = 1; i < countProcess; ++i) {
            for (int j = (lossElement + portionData * i); j < ((lossElement + portionData * i) + portionData); ++j) {
                MPI_Recv(&globalMin[j], 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            }
        }
    }

    return globalMin;
}
