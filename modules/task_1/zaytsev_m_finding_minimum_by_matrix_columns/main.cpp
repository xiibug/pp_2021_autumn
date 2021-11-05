// Copyright 2021 Zaytsev Mikhail
#include <gtest/gtest.h>
#include "./finding_minimum_by_matrix_columns.h"
#include <gtest-mpi-listener.hpp>


TEST(Finding_Minimum_By_Matrix_Columns, rows_equal_columns) {
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> matrix;
    const int rows = 10, columns = 10;
    std::vector<int> parallelMinimum;

    if (currentRank == 0) {
        matrix = fillMatrix(rows, columns);
    }

    parallelMinimum = parallelFindingMinimum(matrix);

    if (currentRank == 0) {
        std::vector<int> refenceMinimum = singleFindingMinimum(matrix);

        for (int i = 0; i < columns; ++i) {
            ASSERT_EQ(refenceMinimum[i], parallelMinimum[i]);
        }
    }
}

TEST(Finding_Minimum_By_Matrix_Columns, rows_greater_columns) {
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> matrix;
    const int rows = 15, columns = 10;
    std::vector<int> parallelMinimum;

    if (currentRank == 0) {
        matrix = fillMatrix(rows, columns);
    }

    parallelMinimum = parallelFindingMinimum(matrix);

    if (currentRank == 0) {
        std::vector<int> refenceMinimum = singleFindingMinimum(matrix);

        for (int i = 0; i < columns; ++i) {
            ASSERT_EQ(refenceMinimum[i], parallelMinimum[i]);
        }
    }
}

TEST(Finding_Minimum_By_Matrix_Columns, rows_less_columns) {
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> matrix;
    const int rows = 10, columns = 15;
    std::vector<int> parallelMinimum;

    if (currentRank == 0) {
        matrix = fillMatrix(rows, columns);
    }

    parallelMinimum = parallelFindingMinimum(matrix);

    if (currentRank == 0) {
        std::vector<int> refenceMinimum = singleFindingMinimum(matrix);

        for (int i = 0; i < columns; ++i) {
            ASSERT_EQ(refenceMinimum[i], parallelMinimum[i]);
        }
    }
}

TEST(Finding_Minimum_By_Matrix_Columns, minimum_elements_at_the_beginning_of_columns) {
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> matrix;
    const int rows = 10, columns = 10;
    std::vector<int> parallelMinimum;

    if (currentRank == 0) {
        matrix = fillMatrix(rows, columns);
        
        for (int i = 0; i < columns; ++i) {
            matrix[0][i] = -1000000;
        }
    }

    parallelMinimum = parallelFindingMinimum(matrix);

    if (currentRank == 0) {
        std::vector<int> refenceMinimum = singleFindingMinimum(matrix);

        for (int i = 0; i < 10; ++i) {
            ASSERT_EQ(refenceMinimum[i], parallelMinimum[i]);
        }
    }
}

TEST(Finding_Minimum_By_Matrix_Columns, minimum_elements_at_the_ending_of_columns) {
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> matrix;
    const int rows = 10, columns = 10;
    std::vector<int> parallelMinimum;

    if (currentRank == 0) {
        matrix = fillMatrix(rows, columns);

        for (int i = 0; i < columns; ++i) {
            matrix[rows-1][i] = -1000000;
        }
    }

    parallelMinimum = parallelFindingMinimum(matrix);

    if (currentRank == 0) {
        std::vector<int> refenceMinimum = singleFindingMinimum(matrix);

        for (int i = 0; i < 10; ++i) {
            ASSERT_EQ(refenceMinimum[i], parallelMinimum[i]);
        }
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
