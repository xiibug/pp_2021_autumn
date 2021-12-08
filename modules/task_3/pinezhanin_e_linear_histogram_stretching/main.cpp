// Copyright 2021 Pinezhanin Evgeny
#include <gtest/gtest.h>
#include "../../../modules/task_3/pinezhanin_e_linear_histogram_stretching/linear_histogram_stretching.h"
#include <gtest-mpi-listener.hpp>

TEST(Bubble_sort_odd_even_test, res_opencv_3x3_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<uchar>> image, ref_image, opencv_image;

    if (rank == 0) {
        image = std::vector<std::vector<uchar>>{ {77, 74, 118},
                                                 {136, 90, 77},
                                                 {70, 164, 76} };
        ref_image = image;
        opencv_image = std::vector<std::vector<uchar>>{ {19, 11, 130},
                                                        {179, 54, 19},
                                                        {0, 255, 16} };
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
        ASSERT_EQ(ref_image, opencv_image);
        ASSERT_EQ(image, opencv_image);
    }
}

TEST(Bubble_sort_odd_even_test, res_opencv_5x5_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<uchar>> image, ref_image, opencv_image;

    if (rank == 0) {
        image = std::vector<std::vector<uchar>>{ {182, 175, 191, 103, 120},
                                                 {191, 178, 121, 110, 166},
                                                 {98, 98, 106, 158, 136},
                                                 {101, 91, 108, 44, 146},
                                                 {30, 69, 73, 27, 48} };
        ref_image = image;
        opencv_image = std::vector<std::vector<uchar>>{ {241, 230, 255, 118, 145},
                                                        {255, 235, 146, 129, 216},
                                                        {110, 110, 123, 204, 169},
                                                        {115, 100, 126, 26, 185},
                                                        {5, 65, 72, 0, 33} };
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
        ASSERT_EQ(ref_image, opencv_image);
        ASSERT_EQ(image, opencv_image);
    }
}

TEST(Bubble_sort_odd_even_test, 5x5_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<uchar>> image, ref_image;
    int width = 5, height = 5;

    if (rank == 0) {
        image = getRandomMatrix(height, width, 10, 189);
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
        ASSERT_EQ(image, ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, 10x10_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<uchar>> image, ref_image;
    int width = 10, height = 10;

    if (rank == 0) {
        image = getRandomMatrix(height, width, 10, 189);
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
        ASSERT_EQ(image, ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, 100x100_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<uchar>> image, ref_image;
    int width = 100, height = 100;

    if (rank == 0) {
        image = getRandomMatrix(height, width, 10, 189);
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
        ASSERT_EQ(image, ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, white_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<uchar>> image, ref_image;
    int width = 20, height = 20;

    if (rank == 0) {
        image.resize(height);
        for (int i = 0; i < height; i++) {
            image[i].resize(width);
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                image[i][j] = 255;
            }
        }
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
        ASSERT_EQ(image, ref_image);
    }
}

TEST(Bubble_sort_odd_even_test, black_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<uchar>> image, ref_image;
    int width = 20, height = 20;

    if (rank == 0) {
        image.resize(height);
        for (int i = 0; i < height; i++) {
            image[i].resize(width);
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                image[i][j] = 0;
            }
        }
        ref_image = image;
    }

    image = LinearHistogramStretchingParallel(image);

    if (rank == 0) {
        ref_image = LinearHistogramStretchingSequential(ref_image);
        ASSERT_EQ(image, ref_image);
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
