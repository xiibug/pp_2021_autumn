// Copyright 2021 Chornyi Yurii
#include <gtest/gtest.h>
#include <vector>
#include "./radix_sort_with_simple_merge.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Redix_Sort, Size_Vector_100) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    vector<int> globalVector;
    const v_size_t vectorSize = 100;
    vector<int> parallelSortedVector, sequentialSortedVector;

    // Act
    if (currentRank == 0) {
        generateRandomVector(&globalVector, vectorSize);
        sequentialSortedVector = globalVector;
        sequentialRadixSort(&sequentialSortedVector);
    }

    parallelSortedVector = parallelRadixSort(globalVector, vectorSize);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(parallelSortedVector, sequentialSortedVector);
    }
}

TEST(Parallel_Redix_Sort, Size_Vector_200) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    vector<int> globalVector;
    const v_size_t vectorSize = 200;
    vector<int> parallelSortedVector, sequentialSortedVector;

    // Act
    if (currentRank == 0) {
        generateRandomVector(&globalVector, vectorSize);
        sequentialSortedVector = globalVector;
        sequentialRadixSort(&sequentialSortedVector);
    }

    parallelSortedVector = parallelRadixSort(globalVector, vectorSize);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(parallelSortedVector, sequentialSortedVector);
    }
}

TEST(Parallel_Redix_Sort, Size_Vector_300) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    vector<int> globalVector;
    const v_size_t vectorSize = 300;
    vector<int> parallelSortedVector, sequentialSortedVector;

    // Act
    if (currentRank == 0) {
        generateRandomVector(&globalVector, vectorSize);
        sequentialSortedVector = globalVector;
        sequentialRadixSort(&sequentialSortedVector);
    }

    parallelSortedVector = parallelRadixSort(globalVector, vectorSize);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(parallelSortedVector, sequentialSortedVector);
    }
}

TEST(Parallel_Redix_Sort, Size_Vector_400) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    vector<int> globalVector;
    const v_size_t vectorSize = 400;
    vector<int> parallelSortedVector, sequentialSortedVector;

    // Act
    if (currentRank == 0) {
        generateRandomVector(&globalVector, vectorSize);
        sequentialSortedVector = globalVector;
        sequentialRadixSort(&sequentialSortedVector);
    }

    parallelSortedVector = parallelRadixSort(globalVector, vectorSize);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(parallelSortedVector, sequentialSortedVector);
    }
}

TEST(Parallel_Redix_Sort, Size_Vector_500) {
    // Arrange
    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    vector<int> globalVector;
    const v_size_t vectorSize = 500;
    vector<int> parallelSortedVector, sequentialSortedVector;

    // Act
    if (currentRank == 0) {
        generateRandomVector(&globalVector, vectorSize);
        sequentialSortedVector = globalVector;
        sequentialRadixSort(&sequentialSortedVector);
    }

    parallelSortedVector = parallelRadixSort(globalVector, vectorSize);

    // Assert
    if (currentRank == 0) {
        ASSERT_EQ(parallelSortedVector, sequentialSortedVector);
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
