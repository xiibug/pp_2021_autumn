// Copyright 2021 Brazhnik Dmitry
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/brazhnik_d_vector_find_min/find_min_element_vector.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, TEST_FIND_MIN_VAL_IN_VECTOR) {
    int commRank;
    std::vector<int> vector;

    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);

    if (commRank == 0) {
        vector = fillRandomValToVector(100);
    }

    int minFirst = defaultFindingMinVal(vector);

    if (commRank == 0) {
        int minSecond = defaultFindingMinVal(vector);
        ASSERT_EQ(minFirst, minSecond);
    }
}

TEST(Parallel_Operations_MPI, TEST_PARALLEL_FIND_MIN_VAL_IN_VECTOR_GET_VAL) {
    int commRank;
    std::vector<int> vector;
    int minFirst, minSecond;

    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    if (commRank == 0) {
        vector = fillRandomValToVector(100);
        minFirst = defaultFindingMinVal(vector);
    }
    minSecond = parallelFindingMinVal(vector, 100);
    if (commRank == 0) {
        ASSERT_EQ(minFirst, minSecond);
    }
}

TEST(Parallel_Operations_MPI, TEST_PUT_NEGATIVE_SIZE_VALUE_TO_FUNCTION_FILL_VECTOR) {
    int commRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);

    ASSERT_ANY_THROW(fillRandomValToVector(-15));
}

TEST(Parallel_Operations_MPI, TEST_SIZE_VECTOR_LARGE_VALUE_TO_FUNCTION_PARALLEL_FIND_GET_MIN_VAL) {
    int commRank;
    std::vector<int> vector;
    int minFirst, minSecond;

    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    if (commRank == 0) {
        vector = fillRandomValToVector(20000000);
        minFirst = defaultFindingMinVal(vector);
    }
    minSecond = parallelFindingMinVal(vector, 20000000);
    if (commRank == 0) {
        ASSERT_EQ(minFirst, minSecond);
    }
}

TEST(Parallel_Operations_MPI, TEST_PUT_VECTOR_HAS_FEWER_ELEMENTS_THAN_CPU_CORES_GET_MIN_VAL) {
    int commRank;
    std::vector<int> vector;
    int minFirst, minSecond;

    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    if (commRank == 0) {
        vector = fillRandomValToVector(4);
        minFirst = defaultFindingMinVal(vector);
    }
    minSecond = parallelFindingMinVal(vector, 4);
    if (commRank == 0) {
        ASSERT_EQ(minFirst, minSecond);
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
