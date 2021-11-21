// Copyright 2021 Pudovkin Artem
#include <mpi.h>
#include <vector>
#include <random>
#include <algorithm>
#include "../../../modules/task_1/pudovkin_a_finding_min_by_rows/finding_min_by_rows.h"


vector<int> getRandomMatrix(const vector<int>::size_type size) {
    vector<int> matrix(size);
    std::random_device dev;
    std::mt19937 gen(dev());

    for (vector<int>::size_type i = 0; i < size; ++i) {
        matrix[i] = gen() % 10000;
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
    int delta = 0, countData = 0, unbreakableData = 0, columns = 0;

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        delta = rows / size;
        countData = delta * cols;
        unbreakableData = rows % size;
        columns = cols;

        globalMinByRows.resize(rows);

        for (int proc = 1; proc < size; ++proc) {
            MPI_Send(matrix.data() + unbreakableData * cols + proc * countData, countData, MPI_INT,
                                                                            proc, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Bcast(&delta, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&countData, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&columns, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        localMinByRows.resize(countData);

        MPI_Status status;
        MPI_Recv(localMinByRows.data(), countData, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        localMinByRows = sequentialFindingMinimumByRows(localMinByRows, delta, columns);

        MPI_Send(localMinByRows.data(), delta, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        MPI_Status status;

        localMinByRows = std::vector<int>(matrix.begin(), matrix.begin() + countData + unbreakableData * cols);
        localMinByRows = sequentialFindingMinimumByRows(localMinByRows, delta + unbreakableData, columns);

        vector<int>::size_type lastElement = delta + unbreakableData;
        for (vector<int>::size_type i = 0; i < lastElement; ++i)
            globalMinByRows[i] = localMinByRows[i];

        for (int proc = 1; proc < size; ++proc) {
            MPI_Recv(globalMinByRows.data() + unbreakableData + proc * delta, delta , MPI_INT,
                                                                proc, 0, MPI_COMM_WORLD, &status);
        }
    }

    return globalMinByRows;
}
