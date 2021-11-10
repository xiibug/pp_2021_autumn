// Copyright 2021 Olynin Alexandr
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "./count_words_in_a_line.h"

TEST(Sequantial_Tests, Sequantial_count_of_words_in_a_line_test_key_0)
{
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    char* my_text = const_cast<char*>(GetReadyText(0));

    int expected_count = 130;
    if (ProcRank == 0)
    {
        int actual_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Sequantial_Tests, Sequantial_count_of_words_in_a_line_test_key_1)
{
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    char* my_text = const_cast<char*>(GetReadyText(1));

    int expected_count = 114;
    if (ProcRank == 0)
    {
        int actual_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Parallel_Tests, Parallel_count_of_words_in_a_line_test_key_0)
{
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    char* my_text = nullptr;
    if (ProcRank == 0)
        my_text = const_cast<char*>(GetReadyText(0));

    int expected_count = ParallelCountWordsInALine(my_text);
    if (ProcRank == 0)
    {
        int actual_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Parallel_Tests, Parallel_count_of_words_in_a_line_test_key_1)
{
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    char* my_text = nullptr;
    if (ProcRank == 0)
        my_text = const_cast<char*>(GetReadyText(1));

    int expected_count = ParallelCountWordsInALine(my_text);
    if (ProcRank == 0)
    {
        int actual_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

TEST(Parallel_Tests, Parallel_count_of_words_in_a_line_test_key_0_and_1)
{
    int ProcRank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    char* my_text = nullptr;
    if (ProcRank == 0)
    {
        char tmp[10000];
        const char* part_1 = GetReadyText(0);
        const char* part_2 = GetReadyText(1);
        strcpy_s(tmp, 10000, part_1);
        strcat_s(tmp, 10000, "\n");
        strcat_s(tmp, 10000, part_2);
        my_text = new char[strlen(tmp) + 1];
        strcpy_s(my_text, strlen(tmp) + 1, tmp);
    }
    
    int expected_count = ParallelCountWordsInALine(my_text);
    if (ProcRank == 0)
    {
        int actual_count = SequentialCountWordsInALine(my_text);
        ASSERT_EQ(expected_count, actual_count);
    }
}

int main(int argc, char** argv)
{
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