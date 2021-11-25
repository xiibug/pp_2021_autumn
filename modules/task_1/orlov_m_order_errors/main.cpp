

#include <gtest/gtest.h>
#include "./order_errors.h"
#include <gtest-mpi-listener.hpp>

TEST(MPI, small_sorted_vector) {
    std::vector<int> v = { 1, 3, 5 };
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0)
        ASSERT_EQ(orderErrors(v), 0);
}

TEST(MPI, large_sorted_vector) {
    std::vector<int> v;
    for (int i = 0; i < 1000; i++)
        v.push_back(i);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    ASSERT_EQ(orderErrors(v), 0);
}

TEST(MPI, unsorted_vector) {
    std::vector<int> v = { 5, 2, 6, 13, 7, 9 };
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    ASSERT_EQ(orderErrors(v), 2); //2
}

TEST(MPI, large_unsorted_vector) {
    std::vector<int> v;
    for (int i = 0; i < 1000; i++)
        v.push_back(1000 - i);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    ASSERT_EQ(orderErrors(v), 999);
}

TEST(MPI, empty_vector) {
    std::vector<int> v;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    ASSERT_EQ(orderErrors(v), 0);
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