// Copyright 2021 Mironova Ekaterina
#include "../../../modules/task_1/mironova_e_max_in_matrix_rows/max_in_matrix_rows.h"
#include <string>
#include <random>
#include <algorithm>

std::vector<int> fillRandomMatrix(const int rows, const int columns) {
    if (rows <=0 ||columns <= 0) throw "Matrix size is uncorrect";
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> matrix(rows * columns);
    for (int i = 0; i < rows * columns; i++) {
        matrix[i] = gen() % 100;
    }
    return matrix;
}

std::vector<int> findMaxesInMatrixRows(std::vector<int> matrix, const int columns) {
    if (matrix.size() == 0 || columns <= 0) throw "Matrix is empty or number of columns is uncorrect";
    std::vector<int> maxesInRows;
    int max;
    for (int i = 0; i < matrix.size(); i += columns) {
        max = matrix[i];
        for (int j = 1; j < columns; j++) {
            if (matrix[i + j] > max) {
                max = matrix[i + j];
            }
        }
        maxesInRows.push_back(max);
    }
    return maxesInRows;
}

std::vector<int> parallelFindMaxesInMatrixRows(std::vector<int> matrix, const int rows, const int columns) {
    if (matrix.size() == 0 || columns <= 0 || rows <= 0) throw "Matrix is empty or size is uncorrect";
    std::vector<int> partOfMatrix, maxesInRows, resultMaxesInRows;
    int dataPiece = 0;
    int remainingData = 0;
    int max = 0;
    int procNum, procRank;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    dataPiece = rows / procNum;
    remainingData = rows % procNum;

    partOfMatrix.resize(dataPiece * columns);
    resultMaxesInRows.resize(dataPiece);

    MPI_Scatter(matrix.data(), dataPiece * columns, MPI_INT, 
                partOfMatrix.data(), dataPiece * columns, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < partOfMatrix.size(); i += columns) {
        max = partOfMatrix[i];
        for (int j = 1; j < columns; j++) {
            if (partOfMatrix[i + j] > max) {
                max = partOfMatrix[i + j];
            }
        }
        maxesInRows.push_back(max);
    }

    MPI_Gather(maxesInRows.data(), dataPiece, MPI_INT, resultMaxesInRows.data(), dataPiece, MPI_INT, 0, MPI_COMM_WORLD);

    if ((procRank == 0) && (remainingData != 0)) {
        for (int i = dataPiece * columns; i < matrix.size(); i += columns) {
            max = matrix[i];
            for (int j = 1; j < columns; j++) {
                if (matrix[i + j] > max) {
                    max = matrix[i + j];
                }
            }
            resultMaxesInRows.push_back(max);
        }
    }

    return resultMaxesInRows;
}
