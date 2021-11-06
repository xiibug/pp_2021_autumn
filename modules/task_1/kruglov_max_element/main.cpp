// Copyright 2021 Kruglov Aleksei
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./max_elem.h"
#include <gtest-mpi-listener.hpp>

TEST(Max_element_test, 1) {
    // test parameters
    std::size_t size = 100;

    int proc_rank;
    std::vector<int> vec;
    int reference_max, calculated_max;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    if (proc_rank == 0) {
        int max_possible = 200;
        vec = get_random_vector(size, max_possible);
        reference_max = *std::max_element(vec.begin(), vec.end());
    }
    calculated_max = get_max_element(vec, size);
    if (proc_rank == 0) {
        ASSERT_EQ(reference_max, calculated_max);
    }
}

TEST(Max_element_test, 2) {
    // test parameters
    std::size_t size = 50;

    int proc_rank;
    std::vector<int> vec;
    int reference_max, calculated_max;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    if (proc_rank == 0) {
        int max_possible = 200;
        vec = get_random_vector(size, max_possible);
        reference_max = *std::max_element(vec.begin(), vec.end());
    }
    calculated_max = get_max_element(vec, size);
    if (proc_rank == 0) {
        ASSERT_EQ(reference_max, calculated_max);
    }
}

TEST(Max_element_test, 3) {
    // test parameters
    std::size_t size = 200;

    int proc_rank;
    std::vector<int> vec;
    int reference_max, calculated_max;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    if (proc_rank == 0) {
        int max_possible = 1000;
        vec = get_random_vector(size, max_possible);
        reference_max = *std::max_element(vec.begin(), vec.end());
    }
    calculated_max = get_max_element(vec, size);
    if (proc_rank == 0) {
        ASSERT_EQ(reference_max, calculated_max);
    }
}

TEST(Max_element_test, 4) {
    // test parameters
    std::size_t size = 200;

    int proc_rank;
    std::vector<int> vec;
    int reference_max, calculated_max;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    if (proc_rank == 0) {
        int max_possible = 150000;
        vec = get_random_vector(size, max_possible);
        reference_max = *std::max_element(vec.begin(), vec.end());
    }
    calculated_max = get_max_element(vec, size);
    if (proc_rank == 0) {
        ASSERT_EQ(reference_max, calculated_max);
    }
}

TEST(Max_element_test, 5) {
    // test parameters
    std::size_t size = 100000;

    int proc_rank;
    std::vector<int> vec;
    int reference_max, calculated_max;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    if (proc_rank == 0) {
        int max_possible = 150000;
        vec = get_random_vector(size, max_possible);
        reference_max = *std::max_element(vec.begin(), vec.end());
    }
    calculated_max = get_max_element(vec, size);
    if (proc_rank == 0) {
        ASSERT_EQ(reference_max, calculated_max);
    }
}

TEST(Max_element_test, 6) {
    // test parameters
    std::size_t size = 5;

    int proc_rank;
    std::vector<int> vec;
    int reference_max, calculated_max;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    if (proc_rank == 0) {
        int max_possible = 100;
        vec = get_random_vector(size, max_possible);
        reference_max = *std::max_element(vec.begin(), vec.end());
    }
    calculated_max = get_max_element(vec, size);
    if (proc_rank == 0) {
        ASSERT_EQ(reference_max, calculated_max);
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
