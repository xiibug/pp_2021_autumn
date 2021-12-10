// Copyright 2021 Shmanalov Alexander
#include <gtest/gtest.h>
#include "./matrix_max_row_element.h"
#include <gtest-mpi-listener.hpp>

TEST(searchMaximumInRows, matrix15x15) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 15, columns = 15;
    int** matrix = nullptr;
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }
    int* parallelResult = nullptr;
    if (rank == 0) {
        generationRandomMatrix(matrix, rows, columns);
        parallelResult = new int[rows];
    }
    parallelSearchMaxElements(matrix, parallelResult, rows, columns);
    if (rank == 0) {
        int* sequentialResult = new int[rows];
        sequentialSearchMaxElements(matrix, sequentialResult, rows, columns);
        for (int i = 0; i < rows; i++) {
            ASSERT_EQ(sequentialResult[i], parallelResult[i]);
        }
    }
}

TEST(searchMaximumInRows, matrix25x50) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 25, columns = 50;
    int** matrix = nullptr;
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }
    int* parallelResult = nullptr;
    if (rank == 0) {
        generationRandomMatrix(matrix, rows, columns);
        parallelResult = new int[rows];
    }
    parallelSearchMaxElements(matrix, parallelResult, rows, columns);
    if (rank == 0) {
        int* sequentialResult = new int[rows];
        sequentialSearchMaxElements(matrix, sequentialResult, rows, columns);
        for (int i = 0; i < rows; i++) {
            ASSERT_EQ(sequentialResult[i], parallelResult[i]);
        }
    }
}

TEST(searchMaximumInRows, matrix50x25) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 50, columns = 25;
    int** matrix = nullptr;
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }
    int* parallelResult = nullptr;
    if (rank == 0) {
        generationRandomMatrix(matrix, rows, columns);
        parallelResult = new int[rows];
    }
    parallelSearchMaxElements(matrix, parallelResult, rows, columns);
    if (rank == 0) {
        int* sequentialResult = new int[rows];
        sequentialSearchMaxElements(matrix, sequentialResult, rows, columns);
        for (int i = 0; i < rows; i++) {
            ASSERT_EQ(sequentialResult[i], parallelResult[i]);
        }
    }
}

TEST(searchMaximumInRows, matrix200x2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 200, columns = 2;
    int** matrix = nullptr;
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }
    int* parallelResult = nullptr;
    if (rank == 0) {
        generationRandomMatrix(matrix, rows, columns);
        parallelResult = new int[rows];
    }
    parallelSearchMaxElements(matrix, parallelResult, rows, columns);
    if (rank == 0) {
        int* sequentialResult = new int[rows];
        sequentialSearchMaxElements(matrix, sequentialResult, rows, columns);
        for (int i = 0; i < rows; i++) {
            ASSERT_EQ(sequentialResult[i], parallelResult[i]);
        }
    }
}

TEST(searchMaximumInRows, matrix1000x1000) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows = 1000, columns = 1000;
    int** matrix = nullptr;
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }
    int* parallelResult = nullptr;
    if (rank == 0) {
        generationRandomMatrix(matrix, rows, columns);
        parallelResult = new int[rows];
    }
    parallelSearchMaxElements(matrix, parallelResult, rows, columns);
    if (rank == 0) {
        int* sequentialResult = new int[rows];
        sequentialSearchMaxElements(matrix, sequentialResult, rows, columns);
        for (int i = 0; i < rows; i++) {
            ASSERT_EQ(sequentialResult[i], parallelResult[i]);
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
