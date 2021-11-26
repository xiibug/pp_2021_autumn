// Copyright 2021 Sablin Alexander
#include <gtest/gtest.h>
#include "./max_el_of_vec.h"
#include <gtest-mpi-listener.hpp>

TEST(Max_element_test, 1) {
    // test parameters
    int ProcRank, dia, ref_max, calc_max;
    int n = 50;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        dia = 200;
        a = getRandomVector(a, n, dia);
        ref_max = CalcMaxNumber(a, n);
    }

    calc_max = DoParallelComputing(a, n);
    delete[] a;

    if (ProcRank == 0) {
        ASSERT_EQ(ref_max, calc_max);
    }
}

TEST(Max_element_test, 2) {
    // test parameters
    int ProcRank, dia, ref_max, calc_max;
    int n = 200;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        dia = 200;
        a = getRandomVector(a, n, dia);
        ref_max = CalcMaxNumber(a, n);
    }

    calc_max = DoParallelComputing(a, n);
    delete[] a;

    if (ProcRank == 0) {
        ASSERT_EQ(ref_max, calc_max);
    }
}

TEST(Max_element_test, 3) {
    // test parameters
    int ProcRank, dia, ref_max, calc_max;
    int n = 200;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        dia = 1000;
        a = getRandomVector(a, n, dia);
        ref_max = CalcMaxNumber(a, n);
    }

    calc_max = DoParallelComputing(a, n);
    delete[] a;

    if (ProcRank == 0) {
        ASSERT_EQ(ref_max, calc_max);
    }
}

TEST(Max_element_test, 4) {
    // test parameters
    int ProcRank, dia, ref_max, calc_max;
    int n = 200;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        dia = 150000;
        a = getRandomVector(a, n, dia);
        ref_max = CalcMaxNumber(a, n);
    }

    calc_max = DoParallelComputing(a, n);
    delete[] a;

    if (ProcRank == 0) {
        ASSERT_EQ(ref_max, calc_max);
    }
}

TEST(Max_element_test, 5) {
    // test parameters
    int ProcRank, dia, ref_max, calc_max;
    int n = 100000;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        dia = 150000;
        a = getRandomVector(a, n, dia);
        ref_max = CalcMaxNumber(a, n);
    }

    calc_max = DoParallelComputing(a, n);
    delete[] a;

    if (ProcRank == 0) {
        ASSERT_EQ(ref_max, calc_max);
    }
}

TEST(Max_element_test, 6) {
    // test parameters
    int ProcRank, dia, ref_max, calc_max;
    int n = 200;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0) {
        dia = 150000;
        a = getRandomVector(a, n, dia);
        ref_max = CalcMaxNumber(a, n);
    }

    calc_max = DoParallelComputing(a, n);
    delete[] a;

    if (ProcRank == 0) {
        ASSERT_EQ(ref_max, calc_max);
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
