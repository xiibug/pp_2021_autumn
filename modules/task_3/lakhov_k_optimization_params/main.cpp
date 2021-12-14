// Copyright 2021 Lakhov Kirill
#define _USE_MATH_DEFINES

#include <gtest/gtest.h>
#include <iostream>
#include "./optimization_params.h"
#include <gtest-mpi-listener.hpp>

TEST(Global_Optimization_MPI, Test_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double left_x = -1;
    double right_x = 1;
    double left_y = -2;
    double right_y = 2;
    Point parallel_result = parralelCalc(left_x, right_x, left_y, right_y, f1);
    if (rank == 0) {
        Point seq_result = sequentialCalc(left_x, right_x, left_y, right_y, f1);
        std::cout<<"Parallel result: ("<<parallel_result.x<<" "<<
        parallel_result.y<<" "<<parallel_result.z<<")"<<std::endl;
        std::cout<<"Sequental result: ("<<seq_result.x<<" "<<
        seq_result.y<<" "<<seq_result.z<<")"<<std::endl;
        ASSERT_TRUE(parallel_result == seq_result);
    }
}

TEST(Global_Optimization_MPI, Test_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double left_x = -1;
    double right_x = 1;
    double left_y = -2;
    double right_y = 2;
    Point parallel_result = parralelCalc(left_x, right_x, left_y, right_y, f2);
    if (rank == 0) {
        Point seq_result = sequentialCalc(left_x, right_x, left_y, right_y, f2);
        std::cout<<"Parallel result: ("<<parallel_result.x<<" "<<
        parallel_result.y<<" "<<parallel_result.z<<")"<<std::endl;
        std::cout<<"Sequental result: ("<<seq_result.x<<" "<<
        seq_result.y<<" "<<seq_result.z<<")"<<std::endl;
        ASSERT_TRUE(parallel_result == seq_result);
    }
}

TEST(Global_Optimization_MPI, Test_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double left_x = 0.5;
    double right_x = 2;
    double left_y = 0.5;
    double right_y = 2;
    Point parallel_result = parralelCalc(left_x, right_x, left_y, right_y, f3);
    if (rank == 0) {
        Point seq_result = sequentialCalc(left_x, right_x, left_y, right_y, f3);
        std::cout<<"Parallel result: ("<<parallel_result.x<<" "<<
        parallel_result.y<<" "<<parallel_result.z<<")"<<std::endl;
        std::cout<<"Sequental result: ("<<seq_result.x<<" "<<
        seq_result.y<<" "<<seq_result.z<<")"<<std::endl;
        ASSERT_TRUE(parallel_result == seq_result);
    }
}

TEST(Global_Optimization_MPI, Test_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double left_x = 0;
    double right_x = 2;
    double left_y = 0;
    double right_y = 2;
    Point parallel_result = parralelCalc(left_x, right_x, left_y, right_y, f4);
    if (rank == 0) {
        Point seq_result = sequentialCalc(left_x, right_x, left_y, right_y, f4);
        std::cout<<"Parallel result: ("<<parallel_result.x<<" "<<
        parallel_result.y<<" "<<parallel_result.z<<")"<<std::endl;
        std::cout<<"Sequental result: ("<<seq_result.x<<" "<<
        seq_result.y<<" "<<seq_result.z<<")"<<std::endl;
        ASSERT_TRUE(parallel_result == seq_result);
    }
}

TEST(Global_Optimization_MPI, Test_5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double left_x = -1.5;
    double right_x = 1;
    double left_y = 0;
    double right_y = 1.5;
    Point parallel_result = parralelCalc(left_x, right_x, left_y, right_y, f5);
    if (rank == 0) {
        Point seq_result = sequentialCalc(left_x, right_x, left_y, right_y, f5);
        std::cout<<"Parallel result: ("<<parallel_result.x<<" "<<
        parallel_result.y<<" "<<parallel_result.z<<")"<<std::endl;
        std::cout<<"Sequental result: ("<<seq_result.x<<" "<<
        seq_result.y<<" "<<seq_result.z<<")"<<std::endl;
        ASSERT_TRUE(parallel_result == seq_result);
    }
}

// Test for time measure
// TEST(Global_Optimization_MPI, Test_6) {
//     int rank;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     double left_x = -1;
//     double right_x = 2;
//     double left_y = -2;
//     double right_y = 2;
//     double time1, time2, delta1, delta2;
//     if(rank == 0){
//         time1 = MPI_Wtime();
//     }
//     Point parallel_result = parralelCalc(left_x, right_x,
//     left_y, right_y, f1);
//     if(rank == 0){
//         time2 = MPI_Wtime();
//         delta1 = time2 - time1;
//         std::cout<<"Parallel time "<<delta1<<std::endl;
//         time1 = MPI_Wtime();
//         Point seq_result = sequentialCalc(left_x, right_x,
//         left_y, right_y, f1);
//         time2 = MPI_Wtime();
//         delta2 = time2 - time1;
//         std::cout<<"Sequental time "<<delta2<<std::endl;
//         std::cout<<"sequental/parallel ratio "<<delta2/delta1<<std::endl;
//         ASSERT_TRUE(parallel_result == seq_result);
//     }
// }

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
    // double left_x = 0.5;
    // double right_x = 2;
    // double left_y = 0.5;
    // double right_y = 2;
    // parralelCalc(left_x, right_x, left_y, right_y, f3);
    // MPI_Finalize();
    return 0;
}
