// Copyright 2021 Novozhilov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./star_topology.h"
#include <gtest-mpi-listener.hpp>




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::vector<int> result1;
    std::vector<int> result2;
    MPI_Init(&argc, &argv);
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();
    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
