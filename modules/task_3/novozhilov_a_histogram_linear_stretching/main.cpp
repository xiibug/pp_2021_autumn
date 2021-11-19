// Copyright 2021 Novozhilov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./histogram_linear_stretching.h"
#include <gtest-mpi-listener.hpp>


TEST(Parallel_Operations_MPI, Test_matrix_one_column) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image;
    if (rank == 0) {
        image = getRandomMatrix(25, 1);
    }
    std::vector<std::vector<int>> result_p = histogrammStretchingParallel(image, 25, 1);
    if (rank == 0) {
        std::vector<std::vector<int>> result_s = histogrammStretchingSequential(image);
        ASSERT_EQ(result_p, result_s);
    }
}

TEST(Parallel_Operations_MPI, Test_even_number_of_rows) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image;

    if (rank == 0) {
        image = getRandomMatrix(100, 25);
    }

    std::vector<std::vector<int>> result_p = histogrammStretchingParallel(image, 100, 25);

    if (rank == 0) {
        std::vector<std::vector<int>> result_s = histogrammStretchingSequential(image);
        ASSERT_EQ(result_p, result_s);
    }
}

TEST(Parallel_Operations_MPI, Test_odd_number_of_rows) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image;

    if (rank == 0) {
        image = getRandomMatrix(125, 25);
    }

    std::vector<std::vector<int>> result_p = histogrammStretchingParallel(image, 125, 25);

    if (rank == 0) {
        std::vector<std::vector<int>> result_s = histogrammStretchingSequential(image);
        ASSERT_EQ(result_p, result_s);
    }
}


TEST(Parallel_Operations_MPI, Test_huge_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image;

    if (rank == 0) {
        image = getRandomMatrix(1000, 1500);
    }

    std::vector<std::vector<int>> result_p = histogrammStretchingParallel(image, 1000, 1500);

    if (rank == 0) {
        std::vector<std::vector<int>> result_s = histogrammStretchingSequential(image);
        ASSERT_EQ(result_p, result_s);
    }
}

TEST(Parallel_Operations_MPI, Test_square_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image;

    if (rank == 0) {
        image = getRandomMatrix(100, 100);
    }

    std::vector<std::vector<int>> result_p = histogrammStretchingParallel(image, 100, 100);

    if (rank == 0) {
        std::vector<std::vector<int>> result_s = histogrammStretchingSequential(image);
        ASSERT_EQ(result_p, result_s);
    }
}

TEST(Parallel_Operations_MPI, Test_time) {
    int rank, size;
    double parallel_t1, parallel_t2, sequential_t1, sequential_t2;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::vector<std::vector<int>> image;
    if (rank == 0) {
        if (size == 1) {
            ASSERT_TRUE(true);
            return;
        }
        image = getRandomMatrix(1000, 1000);
        parallel_t1 = MPI_Wtime();
    }
    std::vector<std::vector<int>> result_p = histogrammStretchingParallel(image, 1000, 1000);
    if (rank == 0) {
        parallel_t2 = MPI_Wtime();
        sequential_t1 = MPI_Wtime();
        std::vector<std::vector<int>> result_s = histogrammStretchingSequential(image);
        sequential_t2 = MPI_Wtime();
        double p_time = parallel_t2 - parallel_t1;
        double s_time = sequential_t2 - sequential_t1;
        ASSERT_TRUE(p_time <= s_time);
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
