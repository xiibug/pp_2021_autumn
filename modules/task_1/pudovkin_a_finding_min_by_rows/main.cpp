// Copyright 2021 Pudovkin Artem
#include <gtest/gtest.h>
#include <vector>
#include "./finding_min_by_rows.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Finding_Min_By_Rows_MPI, Rows_Eq_Cols_100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_matrix;
    const vector<int>::size_type rowsMatrix = 100;
    const vector<int>::size_type colsMatrix = 100;

    if (rank == 0) {
        global_matrix = getRandomMatrix(rowsMatrix*colsMatrix);
    }

    vector<int> global_min_by_rows = parallelFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);

    if (rank == 0) {
        vector<int> reference_min_by_rows = sequentialFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);
        ASSERT_EQ(global_min_by_rows, reference_min_by_rows);
    }
}

TEST(Parallel_Finding_Min_By_Rows_MPI, Rows_Greater_Cols_200_100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_matrix;
    const vector<int>::size_type rowsMatrix = 200;
    const vector<int>::size_type colsMatrix = 100;

    if (rank == 0) {
        global_matrix = getRandomMatrix(rowsMatrix * colsMatrix);
    }

    vector<int> global_min_by_rows = parallelFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);

    if (rank == 0) {
        vector<int> reference_min_by_rows = sequentialFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);
        ASSERT_EQ(global_min_by_rows, reference_min_by_rows);
    }
}

TEST(Parallel_Finding_Min_By_Rows_MPI, Rows_Less_Cols_100_200) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_matrix;
    const vector<int>::size_type rowsMatrix = 100;
    const vector<int>::size_type colsMatrix = 200;

    if (rank == 0) {
        global_matrix = getRandomMatrix(rowsMatrix * colsMatrix);
    }

    vector<int> global_min_by_rows = parallelFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);

    if (rank == 0) {
        vector<int> reference_min_by_rows = sequentialFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);
        ASSERT_EQ(global_min_by_rows, reference_min_by_rows);
    }
}


TEST(Parallel_Finding_Min_By_Rows_MPI, Rows_Eq_Cols_200_Min_At_End) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_matrix;
    const vector<int>::size_type rowsMatrix = 200;
    const vector<int>::size_type colsMatrix = 200;

    if (rank == 0) {
        global_matrix = getRandomMatrix(rowsMatrix * colsMatrix);

        for (vector<int>::size_type i = 1; i <= rowsMatrix; ++i) {
            global_matrix[i * colsMatrix - 1] = -10000;
        }
    }

    vector<int> global_min_by_rows = parallelFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);

    if (rank == 0) {
        vector<int> reference_min_by_rows = sequentialFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);
        ASSERT_EQ(global_min_by_rows, reference_min_by_rows);
    }
}

TEST(Parallel_Finding_Min_By_Rows_MPI, Rows_Eq_Cols_200_Min_At_Start) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_matrix;
    const vector<int>::size_type rowsMatrix = 200;
    const vector<int>::size_type colsMatrix = 200;

    if (rank == 0) {
        global_matrix = getRandomMatrix(rowsMatrix * colsMatrix);

        for (vector<int>::size_type i = 0; i < rowsMatrix; ++i) {
            global_matrix[i * colsMatrix] = -10000;
        }
    }

    vector<int> global_min_by_rows = parallelFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);

    if (rank == 0) {
        vector<int> reference_min_by_rows = sequentialFindingMinimumByRows(global_matrix, rowsMatrix, colsMatrix);
        ASSERT_EQ(global_min_by_rows, reference_min_by_rows);
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
