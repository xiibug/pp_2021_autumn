// Copyright 2021 Groshev Nickolay
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include "../../../modules/task_1/groshev_n_vec_close_values/vector_close_values.h"
#include <gtest-mpi-listener.hpp>



TEST(TEST_VECTOR_CLOSE_VALUES, TEST_SEQUENTAL_ALGORITHM) {
    int rank;
    std::vector<int> testVector = { 4, 5, 10, 12, 44 };
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int minDiff = getMinDiffByOneProc(testVector);
        ASSERT_EQ(minDiff, 1);
    }
}


TEST(TEST_VECTOR_CLOSE_VALUES, TEST_SEQUENTAL_ALGORITHM_ONE_ELEM) {
    int rank;
    std::vector<int> testVector = { 1 };
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int dif = getMinDiffByOneProc(testVector);
        ASSERT_EQ(dif, 0);
    }
}

TEST(TEST_VECTOR_CLOSE_VALUES, TEST_PARALLEL_WITH_ONE_ELEM) {
    int rank;
    std::vector<int> testVector = { 1 };
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int minDiff = getMinDiffParallel(testVector);
    if (rank == 0) {
        ASSERT_EQ(minDiff, 0);
    }
}

TEST(TEST_VECTOR_CLOSE_VALUES, TEST_PARALLEL_WITH_5RAND_ELEM) {
    int rank;
    std::vector<int> testVector;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    testVector = getRandomVector(5);
    int minDiff = getMinDiffParallel(testVector);
    if (rank == 0) {
        ASSERT_EQ(minDiff, getMinDiffByOneProc(testVector));
    }
}

TEST(TEST_VECTOR_CLOSE_VALUES, TEST_PARALLEL_WITH_5_ELEM) {
    int rank;
    std::vector<int> testVector;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    testVector = getRandomVector(5);
    int minDiff = getMinDiffParallel(testVector);
    if (rank == 0) {
        ASSERT_EQ(minDiff, getMinDiffByOneProc(testVector));
    }
}

TEST(TEST_VECTOR_CLOSE_VALUES, TEST_PARALLEL_WITH_10RAND_ELEM) {
    int rank;
    std::vector<int> testVector;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    testVector = getRandomVector(10);
    int minDiff = getMinDiffParallel(testVector);
    if (rank == 0) {
        ASSERT_EQ(minDiff, getMinDiffByOneProc(testVector));
    }
}

TEST(TEST_VECTOR_CLOSE_VALUES, TEST_PARALLEL_WITH_10_ELEM) {
    int rank;
    std::vector<int> testVector = {5, 10, 12, 15, 19, 99, 12, 55, 34 , 22 };
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int minDiff = getMinDiffParallel(testVector);
    if (rank == 0) {
        ASSERT_EQ(minDiff, getMinDiffByOneProc(testVector));
    }
}
TEST(TEST_VECTOR_CLOSE_VALUES, TEST_PARALLEL_WITH_50RAND_ELEM) {
    int rank;
    std::vector<int> testVector;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    testVector = getRandomVector(50);
    int minDiff = getMinDiffParallel(testVector);
    if (rank == 0) {
        ASSERT_EQ(minDiff, getMinDiffByOneProc(testVector));
    }
}
TEST(TEST_VECTOR_CLOSE_VALUES, TEST_PARALLEL_WITH_100RAND_ELEM) {
    int rank;
    std::vector<int> testVector;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    testVector = getRandomVector(50);
    int minDiff = getMinDiffParallel(testVector);
    if (rank == 0) {
        ASSERT_EQ(minDiff, getMinDiffByOneProc(testVector));
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
