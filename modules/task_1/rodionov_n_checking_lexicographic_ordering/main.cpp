// Copyright 2021 TexHik620953
#include <mpi.h>
#include <gtest/gtest.h>
#include <vector>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_1/rodionov_n_checking_lexicographic_ordering/lex_ordering.h"

int length = 5000;

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


TEST(MPILexicalOrdering, IdenticalTest) {
    int procRank = 0;
    char* string1 = get_random_string(length);
    char* string2 = new char[length + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        memcpy(string2, string1, sizeof(char) * (length + 1));
    }
    int result = omp_lex_compare(string1, string2, length);
    if (procRank == 0) {
        EXPECT_EQ(result, 0);
        delete[] string1;
        delete[] string2;
    }
}


TEST(MPILexicalOrdering, GreaterInconsistencyInStart) {
    int procRank = 0;
    char* string1 = get_random_string(length);
    char* string2 = new char[length + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        memcpy(string2, string1, sizeof(char) * (length + 1));
        string1[0] = 'A';
        string2[0] = 'B';
    }
    int result = omp_lex_compare(string1, string2, length);
    if (procRank == 0) {
        EXPECT_EQ(result, 1);
        delete[] string1;
        delete[] string2;
    }
}

TEST(MPILexicalOrdering, GreaterInconsistencyInEnd) {
    int procRank = 0;
    char* string1 = get_random_string(length);
    char* string2 = new char[length + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        memcpy(string2, string1, sizeof(char) * (length + 1));
        string1[length - 2] = 'A';
        string2[length - 2] = 'B';
    }
    int result = omp_lex_compare(string1, string2, length);
    if (procRank == 0) {
        EXPECT_EQ(result, 1);
        delete[] string1;
        delete[] string2;
    }
}

TEST(MPILexicalOrdering, LowerInconsistencyInStart) {
    int procRank = 0;
    char* string1 = get_random_string(length);
    char* string2 = new char[length + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        memcpy(string2, string1, sizeof(char) * (length + 1));
        string1[0] = 'B';
        string2[0] = 'A';
    }
    int result = omp_lex_compare(string1, string2, length);
    if (procRank == 0) {
        EXPECT_EQ(result, -1);
        delete[] string1;
        delete[] string2;
    }
}

TEST(MPILexicalOrdering, LowerInconsistencyInEnd) {
    int procRank = 0;
    char* string1 = get_random_string(length);
    char* string2 = new char[length + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        memcpy(string2, string1, sizeof(char) * (length + 1));
        string1[length - 2] = 'B';
        string2[length - 2] = 'A';
    }
    int result = omp_lex_compare(string1, string2, length);
    if (procRank == 0) {
        EXPECT_EQ(result, -1);
        delete[] string1;
        delete[] string2;
    }
}
