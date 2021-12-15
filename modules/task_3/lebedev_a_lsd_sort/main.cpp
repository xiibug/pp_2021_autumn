// Copyright 2021 Lebedev Alexey
#include <gtest/gtest.h>
#include <random>
#include "./lsd_sort.h"
#include <gtest-mpi-listener.hpp>


bool is_sorted(const std::vector<int>& v) {
    bool sorted = true;
    for (size_t i = 0; i < v.size() - 1; i++) {
        if (v[i] > v[i + 1]) {
            return false;
        }
    }
    return sorted;
}

std::vector<int> get_random_vector(size_t size, int low, int high) {
    std::vector<int> random_vector(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(low, high);
    for (size_t i = 0; i < size; i++) {
        random_vector[i] = distrib(gen);
    }
    return random_vector;
}


TEST(LSD_SORT_MPI, TEST_SORT_SEQENTUAL) {
    std::vector<int> v = get_random_vector(10000, -10000, 10000);
    lsd_sort(v);
    ASSERT_TRUE(is_sorted(v));
}


TEST(LSD_SORT_MPI, Test_2) {
}


TEST(LSD_SORT_MPI, Test_3) {
}


TEST(LSD_SORT_MPI, Test_4) {
}


TEST(LSD_SORT_MPI, Test_5) {
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
