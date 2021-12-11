// Copyright 2021 Chelebaev Artem
#include <gtest/gtest.h>
#include <mpi.h>
#include <vector>
#include "./symbol_frequency.h"
#include <gtest-mpi-listener.hpp>


//----------------------------------------------------

TEST(Parallel_Operations_MPI, parallel_test) {
    std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    char symbol = 'l';
    double freq = parFrequency(&symbol, text);
    if (my_rank == 0) {
        ASSERT_EQ((int)freq, 4);
    }
}

TEST(Parallel_Operations_MPI, sequential_test) {
    std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    char symbol = 'l';
    double freq = seqFrequency(&symbol, text);
    if (my_rank == 0) {
        ASSERT_EQ((int)freq, 4);
    }
}

TEST(Parallel_Operations_MPI, par_seq_test) {
    std::string text = "lorem ipsum dolor sit amet, consectetur adipiscing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    char symbol = 'l';
    double freq1 = parFrequency(&symbol, text);
    if (my_rank == 0) {
        double freq2 = seqFrequency(&symbol, text);
        ASSERT_EQ((int)freq1, (int)freq2);
    }
}

TEST(Parallel_Operations_MPI, lowercase_test) {
    std::string text = "lorem ipsum dolor sit amet, consectetur adipiscing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    char symbol = 'l';
    double freq = parFrequency(&symbol, text);
    if (my_rank == 0) {
        ASSERT_EQ((int)freq, 4);
    }
}

TEST(Parallel_Operations_MPI, uppercase_test) {
    std::string text = "LOREM IPSUM DOLOR SIT AMET, CONSECTETUR ADIPISCING ELIT, "
        "SED DO EIUSMOD TEMPOR INCIDIDUNT UT LABORE ET DOLORE MAGNA ALIQUA.";
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    char symbol = 'l';
    double freq = parFrequency(&symbol, text);
    if (my_rank == 0) {
        ASSERT_EQ((int)freq, 4);
    }
}

TEST(Parallel_Operations_MPI, lower_upper_text) {
    std::string text1 = "LOREM IPSUM DOLOR SIT AMET, CONSECTETUR ADIPISCING ELIT, "
        "SED DO EIUSMOD TEMPOR INCIDIDUNT UT LABORE ET DOLORE MAGNA ALIQUA.",
                text2 = "lorem ipsum dolor sit amet, consectetur adipiscing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    char symbol = 'l';
    double freq1 = parFrequency(&symbol, text1),
        freq2 = parFrequency(&symbol, text2);
    if (my_rank == 0) {
        ASSERT_EQ((int)freq1, (int)freq2);
    }
}

//----------------------------------------------------

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
