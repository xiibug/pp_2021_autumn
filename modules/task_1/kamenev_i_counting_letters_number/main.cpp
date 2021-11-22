// Copyright 2021 Kamenev Ilya

#include <gtest/gtest.h>
#include "counting_letters_number.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Empty_Random_Str) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str;
    const int str_size = 0;
    str = CreateRandomStr(str_size);
    int par_result = CountingLettersParallel(str);
    if (rank == 0) {
        int expected_result = 0;
        ASSERT_EQ(expected_result, par_result);
    }
}

TEST(Parallel_Operations_MPI, Test_Only_Letters_100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str;
    const int str_size = 100;
    str = CreateOnlyLettersStr(str_size);
    int par_result = CountingLettersParallel(str);
    if (rank == 0) {
        int expected_result = 100;
        ASSERT_EQ(expected_result, par_result);
    }
}

TEST(Parallel_Operations_MPI, Test_100_Letters_Str) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str;
    str = CreateOnlyLettersStr(20);
    int par_result = CountingLettersParallel(str);
    if (rank == 0) {
        int expected_result = 20;
        ASSERT_EQ(expected_result, par_result);
    }
}

TEST(Parallel_Operations_MPI, Test_Empty_Str_Parallel_Equals_Sequential) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str;
    const int str_size = 0;
    str = CreateOnlyLettersStr(str_size);
    int par_result, seq_result;
    par_result = CountingLettersParallel(str);
    seq_result = CountingLettersSequential(str);
    if (rank == 0) {
        ASSERT_EQ(seq_result, par_result);
    }
}

TEST(Parallel_Operations_MPI, Test_No_Letters_Str) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str;
    str = "$%##4235!8*15%79)-7$}=";
    int result;
    result = CountingLettersParallel(str);
    if (rank == 0) {
        int expected_result = 0;
        ASSERT_EQ(expected_result, result);
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