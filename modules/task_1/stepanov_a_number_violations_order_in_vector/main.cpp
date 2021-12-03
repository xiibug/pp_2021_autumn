// Copyright 2021 Stepanov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./number_violations_order_in_vector.h"
#include <gtest-mpi-listener.hpp>


TEST(GENERATE_MATRIX, can_generate_random_vector) {
    std::vector<int> vector(10);
    ASSERT_NO_THROW(generateRandomVector(&vector));
}

TEST(SEQUENTIAL_OPERATIONS, can_run_sequential_operations) {
    std::vector<int> vector(5);
    generateRandomVector(&vector);
    ASSERT_NO_THROW(getSequentialOperations(vector));
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_on_ordered_vector) {
    std::vector<int> vector{ 0, 1, 3, 9, 10 };
    int expected_result = 0;
    int result = getSequentialOperations(vector);
    ASSERT_EQ(result, expected_result);
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_on_not_ordered_vector) {
    std::vector<int> vector{ 0, 10, 2, 9, 3 };
    int expected_result = 2;
    int result = getSequentialOperations(vector);
    ASSERT_EQ(result, expected_result);
}

TEST(PARALLEL_OPERATIONS, can_run_parallel_operations) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type vector_size = 100;
    std::vector<int> vector(vector_size);

    if (rank == 0) {
        generateRandomVector(&vector);
    }

    ASSERT_NO_THROW(getParallelOperations(vector, vector_size));
}

TEST(PARALLEL_OPERATIONS, correct_work_on_ordered_vector) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int> vector = { 1, 2, 3, 4, 5 };

    if (rank == 0) {
        generateRandomVector(&vector);
    }

    int result = getParallelOperations(vector, 5);

    if (rank == 0) {
        int expected_result = getSequentialOperations(vector);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_not_ordered_vector) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int> vector = { 1, 10, 2, 4, 1 };

    if (rank == 0) {
        generateRandomVector(&vector);
    }

    int result = getParallelOperations(vector, 5);

    if (rank == 0) {
        int expected_result = getSequentialOperations(vector);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_random_vector_v1) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type global_size = 100;
    std::vector<int> vector(global_size);

    if (rank == 0) {
        generateRandomVector(&vector);
    }

    int result = getParallelOperations(vector, global_size);

    if (rank == 0) {
        int expected_result = getSequentialOperations(vector);
        ASSERT_EQ(result, expected_result);
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_on_random_vector_v2) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<int>::size_type global_size = 71;
    std::vector<int> vector(global_size);

    if (rank == 0) {
        generateRandomVector(&vector);
    }

    int result = getParallelOperations(vector, global_size);

    if (rank == 0) {
        int expected_result = getSequentialOperations(vector);
        ASSERT_EQ(result, expected_result);
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
