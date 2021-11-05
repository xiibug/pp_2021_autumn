// Copyright 2021 Vanyushkov Maxim
#include <gtest/gtest.h>
#include "./max_value_matrix.h"
#include <gtest-mpi-listener.hpp>

TEST(seq_and_par_check_equivalence, all_elements_equal_value15_matrix_size_10) {
    int procRank = 0;
    const int matrixLen = 10;
    int* matrix = nullptr;
    int value = 15;

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        matrix = new int[matrixLen];
        for (int i = 0; i < matrixLen; i++) {
            matrix[i] = value;
        }
    }
    int globalAlternations = parallelMax(matrix, matrixLen);
    if (procRank == 0) {
        delete[] matrix;
        ASSERT_EQ(value, globalAlternations);
    }
}

TEST(seq_and_par_check_equivalence, elements_in_ascending_order_matrix_size_200) {
    int procRank = 0;
    const int matrixLen = 200;
    int* matrix = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        matrix = new int[matrixLen];
        for (int i = 0; i < matrixLen; i++) {
            matrix[i] = i + 1;
        }
    }
    int globalAlternations = parallelMax(matrix, matrixLen);
    if (procRank == 0) {
        delete[] matrix;
        ASSERT_EQ(matrixLen, globalAlternations);
    }
}

TEST(seq_and_par_check_equivalence, elements_in_descending_order_matrix_size_2000) {
    int procRank = 0;
    const int matrixLen = 2000;
    int* matrix = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        matrix = new int[matrixLen];
        for (int i = 0; i < matrixLen; i++) {
            matrix[i] = matrixLen - i;
        }
    }
    int globalAlternations = parallelMax(matrix, matrixLen);
    if (procRank == 0) {
        delete[] matrix;
        ASSERT_EQ(matrixLen, globalAlternations);
    }
}

TEST(seq_and_par_check_equivalence, random_value_matrix_size_10) {
    int procRank = 0;
    const int matrixLen = 10;
    int* matrix = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        matrix = new int[matrixLen];
        fillMatrixRandValue(matrix, matrixLen);
    }
    int globalAlternations = parallelMax(matrix, matrixLen);
    if (procRank == 0) {
        int referenceAlternations = sequentialMax(matrix, matrixLen);
        delete[] matrix;
        ASSERT_EQ(referenceAlternations, globalAlternations);
    }
}

TEST(seq_and_par_check_equivalence, random_value_matrix_size_20001) {
    int procRank = 0;
    const int matrixLen = 20001;
    int* matrix = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        matrix = new int[matrixLen];
        fillMatrixRandValue(matrix, matrixLen);
    }
    int globalAlternations = parallelMax(matrix, matrixLen);
    if (procRank == 0) {
        int referenceAlternations = sequentialMax(matrix, matrixLen);
        delete[] matrix;
        ASSERT_EQ(referenceAlternations, globalAlternations);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);  // check for MPI_SUCCESS?

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}

