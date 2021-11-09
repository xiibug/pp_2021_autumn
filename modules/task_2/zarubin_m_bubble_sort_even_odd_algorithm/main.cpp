// Copyright 2021 Zarubin Mikhail
#include <gtest/gtest.h>
#include <vector>
#include "./bubble_sort_even_odd_algorithm.h"
#include <gtest-mpi-listener.hpp>


TEST(GENERATE_VECTOR, can_generate_random_vector) {
    std::vector<int> vector(5);
    ASSERT_NO_THROW(generateRandomVector(&vector, 5));
}

TEST(SEQUENTIAL_OPERATIONS, can_run_sequential_operations) {
    std::vector<int> vector(5);
    generateRandomVector(&vector, 5);
    ASSERT_NO_THROW(getSequentialOperations(vector, 5));
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_on_vector_even_size) {
    std::vector<int> vector{ 3, 2, 5, 0, 4, 2 };
    std::vector<int> expected_result{ 0, 2, 2, 3, 4, 5 };
    std::vector<int> result = getSequentialOperations(vector, 6);
    ASSERT_EQ(result, expected_result);
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_on_vector_odd_size) {
    std::vector<int> vector{ 3, 2, 5, 0, 4 };
    std::vector<int> expected_result{ 0, 2, 3, 4, 5 };
    std::vector<int> result = getSequentialOperations(vector, 5);
    ASSERT_EQ(result, expected_result);
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
