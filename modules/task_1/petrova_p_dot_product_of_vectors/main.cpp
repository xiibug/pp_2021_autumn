// Copyright 2021 Petrova Polina
#include <gtest/gtest.h>
#include <vector>
#include "./dot_product_of_vectors.h"
#include <gtest-mpi-listener.hpp>

TEST(ScaulMult_Vectors_MPI, can_create_random_vector_0) {
    std::vector<int> a = fillRandomVector(100);
    ASSERT_NO_THROW();
}

TEST(ScaulMult_Vectors_MPI, can_create_random_vector_1) {
    ASSERT_ANY_THROW(std::vector<int> a = fillRandomVector(-7));
}

TEST(ScaulMult_Vectors_MPI, test_0) {
    std::vector<int> a(100, 2), b(100, 1);
    int res;
    res = sequentialScalMult(a, b, 100);
    ASSERT_EQ(res, 200);
}

TEST(ScaulMult_Vectors_MPI, test_1) {
    std::vector<int> a(100, 2), b(100, 1);
    int res;
    res = sequentialScalMult(a, b, 100);
    ASSERT_NE(res, 100);
}

TEST(ScaulMult_Vectors_MPI, test_2) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<int> a(100, 2), b(100, 1);
    int res = parallelScalMult(a, b, 100);
    a.clear();
    b.clear();
    if (procRank == 0) {
        ASSERT_EQ(res, 200);
    }
}

TEST(ScaulMult_Vectors_MPI, test_3) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<int> a(100, 2), b(100, 1);
    int res = parallelScalMult(a, b, 100);
    a.clear();
    b.clear();
    if (procRank == 0) {
        ASSERT_NE(res, 100);
    }
}

TEST(ScaulMult_Vectors_MPI, test_4) {
    int procRank;
    int seqSum;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    const int lenght = 100;
    std::vector<int> a;
    std::vector<int> b;

    if (procRank == 0) {
        a = fillRandomVector(lenght);
        b = fillRandomVector(lenght);
    }
    int sum = parallelScalMult(a, b, lenght);

    if (procRank == 0) {
        seqSum = sequentialScalMult(a, b, lenght);
    }

    a.clear();
    b.clear();

    if (procRank == 0) {
        EXPECT_EQ(seqSum, sum);
    }
}

TEST(ScaulMult_Vectors_MPI, test_5) {
    int procRank;
    int seqSum;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    const int lenght = 10000;
    std::vector<int> a;
    std::vector<int> b;

    if (procRank == 0) {
        a = fillRandomVector(lenght);
        b = fillRandomVector(lenght);
    }
    int sum = parallelScalMult(a, b, lenght);

    if (procRank == 0) {
        seqSum = sequentialScalMult(a, b, lenght);
    }

    a.clear();
    b.clear();

    if (procRank == 0) {
        EXPECT_EQ(seqSum, sum);
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
