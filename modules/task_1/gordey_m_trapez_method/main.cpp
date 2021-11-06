// Copyright 2021 Gordey  Maria
#include <gtest/gtest.h>
#include <functional>
#include <cmath>
#include "./trapez_method.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, x_squared) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int a = 0, b = 10, n = 100;
    const std::function<double(double)> f = [](double x) { return x * x; };

    double global_sum = getParallelOperations(a, b, n, f);

    if (rank == 0) {
        double reference_sum = getSequentialOperations(a, b, n, f);
        ASSERT_DOUBLE_EQ(reference_sum, global_sum);
    }
}
TEST(Parallel_Operations_MPI, x_cube) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a = 0, b = 10, n = 100;
    const std::function<double(double)> f = [](double x) { return x * x * x; };

    double global_sum = getParallelOperations(a, b, n, f);

    if (rank == 0) {
        double reference_sum = getSequentialOperations(a, b, n, f);
        ASSERT_DOUBLE_EQ(reference_sum, global_sum);
    }
}
TEST(Parallel_Operations_MPI, x_sin) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a = 0, b = 10, n = 100;
    const std::function<double(double)> f = [](double x) { return sin(x); };

    double global_sum = getParallelOperations(a, b, n, f);

    if (rank == 0) {
        double reference_sum = getSequentialOperations(a, b, n, f);
        ASSERT_DOUBLE_EQ(reference_sum, global_sum);
    }
}
TEST(Parallel_Operations_MPI, x_polynom) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a = 0, b = 10, n = 100;
    const std::function<double(double)> f =
        [](double x) { return x * x - 5 * x + 4; };

    double global_sum = getParallelOperations(a, b, n, f);

    if (rank == 0) {
        double reference_sum = getSequentialOperations(a, b, n, f);
        ASSERT_DOUBLE_EQ(reference_sum, global_sum);
    }
}
TEST(Parallel_Operations_MPI, x_cos) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a = 0, b = 10, n = 100;
    const std::function<double(double)> f = [](double x) { return cos(x); };

    double global_sum = getParallelOperations(a, b, n, f);

    if (rank == 0) {
        double reference_sum = getSequentialOperations(a, b, n, f);
        ASSERT_DOUBLE_EQ(reference_sum, global_sum);
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
