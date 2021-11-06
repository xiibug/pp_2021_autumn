// Copyright 2021 Novozhilov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./max_values_in_columns.h"
#include <gtest-mpi-listener.hpp>



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto matrix = getRandomMatrix(2, 5);
    std::vector<int> result1;
    std::vector<int> result2;
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    
    
    result1 = maxValuesInColumnsParallel(matrix, 2, 5);
    
    //return RUN_ALL_TESTS();
    
    result2 = maxValuesInColumnsSequential(matrix);
    printMatrix(matrix);
    printVector(result1);
    printVector(result2);

    return 0;
}
