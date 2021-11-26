// Copyright 2021 Nazarov Nikita
#include <gtest/gtest.h>
#include "./sum_of_vec_elem.h"
#include <gtest-mpi-listener.hpp>

const int n = 1;

TEST(Parallel_Operations_MPI, Test_Sum) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<double> vec;
    if (ProcRank == 0) {
        vec = getRandomVector(n);
    }

    double sum_all = getParallelOperations(vec, n, "+");

    if (ProcRank == 0) {
        double sum = getSequentialOperations(vec, n, "+");
        ASSERT_EQ(sum, sum_all);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum_2) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<double> vec;
    if (ProcRank == 0) {
        vec = getRandomVector(n + 1);
    }

    double sum_all = getParallelOperations(vec, n + 1, "+");

    if (ProcRank == 0) {
        double sum = getSequentialOperations(vec, n + 1, "+");
        ASSERT_EQ(sum, sum_all);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum_3) {
     int ProcRank;
     MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
     std::vector<double> vec;
     if (ProcRank == 0) {
         vec = getRandomVector(n + 2);
     }

     double sum_all = getParallelOperations(vec, n + 2, "+");

     if (ProcRank == 0) {
         double sum = getSequentialOperations(vec, n + 2, "+");
         ASSERT_EQ(sum, sum_all);
     }
}

TEST(Parallel_Operations_MPI, Test_Diff) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<double> vec;
    if (ProcRank == 0) {
        vec = getRandomVector(n + 3);
    }

    double diff_all = getParallelOperations(vec, n + 3, "-");

    if (ProcRank == 0) {
        double diff = getSequentialOperations(vec, n + 3, "-");
        ASSERT_EQ(diff, diff_all);
    }
}

TEST(Parallel_Operations_MPI, Test_Diff_2) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<double> vec;
    if (ProcRank == 0) {
        vec = getRandomVector(n + 4);
    }

    double diff_all = getParallelOperations(vec, n + 4, "-");

    if (ProcRank == 0) {
        double diff = getSequentialOperations(vec, n + 4, "-");
        ASSERT_EQ(diff, diff_all);
    }
}

TEST(Parallel_Operations_MPI, Test_Diff_3) {
     int ProcRank;
     MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
     std::vector<double> vec;
     if (ProcRank == 0) {
         vec = getRandomVector(n + 5);
     }

     double diff_all = getParallelOperations(vec, n + 5, "-");

     if (ProcRank == 0) {
         double diff = getSequentialOperations(vec, n + 5, "-");
         ASSERT_EQ(diff, diff_all);
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

