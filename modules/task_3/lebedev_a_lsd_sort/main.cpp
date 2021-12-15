// Copyright 2021 Lebedev Alexey
#include <gtest/gtest.h>
#include "./lsd_sort.h"
#include <gtest-mpi-listener.hpp>


TEST(Jacobi_iterations_MPI, Test_1) {
}


TEST(Jacobi_iterations_MPI, Test_2) {
}


TEST(Jacobi_iterations_MPI, Test_3) {
}


TEST(Jacobi_iterations_MPI, Test_4) {
}


TEST(Jacobi_iterations_MPI, Test_5) {
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
