// Copyright 2021 Kozel Svetlana
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/kozel_s_vector_differ_elements_value/vector_differ_elements_value.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, DEFAULT_FIND_DIFFER_ELEMENT_VALUES_VECTOR_SIZE_5_GET_VAL) {
    int commRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    std::vector<int> vector = { 0, 1, 5, 4, 5 };
    if (commRank == 0) {
        int max = differElementsValue(vector);
        ASSERT_EQ(max, 4);
    }
}

TEST(Parallel_Operations_MPI, PARALLEL_FIND_DIFFER_ELEMENT_VALUES_VECTOR_SIZE_500_GET_VAL) {
    int commRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    std::vector<int> vector = fillVector(500);
    int max1;
    if (commRank == 0) {
        max1 = differElementsValue(vector);
    }
    int max2 = paralleldifferElementsValue(vector, vector.size());
    if (commRank == 0) {
        ASSERT_EQ(max1, max2);
    }
}

TEST(Parallel_Operations_MPI, PARALLEL_FIND_DIFFER_ELEMENT_VALUES_EQUAL_ELEMENTS_IN_VECTOR_GET_VAL) {
    int commRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    std::vector<int> vector = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    int max1;
    if (commRank == 0) {
        max1 = differElementsValue(vector);
    }
    int max2 = paralleldifferElementsValue(vector, vector.size());
    if (commRank == 0) {
        ASSERT_EQ(max1, max2);
    }
}

TEST(Parallel_Operations_MPI, PARALLEL_FIND_DIFFER_ELEMENT_VALUES_VECTOR_ERROR_SIZE_0_GET_VAL) {
    int commRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    std::vector<int> vector = fillVector(0);
    int max1;
    if (commRank == 0) {
        max1 = differElementsValue(vector);
    }
    int max2 = paralleldifferElementsValue(vector, vector.size());
    if (commRank == 0) {
        ASSERT_EQ(max1, max2);
    }
}

TEST(Parallel_Operations_MPI, PARALLEL_FIND_DIFFER_ELEMENT_VALUES_VECTOR_LARGE_SIZE_100000_GET_VAL) {
    int commRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    std::vector<int> vector = fillVector(100000);
    int max1;
    if (commRank == 0) {
        max1 = differElementsValue(vector);
    }
    int max2 = paralleldifferElementsValue(vector, vector.size());
    if (commRank == 0) {
        ASSERT_EQ(max1, max2);
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
