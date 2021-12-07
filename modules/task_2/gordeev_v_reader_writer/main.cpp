// Copyright 2021 Gordeev Viktor
#include <gtest/gtest.h>
#include "./reader_writer_mpi.h"
#include <gtest-mpi-listener.hpp>

TEST(reader_writer_MPI, No_writers_readers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        library(rank, 1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(reader_writer_MPI, Only_readers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        library(rank, size);
    } else {
        reader(rank);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(reader_writer_MPI, One_writer_Many_readers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        library(rank, size);
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

TEST(reader_writer_MPI, One_reader_Many_writers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        library(rank, size);
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

TEST(reader_writer_MPI, Only_writers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        library(rank, size);
    } else {
        writer(rank);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    ASSERT_NO_THROW();
}

TEST(reader_writer_MPI, Nearly_Equal_writers_readers) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        library(rank, size);
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
