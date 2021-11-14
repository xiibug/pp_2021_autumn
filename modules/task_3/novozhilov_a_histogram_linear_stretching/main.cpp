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
