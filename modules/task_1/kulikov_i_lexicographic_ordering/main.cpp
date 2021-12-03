// Copyright 2021 Kulikov Ilya
#include <mpi.h>
#include <gtest/gtest.h>
#include <vector>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_1/kulikov_i_lexicographic_ordering/lexicographic_ordering.h"

int sz = 1000;

TEST(MPILexicalOrdering, IdenticalTest) {
    int rank = 0;
    char* string1 = get_random_str(sz);
    char* string2 = new char[sz + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        memcpy(string2, string1, sizeof(char) * (sz + 1));
    }
    int result = global_finding(string1, string2, sz);
    if (rank == 0) {
        EXPECT_EQ(result, 0);
        delete[] string1;
        delete[] string2;
    }
}


TEST(MPILexicalOrdering, FirstMoreInStart) {
    int rank = 0;
    char* string1 = get_random_str(sz);
    char* string2 = new char[sz + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        memcpy(string2, string1, sizeof(char) * (sz + 1));
        string1[5] = 'B';
        string2[5] = 'A';
    }
    int result = global_finding(string1, string2, sz);
    if (rank == 0) {
        EXPECT_EQ(result, 1);
        delete[] string1;
        delete[] string2;
    }
}

TEST(MPILexicalOrdering, FirstMoreInEnd) {
    int rank = 0;
    char* string1 = get_random_str(sz);
    char* string2 = new char[sz + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        memcpy(string2, string1, sizeof(char) * (sz + 1));
        string1[sz - 5] = 'B';
        string2[sz - 5] = 'A';
    }
    int result = global_finding(string1, string2, sz);
    if (rank == 0) {
        EXPECT_EQ(result, 1);
        delete[] string1;
        delete[] string2;
    }
}

TEST(MPILexicalOrdering, SecondMoreInStart) {
    int rank = 0;
    char* string1 = get_random_str(sz);
    char* string2 = new char[sz + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        memcpy(string2, string1, sizeof(char) * (sz + 1));
        string1[5] = 'A';
        string2[5] = 'B';
    }
    int result = global_finding(string1, string2, sz);
    if (rank == 0) {
        EXPECT_EQ(result, -1);
        delete[] string1;
        delete[] string2;
    }
}

TEST(MPILexicalOrdering, SecondMoreInEnd) {
    int rank = 0;
    char* string1 = get_random_str(sz);
    char* string2 = new char[sz + 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        memcpy(string2, string1, sizeof(char) * (sz + 1));
        string1[sz - 5] = 'A';
        string2[sz - 5] = 'B';
    }
    int result = global_finding(string1, string2, sz);
    if (rank == 0) {
        EXPECT_EQ(result, -1);
        delete[] string1;
        delete[] string2;
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
