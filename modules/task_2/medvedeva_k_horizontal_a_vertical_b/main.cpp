// Copyright 2021 Medvedeva Karina
#include <gtest/gtest.h>
#include <vector>
#include "./horizontal_a_vertical_b.h"
#include <gtest-mpi-listener.hpp>

TEST(Generation_Matrix, can_generate_square_matrix) {
    ASSERT_NO_THROW(getRandomMatrix(10, 10));
}

TEST(Generation_Matrix, can_generate_arbitrary_matrix) {
    ASSERT_NO_THROW(getRandomMatrix(10, 15));
}

TEST(Sequential_Operations_MPI, getSequentialOperations_can_work_with_square_matrix) {
    std::vector<int> matrix1 = getRandomMatrix(10, 10);
    std::vector<int> matrix2 = getRandomMatrix(10, 10);
    ASSERT_NO_THROW(getSequentialOperations(matrix1, matrix2, 10, 10, 10));
}

TEST(Sequential_Operations_MPI, getSequentialOperations_can_work_with_arbitrary_matrix) {
    std::vector<int> matrix1 = getRandomMatrix(10, 15);
    std::vector<int> matrix2 = getRandomMatrix(15, 10);
    ASSERT_NO_THROW(getSequentialOperations(matrix1, matrix2, 10, 15, 10));
}

TEST(Sequential_Operations_MPI, getSequentialOperations_works_correctly_with_square_matrix) {
    std::vector<int> matrix1 = { 1, 1,
                                 1, 1 };
    std::vector<int> matrix2 = { 2, 2,
                                 2, 2 };
    std::vector<int> res = { 4, 4,
                             4, 4 };
    ASSERT_EQ(res, getSequentialOperations(matrix1, matrix2, 2, 2, 2));
}

TEST(Sequential_Operations_MPI, getSequentialOperations_works_correctly_with_arbitary_matrix) {
    std::vector<int> matrix1 = {1, 1, 1, 1,
                                1, 1, 1, 1};
    std::vector<int> matrix2 = {2, 2, 2,
                                2, 2, 2,
                                2, 2, 2,
                                2, 2, 2};
    std::vector<int> res = { 8, 8, 8,
                             8, 8, 8 };
    ASSERT_EQ(res, getSequentialOperations(matrix1, matrix2, 2, 4, 3));
}

TEST(Parallel_Operations_MPI, getParallelOperations_can_work_with_square_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 20, column_count = 20;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    ASSERT_NO_THROW(getParallelOperations(matrix1, matrix2, row_count, column_count));
}

TEST(Parallel_Operations_MPI, getParallelOperations_can_work_with_arbitary_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 20, column_count = 30;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    ASSERT_NO_THROW(getParallelOperations(matrix1, matrix2, row_count, column_count));
}

TEST(Parallel_Operations_MPI, getParallelOperations_works_correctly_with_square_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 20, column_count = 20;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);

    if (rank == 0) {
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);

        ASSERT_EQ(res, expected_res);
    }
}

TEST(Parallel_Operations_MPI, getParallelOperations_works_correctly_with_more_columns) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 20, column_count = 30;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);

    if (rank == 0) {
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);

        ASSERT_EQ(res, expected_res);
    }
}

TEST(Parallel_Operations_MPI, getParallelOperations_works_correctly_with_more_rows) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 30, column_count = 20;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);

    if (rank == 0) {
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);

        ASSERT_EQ(res, expected_res);
    }
}

TEST(Parallel_Operations_MPI, getParallelOperations_works_correctly_with_odd_size_and_more_rows) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 27, column_count = 15;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);

    if (rank == 0) {
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);

        ASSERT_EQ(res, expected_res);
    }
}

TEST(Parallel_Operations_MPI, getParallelOperations_works_correctly_with_odd_size_and_more_columns) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 15, column_count = 27;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);

    if (rank == 0) {
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);

        ASSERT_EQ(res, expected_res);
    }
}

TEST(DISABLED_Parallel_Operations_MPI, check_running_time_of_getParallelOperations_with_small_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 55, column_count = 67;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    auto start_getParallelOperations = MPI_Wtime();
    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);
    auto finish_getParallelOperations = MPI_Wtime();

    if (rank == 0) {
        auto start_getSequentialOperations = MPI_Wtime();
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);
        auto finish_getSequentialOperations = MPI_Wtime();

        auto getSequentialOperations_running_time = finish_getSequentialOperations - start_getSequentialOperations;
        auto getParallelOperations_running_time = finish_getParallelOperations - start_getParallelOperations;
        auto acceleration = getSequentialOperations_running_time / getParallelOperations_running_time;

        printf("Running time of sequential algorithm=%lf\nRunning time of parallel algorithm=%lf\n",
            getSequentialOperations_running_time, getParallelOperations_running_time);
        printf("Acceleration=%lf\n", acceleration);
    }
}

TEST(DISABLED_Parallel_Operations_MPI, check_running_time_of_getParallelOperations_with_middle_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 205, column_count = 198;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    auto start_getParallelOperations = MPI_Wtime();
    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);
    auto finish_getParallelOperations = MPI_Wtime();

    if (rank == 0) {
        auto start_getSequentialOperations = MPI_Wtime();
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);
        auto finish_getSequentialOperations = MPI_Wtime();

        auto getSequentialOperations_running_time = finish_getSequentialOperations - start_getSequentialOperations;
        auto getParallelOperations_running_time = finish_getParallelOperations - start_getParallelOperations;
        auto acceleration = getSequentialOperations_running_time / getParallelOperations_running_time;

        printf("Running time of sequential algorithm=%lf\nRunning time of parallel algorithm=%lf\n",
            getSequentialOperations_running_time, getParallelOperations_running_time);
        printf("Acceleration=%lf\n", acceleration);
    }
}

TEST(DISABLED_Parallel_Operations_MPI, check_running_time_of_getParallelOperations_with_big_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type row_count = 500, column_count = 500;
    std::vector<int> matrix1(row_count * column_count), matrix2(row_count * column_count);

    if (rank == 0) {
        matrix1 = getRandomMatrix(row_count, column_count);
        matrix2 = getRandomMatrix(column_count, row_count);
    }

    auto start_getParallelOperations = MPI_Wtime();
    std::vector<int> res = getParallelOperations(matrix1, matrix2, row_count, column_count);
    auto finish_getParallelOperations = MPI_Wtime();

    if (rank == 0) {
        auto start_getSequentialOperations = MPI_Wtime();
        std::vector<int> expected_res = getSequentialOperations(matrix1, matrix2, row_count, column_count, row_count);
        auto finish_getSequentialOperations = MPI_Wtime();

        auto getSequentialOperations_running_time = finish_getSequentialOperations - start_getSequentialOperations;
        auto getParallelOperations_running_time = finish_getParallelOperations - start_getParallelOperations;
        auto acceleration = getSequentialOperations_running_time / getParallelOperations_running_time;

        printf("Running time of sequential algorithm=%lf\nRunning time of parallel algorithm=%lf\n",
            getSequentialOperations_running_time, getParallelOperations_running_time);
        printf("Acceleration=%lf\n", acceleration);
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
