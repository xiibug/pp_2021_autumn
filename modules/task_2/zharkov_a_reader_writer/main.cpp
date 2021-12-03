// Copyright 2021 Zharkov Andrey
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "./reader-writer_mpi.h"

TEST(reader_writer_MPI, all_R) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        work(rank, size);
    } else {
        reader(rank);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(reader_writer_MPI, firstproc_writer_left_readers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        work(rank, size);
    } else {
        if (rank == 1) {
            writer(rank);
        } else {
            reader(rank);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(reader_writer_MPI, firstproc_reader_left_writers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        work(rank, size);
    } else {
        if (rank == 1) {
            reader(rank);
        } else {
            writer(rank);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(reader_writer_MPI, all_W) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        work(rank, size);
    } else {
        writer(rank);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(reader_writer_MPI, writers_equal_readers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        work(rank, size);
    } else {
        if (rank % 2 == 0) {
            reader(rank);
        } else {
            writer(rank);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    std::srand(std::time(nullptr));

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
