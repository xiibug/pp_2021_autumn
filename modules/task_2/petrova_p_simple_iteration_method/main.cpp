// Copyright 2021 Petrova Polina
#include <gtest/gtest.h>
#include <vector>
#include "./simple_iteration_method.h"
#include <gtest-mpi-listener.hpp>


TEST(simple_iteration, can_create_random_vector_0) {
    std::vector<double> a = fillRandomVector(100);
    ASSERT_NO_THROW();
}
TEST(simple_iteration, can_create_random_vector_1) {
    ASSERT_ANY_THROW(std::vector<double> a = fillRandomVector(-777));
}
TEST(simple_iteration, can_create_random_matrix_0) {
    std::vector< std::vector<double> > a = fillRandomMatrix(100);
    ASSERT_NO_THROW();
}
TEST(simple_iteration, can_create_random_matrix_1) {
    ASSERT_ANY_THROW(std::vector< std::vector<double> > a =
        fillRandomMatrix(-777));
}
TEST(simple_iteration, test_0) {
    std::vector< std::vector<double>> A{
        {4, 1, 1},
        {1, 6, -1},
        {1, 2, 5}
    };
    std::vector<double> b{ 9, 10, 20 };
    std::vector<double> x;
    std::vector<double> ans{ 1.0001, 2, 3.0001 };
    x = seqMethod(A, b, 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE((x[i] - ans[i]) < 0.0001);
    }
}
TEST(simple_iteration, test_1) {
    std::vector< std::vector<double>> A{
        {4, 1, 1},
        {1, 6, -1},
        {1, 2, 5}
    };
    std::vector<double> b{ 9, 10, 20 };
    std::vector<double> ans{ 1.0001, 2, 3.0001 };
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    double eps = 0.0001;
    std::vector<double> x = parallelMethod(A, b, 3);
    if (procRank == 0) {
        for (int i = 0; i < 3; i++) {
            EXPECT_TRUE((x[i] - ans[i]) < eps);
        }
    }
}
TEST(simple_iteration, test_2) {
    std::vector< std::vector<double>> A{
    {4, 1, 1},
    {1, 6, -1},
    {1, 2, 5}
    };
    std::vector<double> b{ 9, 10, 20 };
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<double> x = parallelMethod(A, b, 3);
    if (procRank == 0) {
        std::vector<double> seqX = seqMethod(A, b, 3);
        EXPECT_EQ(x, seqX);
    }
}
TEST(simple_iteration, test_3) {
    std::vector< std::vector<double> >A;
    std::vector<double> b;
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        A = fillRandomMatrix(5);
        b = fillRandomVector(5);
    }
    std::vector<double> x = parallelMethod(A, b, 3);
    if (procRank == 0) {
        EXPECT_NO_THROW();
    }
}
TEST(simple_iteration, test_4) {
    std::vector< std::vector<double> >A;
    std::vector<double> b;
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        A = fillRandomMatrix(33);
        b = fillRandomVector(33);
    }
    std::vector<double> x = parallelMethod(A, b, 3);
    if (procRank == 0) {
        std::vector<double> xSeq = seqMethod(A, b, 3);
        EXPECT_EQ(x, xSeq);
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
