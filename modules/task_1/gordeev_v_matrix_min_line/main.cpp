// Copyright 2021 Gordeev Viktor
#include <gtest/gtest.h>
#include "./matrix_min_line_mpi.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Min_N_Proc) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* global_vec;
    const int count_rows = 4;
    const int count_columns = 5;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        global_vec = getRandomVector(count_rows, count_columns);
    }
    int* global_min = new int[count_rows];
    global_min = getParallelMatrixMinLine(global_vec,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = new int[count_rows];
        reference_min = getSequentialMatrixMinLine(global_vec,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Min_More_N_Proc) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* global_vec;
    const int count_rows = 10;
    const int count_columns = 6;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        global_vec = getRandomVector(count_rows, count_columns);
    }
    int* global_min = new int[count_rows];
    global_min = getParallelMatrixMinLine(global_vec,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = new int[count_rows];
        reference_min = getSequentialMatrixMinLine(global_vec,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Min) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* global_vec;
    const int count_rows = 10;
    const int count_columns = 1;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        global_vec = getRandomVector(count_rows, count_columns);
    }

    int* global_min = new int[count_rows];
    global_min = getParallelMatrixMinLine(global_vec,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = new int[count_rows];
        reference_min = getSequentialMatrixMinLine(global_vec,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Min_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* global_vec;
    const int count_rows = 100;
    const int count_columns = 100;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        global_vec = getRandomVector(count_rows, count_columns);
    }

    int* global_min = new int[count_rows];
    global_min = getParallelMatrixMinLine(global_vec,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = new int[count_rows];
        reference_min = getSequentialMatrixMinLine(global_vec,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Min_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* global_vec;
    const int count_rows = 10000;
    const int count_columns = 10000;
    global_vec = new int[count_rows * count_columns];
    if (rank == 0) {
        global_vec = getRandomVector(count_rows, count_columns);
    }

    int* global_min = new int[count_rows];
    global_min = getParallelMatrixMinLine(global_vec,
        count_rows, count_columns);

    if (rank == 0) {
        int* reference_min = new int[count_rows];
        reference_min = getSequentialMatrixMinLine(global_vec,
            count_rows, count_columns);
        for (int i = 0; i < count_rows; i++) {
            ASSERT_EQ(reference_min[i], global_min[i]);
        }
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
