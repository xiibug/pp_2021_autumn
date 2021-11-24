// Copyright 2021 Tsyplakov Pavel
#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_2/tsyplakov_p_ribbon_horizontal_layout/ribbon_horizontal_layout.h"

vector<int> getRandomVector(vector<int>::size_type size) {
    std::mt19937 gen(100);
    vector<int> vec(size);
    for (vector<int>::size_type i = 0; i < size; i++) {
        vec[i] = gen();
    }

    return vec;
}
vector<int> getRandomMatrix(vector<int>::size_type size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    vector<int> matrix(size);

    for (vector<int>::size_type i = 0; i < size; i++) {
        matrix[i] = gen() % 10;
    }

    return matrix;
}

vector<int> getSequentialOperations(const vector<int>& globalMatrix, vector<int>::size_type numberOfRows,
                                    vector<int>::size_type numberOfCols, const vector<int>& globalVector) {
    vector<int> resultMultiplication(numberOfRows);

    for (vector<int>::size_type i = 0; i < numberOfRows; ++i) {
        resultMultiplication[i] = 0;
        for (vector<int>::size_type j = 0; j < numberOfCols; ++j) {
            resultMultiplication[i] += globalMatrix[i * numberOfCols + j] * globalVector[j];
        }
    }
    return resultMultiplication;
}

vector<int> getParallelOperations(const vector<int>& globalMatrix, vector<int>::size_type numberOfRows,
                                  vector<int>::size_type numberOfCols, const vector<int>& globalVector) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int delta = numberOfRows / size;
    vector<int> localMatrix(delta * numberOfCols);
    vector<int> globalMult(numberOfRows);

    MPI_Scatter(globalMatrix.data(), delta * numberOfCols, MPI_INT, localMatrix.data(),
                                      delta * numberOfCols, MPI_INT, 0, MPI_COMM_WORLD);

    vector<int> localMult = getSequentialOperations(localMatrix, delta, numberOfCols, globalVector);

    MPI_Gather(localMult.data(), delta, MPI_INT, globalMult.data(), delta, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        vector<int>::size_type tailRows = numberOfRows - (delta * size);
        if (tailRows) {
            localMatrix = vector<int>(globalMatrix.end() - tailRows * numberOfCols, globalMatrix.end());
            localMult = getSequentialOperations(localMatrix, tailRows, numberOfCols, globalVector);

            for (vector<int>::size_type i = numberOfRows - tailRows, j = 0; i < numberOfRows; i++, j++) {
                globalMult[i] = localMult[j];
            }
        }
    }

    return globalMult;
}
