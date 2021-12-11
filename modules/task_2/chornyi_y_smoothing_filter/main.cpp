// Copyright 2021 Chornyi Yurii
#include <gtest/gtest.h>
#include <vector>
#include "./smoothing_filter.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Smoothing_Filter, Width_Equal_Height_And_Radius_1) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<float>> globalMatrix;
    const int matrixWidth = 100, matrixHeight = 100;
    std::vector<std::vector<float>> parallelSmoothing, singleSmoothing;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixOfColor(matrixWidth, matrixHeight);

        singleSmoothing = singleSmoothingImage(globalMatrix, 1);
    }

    parallelSmoothing = parallelSmoothingImage(globalMatrix, 1);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleSmoothing, parallelSmoothing);
    }
}

TEST(Parallel_Smoothing_Filter, Width_Greater_Height_And_Radius_1) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<float>> globalMatrix;
    const int matrixWidth = 150, matrixHeight = 100;
    std::vector<std::vector<float>> parallelSmoothing, singleSmoothing;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixOfColor(matrixWidth, matrixHeight);

        singleSmoothing = singleSmoothingImage(globalMatrix, 1);
    }

    parallelSmoothing = parallelSmoothingImage(globalMatrix, 1);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleSmoothing, parallelSmoothing);
    }
}

TEST(Parallel_Smoothing_Filter, Width_Less_Height_And_Radius_1) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<float>> globalMatrix;
    const int matrixWidth = 100, matrixHeight = 150;
    std::vector<std::vector<float>> parallelSmoothing, singleSmoothing;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixOfColor(matrixWidth, matrixHeight);

        singleSmoothing = singleSmoothingImage(globalMatrix, 1);
    }

    parallelSmoothing = parallelSmoothingImage(globalMatrix, 1);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleSmoothing, parallelSmoothing);
    }
}

TEST(Parallel_Smoothing_Filter, Width_Greater_Height_And_Radius_5) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<float>> globalMatrix;
    const int matrixWidth = 350, matrixHeight = 300;
    std::vector<std::vector<float>> parallelSmoothing, singleSmoothing;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixOfColor(matrixWidth, matrixHeight);

        singleSmoothing = singleSmoothingImage(globalMatrix, 5);
    }

    parallelSmoothing = parallelSmoothingImage(globalMatrix, 5);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleSmoothing, parallelSmoothing);
    }
}

TEST(Parallel_Smoothing_Filter, Width_Less_Height_And_Radius_5) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    std::vector<std::vector<float>> globalMatrix;
    const int matrixWidth = 300, matrixHeight = 350;
    std::vector<std::vector<float>> parallelSmoothing, singleSmoothing;

    // Act
    if (currentRank == 0) {
        globalMatrix = fillMatrixOfColor(matrixWidth, matrixHeight);

        singleSmoothing = singleSmoothingImage(globalMatrix, 5);
    }

    parallelSmoothing = parallelSmoothingImage(globalMatrix, 5);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(singleSmoothing, parallelSmoothing);
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
