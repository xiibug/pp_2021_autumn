// Copyright 2021 Lebedev Alexey
#include <gtest/gtest.h>
#include <string>
#include <random>
#include "./unique_chars.h"
#include <gtest-mpi-listener.hpp>


class UniqueCharsTEST : public ::testing::Test {
 protected:
    void SetUp() override {
        strs1 = {"apple", "", "", "orange", "kkk"};
        strs2 = {"orange", "apple", "", "orange", "mmm"};
        answers = {6, 4, 0, 0, 2};
    }
    static const int MAXSIZE = 200;
    static const int STEP = 20;
    std::vector<std::string> strs1;
    std::vector<std::string> strs2;
    std::vector<int> answers;
};


TEST_F(UniqueCharsTEST, Test_Sequential) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int global_count;
        for (size_t i = 0; i < answers.size(); i++) {
            global_count = UniqueCharsSequential(strs1[i], strs2[i]);
            ASSERT_EQ(global_count, answers[i]);
        }
    }
}

TEST_F(UniqueCharsTEST, Test_Parallel) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::string str1, str2;
    int global_count;

    for (size_t i = 0; i < answers.size(); i++) {
        if (rank == 0) {
            str1 = strs1[i];
            str2 = strs2[i];
        }

        global_count = UniqueCharsParallel(str1, str2);

        if (rank == 0) {
            ASSERT_EQ(global_count, answers[i]);
        }
    }
}

TEST_F(UniqueCharsTEST, Test_Parallel_Random_Data_Same_Size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str1, str2;
    int global_count;
    for (size_t data_size = 0; data_size < MAXSIZE; data_size += STEP) {
        if (rank == 0) {
            str1 = getRandomString(data_size);
            str2 = getRandomString(data_size);
        }

        global_count = UniqueCharsParallel(str1, str2);

        if (rank == 0) {
            ASSERT_EQ(global_count, UniqueCharsSequential(str1, str2));
        }
    }
}

TEST_F(UniqueCharsTEST, Test_Parallel_Random_Data_Different_Size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str1, str2;
    int global_count;
    for (size_t data_size = 0; data_size < MAXSIZE; data_size += STEP) {
        if (rank == 0) {
            str1 = getRandomString(data_size);
            str2 = getRandomString(MAXSIZE - data_size);
        }

        global_count = UniqueCharsParallel(str1, str2);

        if (rank == 0) {
            ASSERT_EQ(global_count, UniqueCharsSequential(str1, str2));
        }
    }
}

TEST_F(UniqueCharsTEST, Test_Parallel_Random_Data_Random_Size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str1, str2;
    int global_count;
    if (rank == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, MAXSIZE);
        str1 = getRandomString(distrib(gen));
        str2 = getRandomString(distrib(gen));
    }

    global_count = UniqueCharsParallel(str1, str2);

    if (rank == 0) {
        ASSERT_EQ(global_count, UniqueCharsSequential(str1, str2));
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
