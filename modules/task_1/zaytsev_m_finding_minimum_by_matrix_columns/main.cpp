 // Copyright 2021 Zaytsev Mikhail
#include <gtest/gtest.h>
#include "./finding_minimum_by_matrix_columns.h"
#include <gtest-mpi-listener.hpp>

TEST(Sequential_Finding_Minimum_By_Matrix_Columns, Rows_Equal_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    if (currentProcess == 0) {
        std::vector<int> matrix = { 2, 4, 0, -2, 1, 3, -1, 0, 1 };

        std::vector<int> globalMatrixMultiplication = getSequentialOperations(matrix, 3, 3);
        std::vector<int> referenceMatrixMultiplication = { -2, 0, 0 };
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Sequential_Finding_Minimum_By_Matrix_Columns, Rows_Greater_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    if (currentProcess == 0) {
        std::vector<int> matrix = { 2, 4, 0, -2, 1, 3, -1, 0, -10, 2, 4, 5 };

        std::vector<int> globalMatrixMultiplication = getSequentialOperations(matrix, 4, 3);
        std::vector<int> referenceMatrixMultiplication = { -2, 0, -10 };
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Sequential_Finding_Minimum_By_Matrix_Columns, Rows_Less_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    if (currentProcess == 0) {
        std::vector<int> matrix = { 2, 4, 0, -2, 1, 3, -1, 0, 1, 2, 4, 5 };

        std::vector<int> globalMatrixMultiplication = getSequentialOperations(matrix, 3, 4);
        std::vector<int> referenceMatrixMultiplication = { 1, 2, -1, -2 };
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Parallel_Finding_Minimum_By_Matrix_Columns, Rows_Equal_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 10;
    const std::vector<int>::size_type matrixColumns = 10;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<int> globalMatrixMinimum = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMinimum = getSequentialOperations(matrix, matrixRows, matrixColumns);
        ASSERT_EQ(globalMatrixMinimum, referenceMatrixMinimum);
    }
}

TEST(Parallel_Finding_Minimum_By_Matrix_Columns, Rows_Greater_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 200;
    const std::vector<int>::size_type matrixColumns = 100;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<int> globalMatrixMinimum = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMinimum = getSequentialOperations(matrix, matrixRows, matrixColumns);
        ASSERT_EQ(globalMatrixMinimum, referenceMatrixMinimum);
    }
}

TEST(Parallel_Finding_Minimum_By_Matrix_Columns, Rows_Less_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 100;
    const std::vector<int>::size_type matrixColumns = 200;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
    }

    std::vector<int> globalMatrixMinimum = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMinimum = getSequentialOperations(matrix, matrixRows, matrixColumns);
        ASSERT_EQ(globalMatrixMinimum, referenceMatrixMinimum);
    }
}

TEST(Parallel_Finding_Minimum_By_Matrix_Columns, Minimum_Elements_At_The_Beginning_Of_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 100;
    const std::vector<int>::size_type matrixColumns = 100;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);

        for (std::vector<int>::size_type i = 0; i < matrixRows; ++i) {
            matrix[matrixColumns * i] = -100000;
        }
    }

    std::vector<int> globalMatrixMinimum = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMinimum = getSequentialOperations(matrix, matrixRows, matrixColumns);
        ASSERT_EQ(globalMatrixMinimum, referenceMatrixMinimum);
    }
}

TEST(Parallel_Finding_Minimum_By_Matrix_Columns, Minimum_Elements_At_The_Ending_Of_Columns) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 100;
    const std::vector<int>::size_type matrixColumns = 100;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);

        for (std::vector<int>::size_type i = 0; i < matrixRows; ++i) {
            matrix[matrixColumns * (i + 1) - 1] = -100000;
        }
    }

    std::vector<int> globalMatrixMinimum = getParallelOperations(matrix, matrixRows, matrixColumns);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMinimum = getSequentialOperations(matrix, matrixRows, matrixColumns);
        ASSERT_EQ(globalMatrixMinimum, referenceMatrixMinimum);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
