// Copyright 2021 TexHik620953
#include <gtest/gtest.h>
#include "./quicksort.h"
#include <gtest-mpi-listener.hpp>
int length = 5000;

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);  // check for MPI_SUCCESS?

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}



TEST(QuickSort, CheckOrderingPositiveTest) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int* arr = new int[length];
        for (int i = 0; i < length; i++) {
            arr[i] = i;
        }
        EXPECT_TRUE(CheckOrdering(arr, length));
        delete[] arr;
    }
}

TEST(QuickSort, CheckOrderingNegativeTest) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int* arr = new int[length];
        for (int i = 0; i < length; i++) {
            arr[i] = i;
        }
        arr[length - 1] = 0;
        arr[length - 2] = 1;
        EXPECT_FALSE(CheckOrdering(arr, length));
        delete[] arr;
    }
}




TEST(QuickSort, SequentialSortCheck) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int* arr = new int[length];
        RandomArray(arr, length);
        LinearSortSeq(arr, length);
        EXPECT_TRUE(CheckOrdering(arr, length));
        delete[] arr;
    }
}

TEST(QuickSort, SortsEqualsTest) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* arr = nullptr;
    int* arr2 = nullptr;
    if (rank == 0) {
        arr = new int[length];
        arr2 = new int[length];
        RandomArray(arr, length);
        memcpy(arr2, arr, sizeof(int) * length);
    }

    QuickSortMpi(arr, length);

    if (rank == 0) {
        LinearSortSeq(arr2, length);
        for (int i = 0; i < length; i++) {
            EXPECT_EQ(arr[i], arr2[i]);
        }
        delete[] arr;
        delete[] arr2;
    }
}


TEST(QuickSort, MpiSort) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* arr = nullptr;
    if (rank == 0) {
        arr = new int[length];
        RandomArray(arr, length);
    }

    QuickSortMpi(arr, length);

    if (rank == 0) {
        EXPECT_TRUE(CheckOrdering(arr, length));
        delete[] arr;
    }
}
