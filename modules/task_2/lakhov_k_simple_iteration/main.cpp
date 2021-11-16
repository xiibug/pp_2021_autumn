// Copyright 2021 Lakhov Kirill
#include <gtest/gtest.h>
#include <vector>
#include "./simple_iteration.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Predifined1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 3;
    double eps = 0.0001;
    std::vector<std::vector<double>> v;
    std::vector<double> b;

    if (rank == 0) {
        v = {{10, 3, -3}, {5, 10, -4}, {-2, 2, 10}};
        b = {7, 8, 9};
    }

    std::vector<double> p_result = parallelCalc(v, b, size);
    if (rank == 0) {
        std::vector<double> s_result = sequentialCalc(v, b, size);
        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(std::abs(p_result[i] - s_result[i]) < eps);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Predifined2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 3;
    double eps = 0.0001;
    std::vector<std::vector<double>> v;
    std::vector<double> b;

    if (rank == 0) {
        v = {{15, 5, 6}, {11, 33, -8}, {-3, 3, 9}};
        b = {9, 8, 7};
    }

    std::vector<double> p_result = parallelCalc(v, b, size);
    if (rank == 0) {
        std::vector<double> s_result = sequentialCalc(v, b, size);
        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(std::abs(p_result[i] - s_result[i]) < eps);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Random1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 5;
    double eps = 0.0001;
    std::vector<std::vector<double>> v;
    std::vector<double> b;

    if (rank == 0) {
        v = getRandomMatrix(size);
        b = getRandomVector(size, -10, 10);
    }

    std::vector<double> p_result = parallelCalc(v, b, size);
    if (rank == 0) {
        std::vector<double> s_result = sequentialCalc(v, b, size);
        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(std::abs(p_result[i] - s_result[i]) < eps);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Random2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 6;
    double eps = 0.0001;
    std::vector<std::vector<double>> v;
    std::vector<double> b;

    if (rank == 0) {
        v = getRandomMatrix(size);
        b = getRandomVector(size, -10, 10);
    }

    std::vector<double> p_result = parallelCalc(v, b, size);
    if (rank == 0) {
        std::vector<double> s_result = sequentialCalc(v, b, size);
        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(std::abs(p_result[i] - s_result[i]) < eps);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_Random3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 6;
    double eps = 0.0001;
    std::vector<std::vector<double>> v;
    std::vector<double> b;

    if (rank == 0) {
        v = getRandomMatrix(size);
        b = getRandomVector(size, -10, 10);
    }

    std::vector<double> p_result = parallelCalc(v, b, size);
    if (rank == 0) {
        std::vector<double> s_result = sequentialCalc(v, b, size);
        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(std::abs(p_result[i] - s_result[i]) < eps);
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
