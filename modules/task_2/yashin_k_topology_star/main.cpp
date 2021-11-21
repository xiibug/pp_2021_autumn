// Copyright 2021 Yashin Kirill

#include <gtest/gtest.h>
#include "./topology_star.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_0_send_random) {
    int rank, size, sender, reciever;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm newcomm = Star(size);

    if (size == 1) {
        ASSERT_EQ(1, 1);
    } else {
        sender = 0;
        reciever = getRand(1, size - 1);
        int s = 100500;
        int r;
        if (rank == sender) {
            MPI_Send(&s, 1, MPI_INT, reciever, 0, newcomm);
        }
        if (rank == reciever) {
            MPI_Recv(&r, 1, MPI_INT, sender, 0, newcomm, MPI_STATUS_IGNORE);
            ASSERT_EQ(s, r);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_rand_send_to_center) {
    int rank, size, sender, reciever;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm newcomm = Star(size);

    if (size == 1) {
        ASSERT_EQ(1, 1);
    } else {
        sender = getRand(1, size - 1);
        reciever = 0;
        int s = 70;
        int r;
        if (rank == sender) {
            MPI_Send(&s, 1, MPI_INT, reciever, 0, newcomm);
        }
        if (rank == reciever) {
            MPI_Recv(&r, 1, MPI_INT, sender, 0, newcomm, MPI_STATUS_IGNORE);
            ASSERT_EQ(s, r);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_send_to_1_from_random) {
    int rank, size, sender, reciever;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm newcomm = Star(size);

    if ((size == 1) || (size == 2)) {
        ASSERT_EQ(1, 1);
    } else {
        sender = getRand(2, size - 1);
        reciever = 1;
        int s = 533;
        int r;
        if (rank == sender) {
            MPI_Send(&s, 1, MPI_INT, reciever, 0, newcomm);
        }
        if (rank == reciever) {
            MPI_Recv(&r, 1, MPI_INT, sender, 0, newcomm, MPI_STATUS_IGNORE);
            ASSERT_EQ(s, r);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_0_send_random_double) {
    int rank, size, sender, reciever;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm newcomm = Star(size);

    if (size == 1) {
        ASSERT_EQ(1, 1);
    } else {
        sender = 0;
        reciever = getRand(1, size - 1);
        double s = 777.777;
        double r;
        if (rank == sender) {
            MPI_Send(&s, 1, MPI_DOUBLE, reciever, 0, newcomm);
        }
        if (rank == reciever) {
            MPI_Recv(&r, 1, MPI_DOUBLE, sender, 0, newcomm, MPI_STATUS_IGNORE);
            ASSERT_EQ(s, r);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_0_send_random_char) {
    int rank, size, sender, reciever;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm newcomm = Star(size);

    if (size == 1) {
        ASSERT_EQ(1, 1);
    } else {
        sender = 0;
        reciever = getRand(1, size - 1);
        char s = 'x';
        char r;
        if (rank == sender) {
            MPI_Send(&s, 1, MPI_CHAR, reciever, 0, newcomm);
        }
        if (rank == reciever) {
            MPI_Recv(&r, 1, MPI_CHAR, sender, 0, newcomm, MPI_STATUS_IGNORE);
            ASSERT_EQ(s, r);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_send_char_to_1_from_random) {
    int rank, size, sender, reciever;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm newcomm = Star(size);

    if (size == 1) {
        ASSERT_EQ(1, 1);
    } else {
        sender = getRand(2, size - 1);
        reciever = 1;
        char s = 'y';
        char r;
        if (rank == sender) {
            MPI_Send(&s, 1, MPI_CHAR, reciever, 0, newcomm);
        }
        if (rank == reciever) {
            MPI_Recv(&r, 1, MPI_CHAR, sender, 0, newcomm, MPI_STATUS_IGNORE);
            ASSERT_EQ(s, r);
        }
    }
}

TEST(Parallel_Operations_MPI, Test_send_char_to_0_from_random) {
    int rank, size, sender, reciever;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm newcomm = Star(size);

    if (size == 1) {
        ASSERT_EQ(1, 1);
    } else {
        sender = getRand(1, size - 1);
        reciever = 0;
        char s = 'y';
        char r;
        if (rank == sender) {
            MPI_Send(&s, 1, MPI_CHAR, reciever, 0, newcomm);
        }
        if (rank == reciever) {
            MPI_Recv(&r, 1, MPI_CHAR, sender, 0, newcomm, MPI_STATUS_IGNORE);
            ASSERT_EQ(s, r);
        }
    }
}

int main(int argc, char**argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
