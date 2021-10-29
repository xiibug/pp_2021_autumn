#include <gtest/gtest.h>
#include <string>
#include "unique_chars.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Sequential) {
    std::string str1 = "apple";
    std::string str2 = "orange";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 6);

    str1 = "";
    str2 = "apple";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 4);

    str1 = "";
    str2 = "";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 0);

    str1 = "orange";
    str2 = "orange";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 0);

    str1 = "kkk";
    str2 = "mmm";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 2);
}

TEST(Parallel_Operations_MPI, Test_Parallel) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str1, str2;
    int global_count;

    if(rank == 0) {
        str1 = "apple";
        str2 = "orange";
    }

    global_count = UniqueCharsParallel(str1, str2);

    if(rank == 0) {
        ASSERT_EQ(global_count, 6);
    }

    if(rank == 0) {
        str1 = "";
        str2 = "apple";
    }

    global_count = UniqueCharsParallel(str1, str2);

    if(rank == 0) {
        ASSERT_EQ(global_count, 4);
    }

    if(rank == 0) {
        str1 = "";
        str2 = "";
    }

    global_count = UniqueCharsParallel(str1, str2);

    if(rank == 0) {
        ASSERT_EQ(global_count, 0);
    }

    if(rank == 0) {
        str1 = "orange";
        str2 = "orange";
    }

    global_count = UniqueCharsParallel(str1, str2);

    if(rank == 0) {
        ASSERT_EQ(global_count, 0);
    }

    if(rank == 0) {
        str1 = "kkk";
        str2 = "mmm";
    }

    global_count = UniqueCharsParallel(str1, str2);

    if(rank == 0) {
        ASSERT_EQ(global_count, 2);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum3) {
    std::string str1 = "huie";
    std::string str2 = "hjkl";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 6);
}

TEST(Parallel_Operations_MPI, Test_Sum4) {
    std::string str1 = "huie";
    std::string str2 = "hjkl";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 6);
}

TEST(Parallel_Operations_MPI, Test_Sum5) {
    std::string str1 = "huie";
    std::string str2 = "hjkl";
    ASSERT_EQ(UniqueCharsSequential(str1, str2), 6);
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
