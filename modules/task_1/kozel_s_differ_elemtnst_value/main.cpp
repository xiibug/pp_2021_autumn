// Copyright 2021 Kozel Svetlana
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/kozel_s_differ_elemtnst_value/differ_elemtnst_value.h"
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

TEST(Parallel_Operations_MPI, PARALLEL_FIND_DIFFER_ELEMENT_VALUES_VECTOR_MIN_SIZE_3_GET_VAL) {
    int commRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    std::vector<int> vector = fillVector(3);
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

//TEST(Parallel_Operations_MPI, TEST_PARALLEL_FIND_MIN_VAL_IN_VECTOR_GET_VAL) {
//    int commRank;
//    std::vector<int> vector;
//    int minFirst, minSecond;
//
//    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
//    if (commRank == 0) {
//        vector = fillRandomValToVector(100);
//        minFirst = defaultFindingMinVal(vector);
//    }
//    minSecond = parallelFindingMinVal(vector, 100);
//    if (commRank == 0) {
//        ASSERT_EQ(minFirst, minSecond);
//    }
//}
//
//TEST(Parallel_Operations_MPI, TEST_PUT_NEGATIVE_SIZE_VALUE_TO_FUNCTION_FILL_VECTOR) {
//    int commRank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
//
//    ASSERT_ANY_THROW(fillRandomValToVector(-15));
//}
//
//TEST(Parallel_Operations_MPI, TEST_PUT_NEGATIVE_SIZE_VALUE_TO_FUNCTION_PARALLEL_FIND_VAL) {
//    int commRank;
//    std::vector<int> vector = fillRandomValToVector(50);
//
//    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
//    if (commRank == 0) {
//        ASSERT_ANY_THROW(parallelFindingMinVal(vector, -15));
//    }
//}
//
//TEST(Parallel_Operations_MPI, TEST_PUT_VECTOR_HAS_FEWER_ELEMENTS_THAN_CPU_CORES_GET_MIN_VAL) {
//    int commRank;
//    std::vector<int> vector;
//    int minFirst, minSecond;
//
//    MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
//    if (commRank == 0) {
//        vector = fillRandomValToVector(4);
//        minFirst = defaultFindingMinVal(vector);
//    }
//    minSecond = parallelFindingMinVal(vector, 4);
//    if (commRank == 0) {
//        ASSERT_EQ(minFirst, minSecond);
//    }
//}


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
