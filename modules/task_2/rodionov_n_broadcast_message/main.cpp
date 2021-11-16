// Copyright 2021 TexHik620953
#include <mpi.h>
#include <gtest/gtest.h>
#include <vector>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_2/rodionov_n_broadcast_message/broadcast_message.h"
int length = 1000;
int root = 1;

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


TEST(BroadCastTest, DoubleSum) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Create matrix
    double* linear_matrix = nullptr;
    double seq_sum = 0;
    double mpi_result = 0;
    if (rank == root) {
        linear_matrix = new double[commSize * length];
        for (int i = 0; i < commSize * length; i++) {
            linear_matrix[i] = static_cast<double>(randint(0, 100)) / 100;
            seq_sum += linear_matrix[i];
        }
    }
    BroadcastSum(linear_matrix, &mpi_result, length, root, MPI_SUM, MPI_DOUBLE);
    if (rank == root) {
        EXPECT_NEAR(mpi_result, seq_sum, 1e-2);
        delete[] linear_matrix;
    }
}
TEST(BroadCastTest, DoubleMax) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Create matrix
    double* linear_matrix = nullptr;
    double seq_max = 0;
    double mpi_result = 0;
    if (rank == root) {
        linear_matrix = new double[commSize * length];
        for (int i = 0; i < commSize * length; i++) {
            linear_matrix[i] = static_cast<double>(randint(0, 100)) / 100;
            if (linear_matrix[i] > seq_max) {
                seq_max = linear_matrix[i];
            }
        }
    }
    BroadcastSum(linear_matrix, &mpi_result, length, root, MPI_MAX, MPI_DOUBLE);
    if (rank == root) {
        EXPECT_NEAR(mpi_result, seq_max, 1e-2);
        delete[] linear_matrix;
    }
}


TEST(BroadCastTest, FloatSum) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Create matrix
    float* linear_matrix = nullptr;
    float seq_sum = 0;
    float mpi_result = 0;
    if (rank == root) {
        linear_matrix = new float[commSize * length];
        for (int i = 0; i < commSize * length; i++) {
            linear_matrix[i] = static_cast<float>(randint(0, 100)) / 100;
            seq_sum += linear_matrix[i];
        }
    }
    BroadcastSum(linear_matrix, &mpi_result, length, root, MPI_SUM, MPI_FLOAT);
    if (rank == root) {
        EXPECT_NEAR(mpi_result, seq_sum, 1e-1);
        delete[] linear_matrix;
    }
}
TEST(BroadCastTest, FloatMax) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Create matrix
    float* linear_matrix = nullptr;
    float seq_max = 0;
    float mpi_result = 0;
    if (rank == root) {
        linear_matrix = new float[commSize * length];
        for (int i = 0; i < commSize * length; i++) {
            linear_matrix[i] = static_cast<float>(randint(0, 100)) / 100;
            if (linear_matrix[i] > seq_max) {
                seq_max = linear_matrix[i];
            }
        }
    }
    BroadcastSum(linear_matrix, &mpi_result, length, root, MPI_MAX, MPI_FLOAT);
    if (rank == root) {
        EXPECT_NEAR(mpi_result, seq_max, 1e-1);
        delete[] linear_matrix;
    }
}

TEST(BroadCastTest, IntSum) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Create matrix
    int* linear_matrix = nullptr;
    int seq_sum = 0;
    int mpi_result = 0;
    if (rank == root) {
        linear_matrix = new int[commSize * length];
        for (int i = 0; i < commSize * length; i++) {
            linear_matrix[i] = randint(0, 100);
            seq_sum += linear_matrix[i];
        }
    }
    BroadcastSum(linear_matrix, &mpi_result, length, root, MPI_SUM, MPI_INT);
    if (rank == root) {
        EXPECT_EQ(mpi_result, seq_sum);
        delete[] linear_matrix;
    }
}
TEST(BroadCastTest, IntMax) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Create matrix
    int* linear_matrix = nullptr;
    int seq_max = 0;
    int mpi_result = 0;
    if (rank == root) {
        linear_matrix = new int[commSize * length];
        for (int i = 0; i < commSize * length; i++) {
            linear_matrix[i] = randint(0, 100);
            if (linear_matrix[i] > seq_max) {
                seq_max = linear_matrix[i];
            }
        }
    }
    BroadcastSum(linear_matrix, &mpi_result, length, root, MPI_MAX, MPI_INT);
    if (rank == root) {
        EXPECT_EQ(mpi_result, seq_max);
        delete[] linear_matrix;
    }
}
