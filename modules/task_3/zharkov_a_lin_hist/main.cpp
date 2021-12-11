// Copyright 2021 Zharkov Andrey
#include <gtest/gtest.h>
#include <vector>
#include "./lin_hist.h"
#include <gtest-mpi-listener.hpp>


TEST(Parallel_Operations_MPI, 10_15) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int width = 15;
    int height = 10;
    int* img = new int[width* height];
    if (rank == 0) {
        img = getRandomArr(width, height);
    }
    int *new_img_p = get_Parallel_lin_hist(img, width, height);
    if (rank == 0) {
        int min = get_local_min(img, width, height);
        int max = get_local_max(img, width, height);
        int* new_img_s = get_Sequential_lin_hist(img, width, height, min, max);
        /*for (int i = 0; i < width * height; i++) {
            std::cout << new_img_s[i] << " ";
        }
        std::cout << std::endl;*/
        for (int i = 0; i < width * height; i++) {
            ASSERT_EQ(new_img_p[i], new_img_s[i]);
        }
    }
}
TEST(Parallel_Operations_MPI, 100_150) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int width = 150;
    int height = 100;
    int* img = new int[width * height];
    if (rank == 0) {
        img = getRandomArr(width, height);
    }
    int* new_img_p = get_Parallel_lin_hist(img, width, height);
    if (rank == 0) {
        int min = get_local_min(img, width, height);
        int max = get_local_max(img, width, height);

        int* new_img_s = get_Sequential_lin_hist(img, width, height, min, max);
        for (int i = 0; i < width * height; i++) {
            ASSERT_EQ(new_img_p[i], new_img_s[i]);
        }
    }
}
TEST(Parallel_Operations_MPI, 300_300) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int width = 300;
    int height = 300;
    int* img = new int[width * height];
    if (rank == 0) {
        img = getRandomArr(width, height);
    }
    int* new_img_p = get_Parallel_lin_hist(img, width, height);
    if (rank == 0) {
        int min = get_local_min(img, width, height);
        int max = get_local_max(img, width, height);

        int* new_img_s = get_Sequential_lin_hist(img, width, height, min, max);
        for (int i = 0; i < width * height; i++) {
            ASSERT_EQ(new_img_p[i], new_img_s[i]);
        }
    }
}
TEST(Parallel_Operations_MPI, 500_700) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int width = 500;
    int height = 700;
    int* img = new int[width * height];
    if (rank == 0) {
        img = getRandomArr(width, height);
    }
    int* new_img_p = get_Parallel_lin_hist(img, width, height);
    if (rank == 0) {
        int min = get_local_min(img, width, height);
        int max = get_local_max(img, width, height);

        int* new_img_s = get_Sequential_lin_hist(img, width, height, min, max);
        for (int i = 0; i < width * height; i++) {
            ASSERT_EQ(new_img_p[i], new_img_s[i]);
        }
    }
}
TEST(Parallel_Operations_MPI, 1000_1500) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int width = 1500;
    int height = 1000;
    int* img = new int[width * height];
    if (rank == 0) {
        img = getRandomArr(width, height);
    }
    int* new_img_p = get_Parallel_lin_hist(img, width, height);
    if (rank == 0) {
        int min = get_local_min(img, width, height);
        int max = get_local_max(img, width, height);

        int* new_img_s = get_Sequential_lin_hist(img, width, height, min, max);
        for (int i = 0; i < width * height; i++) {
            ASSERT_EQ(new_img_p[i], new_img_s[i]);
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
