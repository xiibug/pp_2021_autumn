// Copyright 2021 Kolosova Alena
#include <gtest/gtest.h>
#include "./compare_string.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, seq_string_comparison_test_1) {
    int rank;
    for (char i = 0; i < CHAR_MAX; i++) std::cerr << i << std::endl;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char str1[] = "aaaaaaaaaaaa";
    char str2[] = "aaaaaaaaaaaa";

    if (rank == 0) {
        std::cerr << "[          ] str1 = " << str1 << std::endl;
        std::cerr << "[          ] str2 = " << str2 << std::endl;

        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, 0);
    }
}

TEST(Parallel_Operations_MPI, seq_string_comparison_test_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char str1[] = "aaaaaaaaaaaa";
    char str2[] = "b";

    if (rank == 0) {
        std::cerr << "[          ] str1 = " << str1 << std::endl;
        std::cerr << "[          ] str2 = " << str2 << std::endl;

        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, -1);
    }
}

TEST(Parallel_Operations_MPI, seq_string_comparison_test_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char str1[] = "bbb";
    char str2[] = "aaaaaaaaaaaa";

    if (rank == 0) {
        std::cerr << "[          ] str1 = " << str1 << std::endl;
        std::cerr << "[          ] str2 = " << str2 << std::endl;

        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, 1);
    }
}

TEST(Parallel_Operations_MPI, parallel_small_string_comparison_same_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char* str1, * str2;
    const int size_string = 10;

    if (rank == 0) {
        str1 = generateString(size_string);
        str2 = generateString(size_string);

        std::cerr << "[          ] str1 = " << str1 << std::endl;
        std::cerr << "[          ] str2 = " << str2 << std::endl;

        int glob_res = parCompareString(str1, str2);
        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, glob_res);
    }
}

TEST(Parallel_Operations_MPI, parallel_medium_string_comparison_same_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char* str1, * str2;
    const int size_string = 100;

    if (rank == 0) {
        str1 = generateString(size_string);
        str2 = generateString(size_string);

        std::cerr << "[          ] str1 = " << str1 << std::endl;
        std::cerr << "[          ] str2 = " << str2 << std::endl;

        int glob_res = parCompareString(str1, str2);
        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, glob_res);
    }
}

TEST(Parallel_Operations_MPI, parallel_large_string_comparison_same_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char* str1, * str2;
    const int size_string = 10000;

    if (rank == 0) {
        str1 = generateString(size_string);
        str2 = generateString(size_string);

        int glob_res = parCompareString(str1, str2);
        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, glob_res);
    }
}

TEST(Parallel_Operations_MPI, parallel_medium_string_comparison_diff_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char* str1, * str2;
    const int size_string = 100;

    if (rank == 0) {
        str1 = generateString(size_string, size_string / 10);
        str2 = generateString(size_string, size_string / 10);

        std::cerr << "[          ] str1 = " << str1 << std::endl;
        std::cerr << "[          ] str2 = " << str2 << std::endl;

        int glob_res = parCompareString(str1, str2);
        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, glob_res);
    }
}

TEST(Parallel_Operations_MPI, parallel_large_string_comparison_diff_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char* str1, * str2;
    const int size_string = 10000;

    if (rank == 0) {
        str1 = generateString(size_string, size_string / 10);
        str2 = generateString(size_string, size_string / 10);

        int glob_res = parCompareString(str1, str2);
        int ref_res = seqCompareString(str1, str2);
        ASSERT_EQ(ref_res, glob_res);
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
