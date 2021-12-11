  // Copyright 2021 Zaytsev Mikhail
#include <mpi.h>
#include <random>
#include "../../../modules/task_1/zaytsev_m_finding_minimum_by_matrix_columns/finding_minimum_by_matrix_columns.h"

void getRandomMatrix(std::vector<int>* matrix, std::vector<int>::size_type matrixSize) {
    std::random_device dev;
    std::mt19937 gen(dev());

    matrix->resize(matrixSize);
    for (std::vector<int>::size_type i = 0; i < matrixSize; ++i) {
        matrix->at(i) = gen() % 10000;
    }
}

std::vector<int> sequentialFindMinimum(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                                                    std::vector<int>::size_type matrixColumns) {
    std::vector<int> vectorOfMinimum(matrixColumns);

    for (std::vector<int>::size_type i = 0; i < matrixColumns; ++i) {
        vectorOfMinimum[i] = matrix[i];
        for (std::vector<int>::size_type j = 1; j < matrixRows; ++j) {
            if (vectorOfMinimum[i] > matrix[matrixColumns * j + i]) vectorOfMinimum[i] = matrix[matrixColumns * j + i];
        }
    }

    return vectorOfMinimum;
}
std::vector<int> parallelFindMinimum(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                                                  std::vector<int>::size_type matrixColumns) {
    std::vector<int> localVectorOfMinimum, globalVectorOfMinimum;
    int dataPerProcess = 0, lossData = 0;

    int numberOfProcess, currentProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    dataPerProcess = matrixRows / numberOfProcess;
    lossData = matrixRows % numberOfProcess;

    if (currentProcess == 0) {
        globalVectorOfMinimum.resize(matrixColumns);
    }

    localVectorOfMinimum.resize(dataPerProcess * matrixColumns);

    MPI_Scatter(matrix.data() + lossData * matrixColumns, dataPerProcess * matrixColumns, MPI_INT,
          localVectorOfMinimum.data(), dataPerProcess * matrixColumns, MPI_INT, 0, MPI_COMM_WORLD);

    localVectorOfMinimum = sequentialFindMinimum(localVectorOfMinimum, dataPerProcess, matrixColumns);

    MPI_Reduce(localVectorOfMinimum.data(), globalVectorOfMinimum.data(), matrixColumns,
                                                    MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (currentProcess == 0) {
        if (lossData) {
            localVectorOfMinimum = std::vector<int>(matrix.begin(), matrix.begin() + lossData * matrixColumns);
            localVectorOfMinimum = sequentialFindMinimum(localVectorOfMinimum, lossData, matrixColumns);

            for (std::vector<int>::size_type i = 0; i < matrixColumns; ++i) {
                if (globalVectorOfMinimum[i] > localVectorOfMinimum[i]) {
                    globalVectorOfMinimum[i] = localVectorOfMinimum[i];
                }
            }
        }
    }

    return globalVectorOfMinimum;
}
