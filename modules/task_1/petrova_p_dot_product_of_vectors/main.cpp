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
    const int len = 120;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<int> a(len, 2), b(len, 1);
    int res = parallelScalMult(a, b, len);
    a.clear();
    b.clear();
    if (procRank == 0) {
        ASSERT_EQ(res, 240);
    }
}

TEST(ScaulMult_Vectors_MPI, test_3) {
    int procRank;
    const int len = 120;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<int> a(len, 2), b(len, 1);
    int res = parallelScalMult(a, b, len);
    a.clear();
    b.clear();
    if (procRank == 0) {
        ASSERT_NE(res, 100);
    }
}

TEST(ScaulMult_Vectors_MPI, test_4) {
    int procRank;
    int seqRec;
    const int len = 120;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<int> a(len, 2), b(len, 1);
    int res = parallelScalMult(a, b, len);
    if (procRank == 0) {
        seqRec = sequentialScalMult(a, b, len);
    }
    a.clear();
    b.clear();
    if (procRank == 0) {
        ASSERT_EQ(res, seqRec);
    }
}
TEST(ScaulMult_Vectors_MPI, test_5) {
    int procRank;
    int seqRec;
    const int len = 777;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::vector<int> a(len, 2), b(len, 1);
    int res = parallelScalMult(a, b, len);
    if (procRank == 0) {
        seqRec = sequentialScalMult(a, b, len);
    }
    a.clear();
    b.clear();
    if (procRank == 0) {
        ASSERT_EQ(res, seqRec);
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
