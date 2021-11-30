// Copyright 2021 Zarubin Mikhail
#include <gtest/gtest.h>
#include <vector>
#include "./dense_matrix_cannon_algorithm.h"
#include <gtest-mpi-listener.hpp>


TEST(GENERATE_VECTOR, can_generate_random_matrix) {
    std::vector<double> matrix(5 * 5);
    ASSERT_NO_THROW(generateRandomMatrix(&matrix, 5, -100, 100));
}

TEST(SEQUENTIAL_OPERATIONS, can_run_sequential_operations) {
    std::vector<double> first_matrix(5 * 5), second_matrix(5 * 5), answer(5 * 5, 0.0);
    generateRandomMatrix(&first_matrix, 5, -100, 100);
    generateRandomMatrix(&second_matrix, 5, -100, 100);
    ASSERT_NO_THROW(getSequentialOperations(first_matrix, second_matrix, &answer, 5));
}

TEST(SEQUENTIAL_OPERATIONS, correct_work_sequential_operations) {
    std::vector<double> first_matrix = { 3.7 , 1.5, -4.1,
                                        10.2, -8.6, 7.3,
                                        -5.3, 9.2, -0.8 };
    std::vector<double> second_matrix = { 2.9 , 0.5, -3.4,
                                          11.8, -2.6, 10.3,
                                          -1.3, 0.2, -10.1 };
    std::vector<double> expected_result = { 33.76, -2.87, 44.28,
                                            -81.39, 28.92, -196.99,
                                            94.23, -26.73, 120.86 };
    std::vector<double> result(3 * 3, 0.0);
    getSequentialOperations(first_matrix, second_matrix, &result, 3);

    for (std::vector<double>::size_type i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(result[i], expected_result[i], 0.001);
    }
}

TEST(PARALLEL_OPERATIONS, can_run_parallel_operations) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double>::size_type matrix_size = 30;
    std::vector<double> first_matrix(matrix_size * matrix_size, 0.0);
    std::vector<double> second_matrix(matrix_size * matrix_size, 0.0);

    if (rank == 0) {
        generateRandomMatrix(&first_matrix, matrix_size, -100, 100);
        generateRandomMatrix(&second_matrix, matrix_size, -100, 100);
    }

    ASSERT_NO_THROW(getParallelOperations(first_matrix, second_matrix, matrix_size));
}

TEST(PARALLEL_OPERATIONS, correct_work_with_matirx_size_multiple_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double>::size_type matrix_size = 44;
    std::vector<double> first_matrix(matrix_size * matrix_size, 0.0);
    std::vector<double> second_matrix(matrix_size * matrix_size, 0.0);

    if (rank == 0) {
        generateRandomMatrix(&first_matrix, matrix_size, -100, 100);
        generateRandomMatrix(&second_matrix, matrix_size, -100, 100);
    }

    std::vector<double> result = getParallelOperations(first_matrix, second_matrix, matrix_size);

    if (rank == 0) {
        std::vector<double> expected_result(matrix_size * matrix_size, 0.0);
        getSequentialOperations(first_matrix, second_matrix, &expected_result, matrix_size);

        for (std::vector<double>::size_type i = 0; i < result.size(); ++i) {
            ASSERT_NEAR(result[i], expected_result[i], 0.001);
        }
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_with_matirx_size_multiple_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double>::size_type matrix_size = 27;
    std::vector<double> first_matrix(matrix_size * matrix_size, 0.0);
    std::vector<double> second_matrix(matrix_size * matrix_size, 0.0);

    if (rank == 0) {
        generateRandomMatrix(&first_matrix, matrix_size, -100, 100);
        generateRandomMatrix(&second_matrix, matrix_size, -100, 100);
    }

    std::vector<double> result = getParallelOperations(first_matrix, second_matrix, matrix_size);

    if (rank == 0) {
        std::vector<double> expected_result(matrix_size * matrix_size, 0.0);
        getSequentialOperations(first_matrix, second_matrix, &expected_result, matrix_size);

        for (std::vector<double>::size_type i = 0; i < result.size(); ++i) {
            ASSERT_NEAR(result[i], expected_result[i], 0.001);
        }
    }
}

TEST(PARALLEL_OPERATIONS, correct_work_with_matirx_size_multiple_5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double>::size_type matrix_size = 25;
    std::vector<double> first_matrix(matrix_size * matrix_size, 0.0);
    std::vector<double> second_matrix(matrix_size * matrix_size, 0.0);

    if (rank == 0) {
        generateRandomMatrix(&first_matrix, matrix_size, -100, 100);
        generateRandomMatrix(&second_matrix, matrix_size, -100, 100);
    }

    std::vector<double> result = getParallelOperations(first_matrix, second_matrix, matrix_size);

    if (rank == 0) {
        std::vector<double> expected_result(matrix_size * matrix_size, 0.0);
        getSequentialOperations(first_matrix, second_matrix, &expected_result, matrix_size);

        for (std::vector<double>::size_type i = 0; i < result.size(); ++i) {
            ASSERT_NEAR(result[i], expected_result[i], 0.001);
        }
    }
}


TEST(PARALLEL_OPERATIONS, correct_work_with_matirx_size_multiple_7) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double>::size_type matrix_size = 49;
    std::vector<double> first_matrix(matrix_size * matrix_size, 0.0);
    std::vector<double> second_matrix(matrix_size * matrix_size, 0.0);

    if (rank == 0) {
        generateRandomMatrix(&first_matrix, matrix_size, -100, 100);
        generateRandomMatrix(&second_matrix, matrix_size, -100, 100);
    }

    std::vector<double> result = getParallelOperations(first_matrix, second_matrix, matrix_size);

    if (rank == 0) {
        std::vector<double> expected_result(matrix_size * matrix_size, 0.0);
        getSequentialOperations(first_matrix, second_matrix, &expected_result, matrix_size);

        for (std::vector<double>::size_type i = 0; i < result.size(); ++i) {
            ASSERT_NEAR(result[i], expected_result[i], 0.001);
        }
    }
}

TEST(DISABLED_PARALLEL_OPERATIONS, comparison_working_hours_with_matrix_120x120) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double>::size_type matrix_size = 120;
    std::vector<double> first_matrix(matrix_size * matrix_size, 0.0);
    std::vector<double> second_matrix(matrix_size * matrix_size, 0.0);

    if (rank == 0) {
        generateRandomMatrix(&first_matrix, matrix_size, -100, 100);
        generateRandomMatrix(&second_matrix, matrix_size, -100, 100);
    }

    auto start_parallel_algorithm = MPI_Wtime();
    std::vector<double> result = getParallelOperations(first_matrix, second_matrix, matrix_size);
    auto finish_parallel_algorithm = MPI_Wtime();

    if (rank == 0) {
        std::vector<double> expected_result(matrix_size * matrix_size, 0.0);

        auto start_sequential_algorithm = MPI_Wtime();
        getSequentialOperations(first_matrix, second_matrix, &expected_result, matrix_size);
        auto finish_sequential_algorithm = MPI_Wtime();

        auto parallel_time = finish_parallel_algorithm - start_parallel_algorithm;
        auto sequential_time = finish_sequential_algorithm - start_sequential_algorithm;

        printf("Sequential Time = %lf\nParallel Time = %lf\nBoost = %lf\n",
            sequential_time, parallel_time, sequential_time / parallel_time);
    }
}

TEST(DISABLED_PARALLEL_OPERATIONS, comparison_working_hours_with_matrix_240x240) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double>::size_type matrix_size = 240;
    std::vector<double> first_matrix(matrix_size * matrix_size, 0.0);
    std::vector<double> second_matrix(matrix_size * matrix_size, 0.0);

    if (rank == 0) {
        generateRandomMatrix(&first_matrix, matrix_size, -100, 100);
        generateRandomMatrix(&second_matrix, matrix_size, -100, 100);
    }

    auto start_parallel_algorithm = MPI_Wtime();
    std::vector<double> result = getParallelOperations(first_matrix, second_matrix, matrix_size);
    auto finish_parallel_algorithm = MPI_Wtime();

    if (rank == 0) {
        std::vector<double> expected_result(matrix_size * matrix_size, 0.0);

        auto start_sequential_algorithm = MPI_Wtime();
        getSequentialOperations(first_matrix, second_matrix, &expected_result, matrix_size);
        auto finish_sequential_algorithm = MPI_Wtime();

        auto parallel_time = finish_parallel_algorithm - start_parallel_algorithm;
        auto sequential_time = finish_sequential_algorithm - start_sequential_algorithm;

        printf("Sequential Time = %lf\nParallel Time = %lf\nBoost = %lf\n",
            sequential_time, parallel_time, sequential_time / parallel_time);
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
