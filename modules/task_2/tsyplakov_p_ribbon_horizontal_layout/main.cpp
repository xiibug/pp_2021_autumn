// Copyright 2021 Tsyplakov Pavel
#include <gtest/gtest.h>
#include <vector>
#include "./ribbon_horizontal_layout.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Multiolication) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> globalMatrix;
    const vector<int>::size_type numberOfRows = 100;
    const vector<int>::size_type numberOfCols = 100;
    vector<int> globalVector;
    const vector<int>::size_type sizeVector = 100;

    globalVector = getRandomVector(sizeVector);

    if (rank == 0) {
        globalMatrix = getRandomMatrix(numberOfRows * numberOfCols);
    }

    vector<int> globalMult = getParallelOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);

    if (rank == 0) {
        vector<int> referenceMult = getSequentialOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);
        ASSERT_EQ(globalMult, referenceMult);
    }
}

TEST(Parallel_Operations_MPI, Test_Multiolication_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> globalMatrix;
    const vector<int>::size_type numberOfRows = 200;
    const vector<int>::size_type numberOfCols = 200;
    vector<int> globalVector;
    const vector<int>::size_type sizeVector = 200;

    globalVector = getRandomVector(sizeVector);

    if (rank == 0) {
        globalMatrix = getRandomMatrix(numberOfRows * numberOfCols);
    }

    vector<int> globalMult = getParallelOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);

    if (rank == 0) {
        vector<int> referenceMult = getSequentialOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);
        ASSERT_EQ(globalMult, referenceMult);
    }
}

TEST(Parallel_Operations_MPI, Test_Multiolication_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> globalMatrix;
    const vector<int>::size_type numberOfRows = 300;
    const vector<int>::size_type numberOfCols = 300;
    vector<int> globalVector;
    const vector<int>::size_type sizeVector = 300;

    globalVector = getRandomVector(sizeVector);

    if (rank == 0) {
        globalMatrix = getRandomMatrix(numberOfRows * numberOfCols);
    }

    vector<int> globalMult = getParallelOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);

    if (rank == 0) {
        vector<int> referenceMult = getSequentialOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);
        ASSERT_EQ(globalMult, referenceMult);
    }
}

TEST(Parallel_Operations_MPI, Test_Multiolication_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> globalMatrix;
    const vector<int>::size_type numberOfRows = 200;
    const vector<int>::size_type numberOfCols = 300;
    vector<int> globalVector;
    const vector<int>::size_type sizeVector = 300;

    globalVector = getRandomVector(sizeVector);

    if (rank == 0) {
        globalMatrix = getRandomMatrix(numberOfRows * numberOfCols);
    }

    vector<int> globalMult = getParallelOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);

    if (rank == 0) {
        vector<int> referenceMult = getSequentialOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);
        ASSERT_EQ(globalMult, referenceMult);
    }
}

TEST(Parallel_Operations_MPI, Test_Multiolication_5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> globalMatrix;
    const vector<int>::size_type numberOfRows = 300;
    const vector<int>::size_type numberOfCols = 200;
    vector<int> globalVector;
    const vector<int>::size_type sizeVector = 200;

    globalVector = getRandomVector(sizeVector);

    if (rank == 0) {
        globalMatrix = getRandomMatrix(numberOfRows * numberOfCols);
    }

    vector<int> globalMult = getParallelOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);

    if (rank == 0) {
        vector<int> referenceMult = getSequentialOperations(globalMatrix, numberOfRows, numberOfCols, globalVector);
        ASSERT_EQ(globalMult, referenceMult);
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
