// Copyright 2021 Pinezhanin Evgeny
#include <gtest/gtest.h>
#include "../../../modules/task_3/pinezhanin_e_linear_histogram_stretching/linear_histogram_stretching.h"
#include <gtest-mpi-listener.hpp>

TEST(Bubble_sort_odd_even_test, one) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image, ref_image;
    int width = 2, height = 2;

    if (rank == 0) {
        image.resize(height);
        for (int i = 0; i < height; i++) {
            image[i].resize(width);
        }
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, two) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image, ref_image;
    int width = 2, height = 2;

    if (rank == 0) {
        image.resize(height);
        for (int i = 0; i < height; i++) {
            image[i].resize(width);
        }
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, three) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image, ref_image;
    int width = 2, height = 2;

    if (rank == 0) {
        image.resize(height);
        for (int i = 0; i < height; i++) {
            image[i].resize(width);
        }
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, four) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image, ref_image;
    int width = 2, height = 2;

    if (rank == 0) {
        image.resize(height);
        for (int i = 0; i < height; i++) {
            image[i].resize(width);
        }
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, five) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int>> image, ref_image;
    int width = 2, height = 2;

    if (rank == 0) {
        image.resize(height);
        for (int i = 0; i < height; i++) {
            image[i].resize(width);
        }
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
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
