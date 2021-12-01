// Copyright 2021 Zaytsev Mikhail
#include <gtest/gtest.h>
#include <vector>
#include "./linear_stretching_of_histogram.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Matrix_Multiplacition, mRows_Eq_mColumns_100) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<double> matrix;
    const std::vector<double>::size_type matrixRows = 100;
    const std::vector<double>::size_type matrixColumns = 100;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<double> globalMatrix = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        double maxValue, minValue;
        findMaxAndMinValue(matrix, matrixRows, matrixColumns, &maxValue, &minValue);
        std::vector<double> referenceMatrix = getSequentialOperations(matrix, matrixRows,
            matrixColumns, maxValue, minValue);
        ASSERT_EQ(globalMatrix, referenceMatrix);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Eq_mColumns_150) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<double> matrix;
    const std::vector<double>::size_type matrixRows = 150;
    const std::vector<double>::size_type matrixColumns = 150;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<double> globalMatrix = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        double maxValue, minValue;
        findMaxAndMinValue(matrix, matrixRows, matrixColumns, &maxValue, &minValue);
        std::vector<double> referenceMatrix = getSequentialOperations(matrix, matrixRows,
            matrixColumns, maxValue, minValue);
        ASSERT_EQ(globalMatrix, referenceMatrix);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Eq_mColumns_200) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<double> matrix;
    const std::vector<double>::size_type matrixRows = 200;
    const std::vector<double>::size_type matrixColumns = 200;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<double> globalMatrix = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        double maxValue, minValue;
        findMaxAndMinValue(matrix, matrixRows, matrixColumns, &maxValue, &minValue);
        std::vector<double> referenceMatrix = getSequentialOperations(matrix, matrixRows,
            matrixColumns, maxValue, minValue);
        ASSERT_EQ(globalMatrix, referenceMatrix);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Gr_mColumns_150_100) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<double> matrix;
    const std::vector<double>::size_type matrixRows = 150;
    const std::vector<double>::size_type matrixColumns = 100;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<double> globalMatrix = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        double maxValue, minValue;
        findMaxAndMinValue(matrix, matrixRows, matrixColumns, &maxValue, &minValue);
        std::vector<double> referenceMatrix = getSequentialOperations(matrix, matrixRows,
            matrixColumns, maxValue, minValue);
        ASSERT_EQ(globalMatrix, referenceMatrix);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Le_mColumns_100_150) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<double> matrix;
    const std::vector<double>::size_type matrixRows = 100;
    const std::vector<double>::size_type matrixColumns = 150;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<double> globalMatrix = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        double maxValue, minValue;
        findMaxAndMinValue(matrix, matrixRows, matrixColumns, &maxValue, &minValue);
        std::vector<double> referenceMatrix = getSequentialOperations(matrix, matrixRows,
            matrixColumns, maxValue, minValue);
        ASSERT_EQ(globalMatrix, referenceMatrix);
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
