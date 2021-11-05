// Copyright 2021 Chornyi Yurii

#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "mpi.h"
#include <vector>
#include "./find_matrix_min.h"


TEST(Parallel_Find_Minimum_In_Matrix, Rows_Equal_Columns) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> globalMatrix;
    const int numberOfRows = 10, numberOfColumns = 10;
    int parallelMinimum, singleMinimum;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixWithRandom(numberOfRows, numberOfColumns);

        singleMinimum = singleFindMinimum(globalMatrix);
    }

    parallelMinimum = parallelFindMinimum(globalMatrix);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleMinimum, parallelMinimum);
    }
}

TEST(Parallel_Find_Minimum_In_Matrix, Rows_Greater_Columns) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> globalMatrix;
    const int numberOfRows = 15, numberOfColumns = 10;
    int parallelMinimum, singleMinimum;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixWithRandom(numberOfRows, numberOfColumns);

        singleMinimum = singleFindMinimum(globalMatrix);
    }

    parallelMinimum = parallelFindMinimum(globalMatrix);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleMinimum, parallelMinimum);
    }
}

TEST(Parallel_Find_Minimum_In_Matrix, Rows_Less_Columns) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> globalMatrix;
    const int numberOfRows = 10, numberOfColumns = 15;
    int parallelMinimum, singleMinimum;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixWithRandom(numberOfRows, numberOfColumns);

        singleMinimum = singleFindMinimum(globalMatrix);
    }

    parallelMinimum = parallelFindMinimum(globalMatrix);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleMinimum, parallelMinimum);
    }
}

TEST(Parallel_Find_Minimum_In_Matrix, Minimum_At_The_Beginning_Of_The_Matrix) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> globalMatrix;
    const int numberOfRows = 10, numberOfColumns = 10;
    int parallelMinimum, singleMinimum;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixWithRandom(numberOfRows, numberOfColumns);
        globalMatrix[0][0] = -10000000;

        singleMinimum = singleFindMinimum(globalMatrix);
    }

    parallelMinimum = parallelFindMinimum(globalMatrix);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleMinimum, parallelMinimum);
    }
}

TEST(Parallel_Find_Minimum_In_Matrix, Minimum_At_The_End_Of_The_Matrix) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<int>> globalMatrix;
    const int numberOfRows = 10, numberOfColumns = 10;
    int parallelMinimum, singleMinimum;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixWithRandom(numberOfRows, numberOfColumns);
        globalMatrix[numberOfRows - 1][numberOfColumns - 1] = -10000000;

        singleMinimum = singleFindMinimum(globalMatrix);
    }

    parallelMinimum = parallelFindMinimum(globalMatrix);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleMinimum, parallelMinimum);
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