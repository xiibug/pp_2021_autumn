// Copyright 2021 Pudovkin Artem
#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_1/pudovkin_a_finding_min_by_rows/finding_min_by_rows.h"


vector<int> getRandomMatrix(const vector<int>::size_type size) {
    vector<int> matrix(size);
    std::random_device dev;
    std::mt19937 gen(dev());

    for (vector<int>::size_type i = 0; i < size; ++i) {
        matrix[i] = gen() % 1000;
    }
    return matrix;
}

vector<int> sequentialFindingMinimumByRows(vector<int> matrix, const vector<int>::size_type rows,
                                                                const vector<int>::size_type cols) {
    vector<int> minimumByRows(rows);

    for (vector<int>::size_type i = 0; i < rows; ++i) {
        minimumByRows[i] = matrix[i * cols];

        for (vector<int>::size_type j = 0; j < cols; ++j)
            if (minimumByRows[i] > matrix[(i*cols)+j]) minimumByRows[i] = matrix[(i * cols) + j];
    }

    return minimumByRows;
}

vector<int> parallelFindingMinimumByRows(vector<int> matrix, const vector<int>::size_type rows,
                                                              const vector<int>::size_type cols) {
    vector<int> localMinByRows, globalMinByRows;
    int delta = 0;

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    delta = rows / size;

    if (rank == 0) {
        globalMinByRows.resize(rows);
    }

    localMinByRows.resize(delta * cols);

    MPI_Scatter(matrix.data(), delta * cols, MPI_INT,
                localMinByRows.data(), delta * cols, MPI_INT, 0, MPI_COMM_WORLD);

    localMinByRows = sequentialFindingMinimumByRows(localMinByRows, delta, cols);
    MPI_Gather(localMinByRows.data(), delta, MPI_INT, globalMinByRows.data(),
               delta, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (size != 1) {
            int tail = rows - size * delta;
            if (tail) {
                localMinByRows = vector<int>(matrix.begin() + (rows - tail) * cols, matrix.end());
                localMinByRows = sequentialFindingMinimumByRows(localMinByRows, tail, cols);

                for (vector<int>::size_type i = (rows - tail), j = 0; i < rows; ++i, ++j) {
                    globalMinByRows[i] = localMinByRows[j];
                }
            }
        }
    }

    return globalMinByRows;
}
