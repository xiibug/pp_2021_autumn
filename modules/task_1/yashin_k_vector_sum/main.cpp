// Copyright 2021 Yashin Kirill

#include <gtest/gtest.h>
#include "./vector_sum.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Sum_MPI, Size_50_Prom_49) {
    int ProcRank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 50;
    if (ProcRank == 0) {
        prom = 49;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (ProcRank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, 1111111111111111) {
    int ProcRank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 5;
    if (ProcRank == 0) {
        prom = 49;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (ProcRank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, Size_50_Prom_1000) {
    int ProcRank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 50;
    if (ProcRank == 0) {
        prom = 1000;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (ProcRank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, Size_500_Prom_1000) {
    int ProcRank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 500;
    if (ProcRank == 0) {
        prom = 1000;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (ProcRank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, Size_1500_Prom_1000) {
    int ProcRank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 1500;
    if (ProcRank == 0) {
        prom = 1000;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (ProcRank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, Test_10000_Prom_1000) {
    int Comm_rank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &Comm_rank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 10000;
    if (Comm_rank == 0) {
        prom = 1000;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (Comm_rank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, Test_10000_Prom_10000) {
    int Comm_rank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &Comm_rank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 10000;
    if (Comm_rank == 0) {
        prom = 10000;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (Comm_rank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, Test_1000000_Prom_1000) {
    int Comm_rank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &Comm_rank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 1000000;
    if (Comm_rank == 0) {
        prom = 1000;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (Comm_rank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

TEST(Parallel_Sum_MPI, Test_1000000_Prom_10000) {
    int Comm_rank, prom;
    MPI_Comm_rank(MPI_COMM_WORLD, &Comm_rank);
    std::vector<int> vec;
    int calc_sum, ref_sum;
    int vec_size = 1000000;
    if (Comm_rank == 0) {
        prom = 10000;
        vec = getRandVector(vec_size, prom);
        ref_sum = getSum(vec);
    }
    calc_sum = getParallelSum(vec, vec_size);
    if (Comm_rank == 0) {
        ASSERT_EQ(ref_sum, calc_sum);
    }
}

int main(int argc, char**argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
