// Copyright 2021 Gordeev Viktor
#include <gtest/gtest.h>
#include "./matrix_min_line_mpi.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Min_N_Proc) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_rows = 4;
    const int count_columns = 5;
    int* global_vec = nullptr;
    int* global_min = nullptr;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        getRandomVector(global_vec, count_rows, count_columns);
        global_min = new int[count_rows];
    }
    getParallelMatrixMinLine(global_vec, global_min,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = nullptr;
        reference_min = new int[count_rows];
        getSequentialMatrixMinLine(global_vec, reference_min,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
        delete[] global_min;
        delete[] reference_min;
        delete[] global_vec;
    }
}

TEST(Parallel_Operations_MPI, Test_Min_More_N_Proc) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_rows = 6;
    const int count_columns = 10;
    int* global_vec = nullptr;
    int* global_min = nullptr;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        getRandomVector(global_vec, count_rows, count_columns);
        global_min = new int[count_rows];
    }
    getParallelMatrixMinLine(global_vec, global_min,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = nullptr;
        reference_min = new int[count_rows];
        getSequentialMatrixMinLine(global_vec, reference_min,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
        delete[] global_min;
        delete[] reference_min;
        delete[] global_vec;
    }
}

TEST(Parallel_Operations_MPI, Test_Min) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_rows = 10;
    const int count_columns = 1;
    int* global_vec = nullptr;
    int* global_min = nullptr;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        getRandomVector(global_vec, count_rows, count_columns);
        global_min = new int[count_rows];
    }
    getParallelMatrixMinLine(global_vec, global_min,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = nullptr;
        reference_min = new int[count_rows];
        getSequentialMatrixMinLine(global_vec, reference_min,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
        delete[] global_min;
        delete[] reference_min;
        delete[] global_vec;
    }
}

TEST(Parallel_Operations_MPI, Test_Min_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_rows = 100;
    const int count_columns = 100;
    int* global_vec = nullptr;
    int* global_min = nullptr;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        getRandomVector(global_vec, count_rows, count_columns);
        global_min = new int[count_rows];
    }
    getParallelMatrixMinLine(global_vec, global_min,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = nullptr;
        reference_min = new int[count_rows];
        getSequentialMatrixMinLine(global_vec, reference_min,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
        delete[] global_min;
        delete[] reference_min;
        delete[] global_vec;
    }
}

TEST(Parallel_Operations_MPI, Test_Min_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_rows = 10000;
    const int count_columns = 10000;
    int* global_vec = nullptr;
    int* global_min = nullptr;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        getRandomVector(global_vec, count_rows, count_columns);
        global_min = new int[count_rows];
    }
    getParallelMatrixMinLine(global_vec, global_min,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = nullptr;
        reference_min = new int[count_rows];
        getSequentialMatrixMinLine(global_vec, reference_min,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
        delete[] global_min;
        delete[] reference_min;
        delete[] global_vec;
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
