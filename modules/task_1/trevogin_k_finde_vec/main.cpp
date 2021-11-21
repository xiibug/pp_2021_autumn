// Copyright 2021 Trevogin Kirill

#include "./finde_vec.h"

TEST(Parallel_Operations_MPI, Test_Vec_Size_0) {
    int Rank, res, res1;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    std::vector<int> vec;

    if (Rank == 0)
        vec = getRandomVector(0);

    res = getFindeOrderedElementsParall(vec, vec.size());

    if (Rank == 0) {
        res1 = getFindeOrderedElements(vec);
        ASSERT_EQ(res1, res);
    }
}
TEST(Parallel_Operations_MPI, Test_Vec_Size_1) {
    int Rank, res, res1;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    std::vector<int> vec;

    if (Rank == 0)
        vec = getRandomVector(1);

    res = getFindeOrderedElementsParall(vec, vec.size());

    if (Rank == 0) {
        res1 = getFindeOrderedElements(vec);
        ASSERT_EQ(res1, res);
    }
}
TEST(Parallel_Operations_MPI, Test_Vec_Size_5) {
    int Rank, res, res1;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    std::vector<int> vec;

    if (Rank == 0)
        vec = getRandomVector(5);

    res = getFindeOrderedElementsParall(vec, vec.size());

    if (Rank == 0) {
        res1 = getFindeOrderedElements(vec);
        ASSERT_EQ(res1, res);
    }
}
TEST(Parallel_Operations_MPI, Test_Vec_Size_20) {
    int Rank, res, res1;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    std::vector<int> vec;

    if (Rank == 0)
        vec = getRandomVector(20);

    res = getFindeOrderedElementsParall(vec, vec.size());

    if (Rank == 0) {
        res1 = getFindeOrderedElements(vec);
        ASSERT_EQ(res1, res);
    }
}
TEST(Parallel_Operations_MPI, Test_Vec_Size_60) {
    int Rank, res, res1;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    std::vector<int> vec;

    if (Rank == 0)
        vec = getRandomVector(60);

    res = getFindeOrderedElementsParall(vec, vec.size());

    if (Rank == 0) {
        res1 = getFindeOrderedElements(vec);
        ASSERT_EQ(res1, res);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
