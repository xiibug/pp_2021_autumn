// Copyright 2021 Lakhov Kirill
#include <gtest/gtest.h>
#include <vector>
#include "./simple_iteration.h"
#include <gtest-mpi-listener.hpp>
#include <iostream>

TEST(Parallel_Operations_MPI, Test_Diff2) {

}
TEST(Parallel_Operations_MPI, Test_Diff3) {

}
TEST(Parallel_Operations_MPI, Test_Diff4) {

}
TEST(Parallel_Operations_MPI, Test_Diff5) {

}
TEST(Parallel_Operations_MPI, Test_Diff6) {

}

int main(int argc, char** argv) {
    // ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    // ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    // ::testing::TestEventListeners& listeners =
    //     ::testing::UnitTest::GetInstance()->listeners();

    // listeners.Release(listeners.default_result_printer());
    // listeners.Release(listeners.default_xml_generator());

    // listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    // return RUN_ALL_TESTS();
    // std::vector<std::vector<double>> v = getRandomMatrix(5);
    // std::vector<double> b = getRandomVector(5, -20, 20);
    // printMatrix(v, 5);

    std::vector<std::vector<double>> v = {{10, 3, -3}, {5, 10, -4}, {-2, 2, 10}};
    std::vector<double> b = {7,8,9};
    // sequentialCalc(v, b, 3);
    parallelCalc(v, b, 3);
    MPI_Finalize();
 }
