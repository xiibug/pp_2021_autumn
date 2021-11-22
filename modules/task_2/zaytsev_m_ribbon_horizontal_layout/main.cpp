// Copyright 2021 Zaytsev Mikhail
#include <gtest/gtest.h>
#include <vector>
#include "./ribbon_horizontal_layout.h"
#include <gtest-mpi-listener.hpp>

TEST(Sequential_Matrix_Multiplacition, mRows_Eq_mColumns_3_vSize_3) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    if (currentProcess == 0) {
       // The number of columns of the matrix must be equal
       // to the number of elements of the vector
        std::vector<int> matrix = { 2, 4, 0, -2, 1, 3, -1, 0, 1 };
        std::vector<int> vector = { 1, 2, -1 };

        std::vector<int> globalMatrixMultiplication = getSequentialOperations(matrix, 3, 3, vector);
        std::vector<int> referenceMatrixMultiplication = { 10, -3, -2 };
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Sequential_Matrix_Multiplacition, mRows_Gr_mColumns_4_3_vSize_3) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    if (currentProcess == 0) {
        // The number of columns of the matrix must be equal
        // to the number of elements of the vector
        std::vector<int> matrix = { 2, 4, 0, -2, 1, 3, -1, 0, 1, 2, 4, 5 };
        std::vector<int> vector = { 1, 2, -1 };

        std::vector<int> globalMatrixMultiplication = getSequentialOperations(matrix, 4, 3, vector);
        std::vector<int> referenceMatrixMultiplication = { 10, -3, -2, 5 };
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Sequential_Matrix_Multiplacition, mRows_Le_mColumns_3_4_vSize_4) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    if (currentProcess == 0) {
        // The number of columns of the matrix must be equal
        // to the number of elements of the vector
        std::vector<int> matrix = { 2, 4, 0, -2, 1, 3, -1, 0, 1, 2, 4, 5 };
        std::vector<int> vector = { 1, 2, -1, 1 };

        std::vector<int> globalMatrixMultiplication = getSequentialOperations(matrix, 3, 4, vector);
        std::vector<int> referenceMatrixMultiplication = { 8, 8, 6 };
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Eq_mColumns_100_vSize_100) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    // The number of columns of the matrix must be equal
    // to the number of elements of the vector
    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 100;
    const std::vector<int>::size_type matrixColumns = 100;
    std::vector<int> vector;
    const std::vector<int>::size_type vectorSize = 100;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
        getRandomVector(&vector, vectorSize);
    }

    std::vector<int> globalMatrixMultiplication = getParallelOperations(matrix, matrixRows, matrixColumns, vector);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMultiplication = getSequentialOperations(matrix, matrixRows, matrixColumns, vector);
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Eq_mColumns_150_vSize_150) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    // The number of columns of the matrix must be equal
    // to the number of elements of the vector
    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 150;
    const std::vector<int>::size_type matrixColumns = 150;
    std::vector<int> vector;
    const std::vector<int>::size_type vectorSize = 150;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
        getRandomVector(&vector, vectorSize);
    }

    std::vector<int> globalMatrixMultiplication = getParallelOperations(matrix, matrixRows, matrixColumns, vector);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMultiplication = getSequentialOperations(matrix, matrixRows, matrixColumns, vector);
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Eq_mColumns_200_vSize_200) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    // The number of columns of the matrix must be equal
    // to the number of elements of the vector
    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 200;
    const std::vector<int>::size_type matrixColumns = 200;
    std::vector<int> vector;
    const std::vector<int>::size_type vectorSize = 200;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
        getRandomVector(&vector, vectorSize);
    }

    std::vector<int> globalMatrixMultiplication = getParallelOperations(matrix, matrixRows, matrixColumns, vector);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMultiplication = getSequentialOperations(matrix, matrixRows, matrixColumns, vector);
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Gr_mColumns_150_100_vSize_100) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    // The number of columns of the matrix must be equal
    // to the number of elements of the vector
    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 150;
    const std::vector<int>::size_type matrixColumns = 100;
    std::vector<int> vector;
    const std::vector<int>::size_type vectorSize = 100;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
        getRandomVector(&vector, vectorSize);
    }

    std::vector<int> globalMatrixMultiplication = getParallelOperations(matrix, matrixRows, matrixColumns, vector);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMultiplication = getSequentialOperations(matrix, matrixRows, matrixColumns, vector);
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
    }
}

TEST(Parallel_Matrix_Multiplacition, mRows_Le_mColumns_100_150_vSize_150) {
    int currentProcess;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);

    // The number of columns of the matrix must be equal
    // to the number of elements of the vector
    std::vector<int> matrix;
    const std::vector<int>::size_type matrixRows = 100;
    const std::vector<int>::size_type matrixColumns = 150;
    std::vector<int> vector;
    const std::vector<int>::size_type vectorSize = 150;

    if (currentProcess == 0) {
        getRandomMatrix(&matrix, matrixRows * matrixColumns);
        getRandomVector(&vector, vectorSize);
    }

    std::vector<int> globalMatrixMultiplication = getParallelOperations(matrix, matrixRows, matrixColumns, vector);

    if (currentProcess == 0) {
        std::vector<int> referenceMatrixMultiplication = getSequentialOperations(matrix, matrixRows, matrixColumns, vector);
        ASSERT_EQ(globalMatrixMultiplication, referenceMatrixMultiplication);
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
