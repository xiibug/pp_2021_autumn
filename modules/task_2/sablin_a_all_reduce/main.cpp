// Copyright 2021 Sablin Alexander
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "./all_reduce.h"

TEST(All_reduse_test, SIZEx1_INT_SUM) {
    int ProcRank, n, dia;
    int flag = 1;
    typedef int T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 10;
    dia = 100;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx1_DOUBLE_SUM) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef double T;
    double* send_vec = nullptr;
    double* ref_vec = nullptr;
    double* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 10;
    dia = 100;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx1_DOUBLE_PROD) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef double T;
    double* send_vec = nullptr;
    double* ref_vec = nullptr;
    double* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 10;
    dia = 100;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_DOUBLE, MPI_PROD, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_DOUBLE, MPI_PROD, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx1_DOUBLE_MIN) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef double T;
    double* send_vec = nullptr;
    double* ref_vec = nullptr;
    double* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 10;
    dia = 100;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx1_FLOAT_SUM) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef float T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 10;
    dia = 100;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx3_INT_SUM) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef int T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 1000;
    dia = 1000;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx3_DOUBLE_SUM) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef double T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 1000;
    dia = 1000;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx3_FLOAT_SUM) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef float T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 1000;
    dia = 1000;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx6_INT_SUM) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef int T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 1000000;
    dia = 10000;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx6_DOUBLE_MAX) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef double T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 1000000;
    dia = 10000;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
    }
}

TEST(All_reduse_test, SIZEx6_FLOAT_SUM) {

    int ProcRank, n, dia;
    int flag = 1;
    typedef float T;
    T* send_vec = nullptr;
    T* ref_vec = nullptr;
    T* calc_vec = nullptr;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    n = 1000000;
    dia = 10000;
    send_vec = getRandomVector<T>(send_vec, n, dia, true);
    calc_vec = getRandomVector<T>(calc_vec, n, dia, false);
    Allreduce(send_vec, calc_vec, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    ref_vec = getRandomVector<T>(ref_vec, n, dia, false);
    MPI_Allreduce(send_vec, ref_vec, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        if (ref_vec[i] != calc_vec[i]) {
            flag = 0;
            break;
        }
    }

    delete[] send_vec;
    delete[] ref_vec;
    delete[] calc_vec;

    if (ProcRank == 0) {
        ASSERT_EQ(flag, 1);
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
