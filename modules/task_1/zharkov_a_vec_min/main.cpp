// Copyright 2021 Zharkov Andrey
#include <gtest/gtest.h>
#include "./vec_min.h"
#include <gtest-mpi-listener.hpp>

TEST(Min_vec, 1) {
    int rank, intarval, loc_min, gl_min;
    int n = 99;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        intarval = 100;
        a = getRandomVector(a, n, intarval);
        loc_min = Get_Min(a, n);
    }

    gl_min = ParallCulc(a, n);
    delete[] a;

    if (rank == 0) {
        ASSERT_EQ(loc_min, gl_min);
    }
}

TEST(Min_vec, 2) {
    int rank, intarval, loc_min, gl_min;
    int n = 599;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        intarval = 100;
        a = getRandomVector(a, n, intarval);
        loc_min = Get_Min(a, n);
    }

    gl_min = ParallCulc(a, n);
    delete[] a;

    if (rank == 0) {
        ASSERT_EQ(loc_min, gl_min);
    }
}

TEST(Min_vec, 3) {
    int rank, intarval, loc_min, gl_min;
    int n = 99;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        intarval = 1000;
        a = getRandomVector(a, n, intarval);
        loc_min = Get_Min(a, n);
    }

    gl_min = ParallCulc(a, n);
    delete[] a;

    if (rank == 0) {
        ASSERT_EQ(loc_min, gl_min);
    }
}

TEST(Min_vec, 4) {
    int rank, intarval, loc_min, gl_min;
    int n = 999;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        intarval = 5000;
        a = getRandomVector(a, n, intarval);
        loc_min = Get_Min(a, n);
    }

    gl_min = ParallCulc(a, n);
    delete[] a;

    if (rank == 0) {
        ASSERT_EQ(loc_min, gl_min);
    }
}

TEST(Min_vec, 5) {
    int rank, intarval, loc_min, gl_min;
    int n = 999;
    double* a = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        intarval = 10000;
        a = getRandomVector(a, n, intarval);
        loc_min = Get_Min(a, n);
    }

    gl_min = ParallCulc(a, n);
    delete[] a;

    if (rank == 0) {
        ASSERT_EQ(loc_min, gl_min);
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
