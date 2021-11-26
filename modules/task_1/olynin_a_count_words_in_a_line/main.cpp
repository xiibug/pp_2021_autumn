// Copyright 2021 Olynin Alexandr
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "./count_words_in_a_line.h"

TEST(Sequantial_Tests, Sequantial_count_of_words_in_a_line_test_line_one) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        std::string my_text;
        my_text = GetReadyText(0);
        int expected_count = 11;
        int actual_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Sequantial_Tests, Sequantial_count_of_words_in_a_line_test_line_two) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        std::string my_text;
        my_text = GetReadyText(1);
        int expected_count = 13;
        int actual_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Parallel_Tests, Parallel_count_of_words_in_a_line_test_line_one) {
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    std::string my_text;
    if (ProcRank == 0)
        my_text = GetReadyText(0);

    int actual_count = ParallelCountWordsInALine(my_text);
    if (ProcRank == 0) {
        int expected_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Parallel_Tests, Parallel_count_of_words_in_a_line_test_line_two) {
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    std::string my_text;
    if (ProcRank == 0) {
        my_text = GetReadyText(1);
    }

    int actual_count = ParallelCountWordsInALine(my_text);
    if (ProcRank == 0) {
        int expected_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Parallel_Tests, Parallel_count_of_words_in_a_line_test_line_one_and_two) {
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    std::string my_text;
    if (ProcRank == 0) {
        my_text = GetReadyText(0) + " " + GetReadyText(1);
    }

    int actual_count = ParallelCountWordsInALine(my_text);
    if (ProcRank == 0) {
        int expected_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
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
