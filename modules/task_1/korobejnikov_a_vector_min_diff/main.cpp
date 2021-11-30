// Copyright 2021 Korobejnikov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./vector_min_diff.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_even_count) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 100;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_even_count_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 120;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_uneven_count) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 111;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_uneven_count_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 99;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_uneven_count_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 77;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_even_count_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 86;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_7) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 9;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_8) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 11;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_9) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 10;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_10) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 24;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    int globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        int reference_min = sequentialCount(global_vec);
        ASSERT_EQ(globalMin, reference_min);
    }
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing
        ::UnitTest::GetInstance()->listeners();
    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
