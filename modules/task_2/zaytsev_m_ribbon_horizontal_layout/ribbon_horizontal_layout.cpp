// Copyright 2021 Zaytsev Mikhail
#include <mpi.h>
#include <vector>
#include <random>
#include <algorithm>
#include "../../../modules/task_2/zaytsev_m_ribbon_horizontal_layout/ribbon_horizontal_layout.h"

void getRandomVector(std::vector<int>* vector, std::vector<int>::size_type vectorSize) {
    std::random_device dev;
    std::mt19937 gen(dev());

    vector->resize(vectorSize);
    for (std::vector<int>::size_type i = 0; i < vectorSize; ++i) {
        vector->at(i) = gen() % 100;
    }
}
void getRandomMatrix(std::vector<int>* matrix, std::vector<int>::size_type matrixSize) {
    std::random_device dev;
    std::mt19937 gen(dev());

    matrix->resize(matrixSize);
    for (std::vector<int>::size_type i = 0; i < matrixSize; ++i) {
        matrix->at(i) = gen() % 100;
    }
}

std::vector<int> getSequentialOperations(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                             std::vector<int>::size_type matrixColumns, std::vector<int> vector) {
    std::vector<int> resultVector(matrixRows);

    for (std::vector<int>::size_type i = 0; i < matrixRows; ++i) {
        int resultValue = 0;
        for (std::vector<int>::size_type j = 0; j < matrixColumns; ++j) {
            resultValue += matrix[(i * matrixColumns) + j] * vector[j];
        }
        resultVector[i] = resultValue;
    }

    return resultVector;
}
std::vector<int> getParallelOperations(const std::vector<int>& matrix, std::vector<int>::size_type matrixRows,
                                           std::vector<int>::size_type matrixColumns, std::vector<int> vector) {
    std::vector<int> localMatrixMultiplication, globalMatrixMultiplication;
    int dataPerProcess = 0, lossData = 0;

    int numberOfProcess, currentProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    dataPerProcess = matrixRows / numberOfProcess;
    lossData = matrixRows % numberOfProcess;

    if (currentProcess == 0) {
        if (lossData) {
            localMatrixMultiplication = std::vector<int>(matrix.begin(), matrix.begin() + lossData * matrixColumns);
            globalMatrixMultiplication = getSequentialOperations(localMatrixMultiplication, lossData,
                                                                              matrixColumns, vector);
        }
        globalMatrixMultiplication.resize(matrixRows);
    } else {
        vector.resize(matrixColumns);
    }
    MPI_Bcast(vector.data(), matrixColumns, MPI_INT, 0, MPI_COMM_WORLD);

    localMatrixMultiplication.resize(dataPerProcess * matrixColumns);

    MPI_Scatter(matrix.data() + (lossData * matrixColumns), dataPerProcess * matrixColumns, MPI_INT,
        localMatrixMultiplication.data(), dataPerProcess * matrixColumns, MPI_INT, 0, MPI_COMM_WORLD);

    localMatrixMultiplication = getSequentialOperations(localMatrixMultiplication, dataPerProcess,
                                                                            matrixColumns, vector);

    MPI_Gather(localMatrixMultiplication.data(), dataPerProcess, MPI_INT, globalMatrixMultiplication.data() + lossData,
        dataPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

    return globalMatrixMultiplication;
}
