// Copyright 2021 Zaytsev Mikhail
#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include "../../../modules/task_3/zaytsev_m_linear_stretching_of_histogram/linear_stretching_of_histogram.h"

using std::vector;

double calculatedNewPixelColor(const vector<double>& matrix, vector<double>::size_type matrixRows,
    vector<double>::size_type matrixColumns, const double maxValue, const double minValue, const int x, const int y) {
    double linearHistogramValue = 0;
    if (!((maxValue - minValue) == 0)) {
        linearHistogramValue = (matrix[matrixColumns * x + y] - minValue) * (1.f / (maxValue - minValue));
    }

    return linearHistogramValue;
}
void findMaxAndMinValue(const vector<double>& matrix, vector<double>::size_type matrixRows,
    vector<double>::size_type matrixColumns, double* maxValue, double* minValue) {
    *maxValue = 0;
    *minValue = 1;

    for (int x = 0; x < matrixRows; ++x) {
        for (int y = 0; y < matrixColumns; ++y) {
            double currentValue = matrix[matrixColumns * x + y];
            if (currentValue > *maxValue) {
                *maxValue = currentValue;
            }
            else if (currentValue < *minValue) {
                *minValue = currentValue;
            }
        }
    }
}

void getRandomMatrix(vector<double>* matrix, vector<double>::size_type matrixSize) {
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(0, 1);

    matrix->resize(matrixSize);
    for (vector<double>::size_type i = 0; i < matrixSize; ++i) {
        matrix->at(i) = urd(gen);
    }
}

vector<double> getSequentialOperations(const vector<double>& matrix, vector<double>::size_type matrixRows,
    vector<double>::size_type matrixColumns, const double maxValue, const double minValue) {

    vector<double> resultMatrix(matrixRows * matrixColumns);

    for (int x = 0; x < matrixRows; ++x) {
        for (int y = 0; y < matrixColumns; y++) {
            double value = calculatedNewPixelColor(matrix, matrixRows, matrixColumns, maxValue, minValue, x, y);
            resultMatrix[matrixColumns * x + y] = value;
        }
    }

    return resultMatrix;
}
vector<double> getParallelOperations(const vector<double>& matrix, vector<double>::size_type matrixRows,
    vector<double>::size_type matrixColumns) {

    vector<double> localMatrix, globalMatrix;
    double maxValue = 0, minValue = 1;
    int dataPerProcess = 0, lossData = 0;

    int numberOfProcess, currentProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    dataPerProcess = matrixRows / numberOfProcess;
    lossData = matrixRows % numberOfProcess;

    if (currentProcess == 0) {
        findMaxAndMinValue(matrix, matrixRows, matrixColumns, &maxValue, &minValue);
        if (lossData) {
            localMatrix = vector<double>(matrix.begin(), matrix.begin() + lossData * matrixColumns);
            globalMatrix = getSequentialOperations(localMatrix, lossData, matrixColumns, maxValue, minValue);
        }
        globalMatrix.resize(matrixRows * matrixColumns);
    }

    MPI_Bcast(&maxValue, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&minValue, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    localMatrix.resize(dataPerProcess * matrixColumns);

    MPI_Scatter(matrix.data() + (lossData * matrixColumns), dataPerProcess * matrixColumns, MPI_DOUBLE,
        localMatrix.data(), dataPerProcess * matrixColumns, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    localMatrix = getSequentialOperations(localMatrix, dataPerProcess, matrixColumns, maxValue, minValue);

    MPI_Gather(localMatrix.data(), dataPerProcess * matrixColumns, MPI_DOUBLE, globalMatrix.data() +
        lossData * matrixColumns, dataPerProcess * matrixColumns, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    return globalMatrix;
}