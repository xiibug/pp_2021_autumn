// Copyright 2021 Ershov Aleksey
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_min_line_mpi.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Sequential_Algorithm) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double* data = new double[9];
    for (size_t i = 0; i < 9; ++i) {
        data[i] = i;
    }
    Matrix testMatrix(data, 3, 3);
    std::vector<double> realResult = { 0, 3, 6 };
    std::vector<double> result;
    if (rank == 0) {
        result = getSequentialMatrixMinLine(testMatrix);
        for (size_t i = 0; i < testMatrix.height; ++i) {
            ASSERT_EQ(result[i], realResult[i]);
        }
    }
    delete[] data;
    data = nullptr;
}

TEST(Parallel_Operations_MPI, Test_Parallel_Algorithm) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double* data = new double[9];
    for (size_t i = 0; i < 9; ++i) {
        data[i] = i;
    }
    Matrix testMatrix(data, 3, 3);
    std::vector<double> realResult = { 0, 3, 6 };
    std::vector<double> result;
    result = getParallelMatrixMinLine(testMatrix);
    if (rank == 0) {
        for (size_t i = 0; i < testMatrix.height; ++i) {
            ASSERT_EQ(result[i], realResult[i]);
        }
    }
    delete[] data;
    data = nullptr;
}

TEST(Parallel_Operations_MPI, Test_Min_Algorithm) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double* data = new double[9];
    for (size_t i = 0; i < 9; ++i) {
        data[i] = i;
    }
    Matrix testMatrix(data, 3, 3);
    std::vector<double> sequentialResult;
    std::vector<double> parallelsResult;
    parallelsResult = getParallelMatrixMinLine(testMatrix);
    if (rank == 0) {
        sequentialResult = getSequentialMatrixMinLine(testMatrix);
        for (size_t i = 0; i < testMatrix.height; ++i) {
            ASSERT_EQ(sequentialResult[i], parallelsResult[i]);
        }
    }
    delete[] data;
    data = nullptr;
}

TEST(Parallel_Operations_MPI, Test_Big_Row_Matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double* data = new double[1000];
    for (size_t i = 0; i < 1000; ++i) {
        data[i] = i;
    }
    Matrix testMatrix(data, 20, 50);
    std::vector<double> sequentialResult;
    std::vector<double> parallelsResult;
    parallelsResult = getParallelMatrixMinLine(testMatrix);
    if (rank == 0) {
        sequentialResult = getSequentialMatrixMinLine(testMatrix);
        for (size_t i = 0; i < testMatrix.height; ++i) {
            ASSERT_EQ(sequentialResult[i], parallelsResult[i]);
        }
    }
    delete[] data;
    data = nullptr;
}

TEST(Parallel_Operations_MPI, Test_Big_Collums_Matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double* data = new double[1000];
    for (size_t i = 0; i < 1000; ++i) {
        data[i] = i;
    }
    Matrix testMatrix(data, 50, 20);
    std::vector<double> sequentialResult;
    std::vector<double> parallelsResult;
    parallelsResult = getParallelMatrixMinLine(testMatrix);
    if (rank == 0) {
        sequentialResult = getSequentialMatrixMinLine(testMatrix);
        for (size_t i = 0; i < testMatrix.height; ++i) {
            ASSERT_EQ(sequentialResult[i], parallelsResult[i]);
        }
    }
    delete[] data;
    data = nullptr;
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
