// Copyright 2021 Gordey Maria
#include <gtest/gtest.h>
#include "./ribbon_horizontal.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Matrix_Multiplication_MPI, A_2x2_B_2x2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* A = nullptr, * B = nullptr, * C = nullptr, * Cs = nullptr;
    int ARows = 2, ACols = 2, BRows = 2, BCols = 2;
    if (rank == 0) {
        A = getRandomMatrix(ARows, ACols);
        B = getRandomMatrix(BRows, BCols);
        C = initEmptyMatrix(ARows, BCols);
        Cs = initEmptyMatrix(ARows, BCols);
    }
    // double start = MPI_Wtime();
    ParallelMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, C);
    // double end = MPI_Wtime();
    // double ptime = end - start;
    if (rank == 0) {
        // start = MPI_Wtime();
        SequentialMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, Cs);
        // end = MPI_Wtime();
        // double stime = end - start;
        // std::cout << "The sequential process took " << stime
        //     << " seconds to run." << std::endl;
        // std::cout << "The parallel process took " << ptime
        //     << " seconds to run." << std::endl;
        // std::cout << "The speedup is " << stime - ptime
        //     << " seconds." << std::endl;
        bool flag = true;

        for (int i = 0; i < ARows * BCols; i++) {
            if (C[i] != Cs[i]) {
                flag = false;
            }
        }
        ASSERT_EQ(flag, true);
    }
}

TEST(Parallel_Matrix_Multiplication_MPI, A_4x3_B_3x2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* A = nullptr, * B = nullptr, * C = nullptr, * Cs = nullptr;
    int ARows = 4, ACols = 3, BRows = 3, BCols = 2;
    if (rank == 0) {
        A = getRandomMatrix(ARows, ACols);
        B = getRandomMatrix(BRows, BCols);
        C = initEmptyMatrix(ARows, BCols);
        Cs = initEmptyMatrix(ARows, BCols);
        // printf_s("Matrix A:\n");
        // for (int i = 0; i < ARows; i++) {
        //     for (int j = 0; j < ACols; j++) {
        //         printf_s("%d ", A[ACols * i + j]);
        //     }
        //     printf_s("\n");
        //     fflush(stdout);
        // }
        // printf_s("Matrix B:\n");
        // for (int i = 0; i < BRows; i++) {
        //     for (int j = 0; j < BCols; j++) {
        //         printf_s("%d ", B[BCols * i + j]);
        //     }
        //     printf_s("\n");
        //     fflush(stdout);
        // }
    }
    // double start = MPI_Wtime();
    ParallelMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, C);
    // double end = MPI_Wtime();
    // double ptime = end - start;
    if (rank == 0) {
        // start = MPI_Wtime();
        SequentialMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, Cs);
        // end = MPI_Wtime();
        // double stime = end - start;
        // std::cout << "The sequential process took " << stime
        //     << " seconds to run." << std::endl;
        // std::cout << "The parallel process took " << ptime
        //     << " seconds to run." << std::endl;
        // std::cout << "The speedup is " << stime - ptime
        //     << " seconds." << std::endl;
        // printf_s("Matrix C:\n");
        // for (int i = 0; i < ARows; i++) {
        //     for (int j = 0; j < BCols; j++) {
        //         printf_s("%d ", C[BCols * i + j]);
        //     }
        //     printf_s("\n");
        //     fflush(stdout);
        // }
        bool flag = true;
        // printf_s("Matrix Cs:\n");
        for (int i = 0; i < ARows; i++) {
            for (int j = 0; j < BCols; j++) {
                // printf_s("%d ", C[BCols * i + j]);
                if (C[BCols * i + j] != Cs[BCols * i + j]) {
                    flag = false;
                }
            }
            // printf_s("\n");
            // fflush(stdout);
        }
        ASSERT_EQ(flag, true);
    }
}

TEST(Parallel_Matrix_Multiplication_MPI, A_5x10_B_10x2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* A = nullptr, * B = nullptr, * C = nullptr, * Cs = nullptr;
    int ARows = 5, ACols = 10, BRows = 10, BCols = 2;
    if (rank == 0) {
        A = getRandomMatrix(ARows, ACols);
        B = getRandomMatrix(BRows, BCols);
        C = initEmptyMatrix(ARows, BCols);
        Cs = initEmptyMatrix(ARows, BCols);
    }
    // double start = MPI_Wtime();
    ParallelMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, C);
    // double end = MPI_Wtime();
    // double ptime = end - start;
    if (rank == 0) {
        // start = MPI_Wtime();
        SequentialMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, Cs);
        // end = MPI_Wtime();
        // double stime = end - start;
        // std::cout << "The sequential process took " << stime
        //     << " seconds to run." << std::endl;
        // std::cout << "The parallel process took " << ptime
        //     << " seconds to run." << std::endl;
        // std::cout << "The speedup is " << stime - ptime
        //     << " seconds." << std::endl;
        bool flag = true;

        for (int i = 0; i < ARows * BCols; i++) {
            if (C[i] != Cs[i]) {
                flag = false;
            }
        }
        ASSERT_EQ(flag, true);
    }
}

TEST(Parallel_Matrix_Multiplication_MPI, A_15x3_B_3x20) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* A = nullptr, * B = nullptr, * C = nullptr, * Cs = nullptr;
    int ARows = 15, ACols = 3, BRows = 3, BCols = 20;
    if (rank == 0) {
        A = getRandomMatrix(ARows, ACols);
        B = getRandomMatrix(BRows, BCols);
        C = initEmptyMatrix(ARows, BCols);
        Cs = initEmptyMatrix(ARows, BCols);
    }
    // double start = MPI_Wtime();
    ParallelMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, C);
    // double end = MPI_Wtime();
    // double ptime = end - start;
    if (rank == 0) {
        // start = MPI_Wtime();
        SequentialMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, Cs);
        // end = MPI_Wtime();
        // double stime = end - start;
        // std::cout << "The sequential process took " << stime
        //     << " seconds to run." << std::endl;
        // std::cout << "The parallel process took " << ptime
        //     << " seconds to run." << std::endl;
        // std::cout << "The speedup is " << stime - ptime
        //     << " seconds." << std::endl;
        bool flag = true;

        for (int i = 0; i < ARows * BCols; i++) {
            if (C[i] != Cs[i]) {
                flag = false;
            }
        }
        ASSERT_EQ(flag, true);
    }
}

TEST(Parallel_Matrix_Multiplication_MPI, A_500x100_B_100x300) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* A = nullptr, * B = nullptr, * C = nullptr, * Cs = nullptr;
    int ARows = 500, ACols = 100, BRows = 100, BCols = 300;
    if (rank == 0) {
        A = getRandomMatrix(ARows, ACols);
        B = getRandomMatrix(BRows, BCols);
        C = initEmptyMatrix(ARows, BCols);
        Cs = initEmptyMatrix(ARows, BCols);
    }
    // double start = MPI_Wtime();
    ParallelMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, C);
    // double end = MPI_Wtime();
    // double ptime = end - start;
    if (rank == 0) {
        // start = MPI_Wtime();
        SequentialMatrixMultiplication(A, ARows, ACols, B, BRows, BCols, Cs);
        // end = MPI_Wtime();
        // double stime = end - start;
        // std::cout << "The sequential process took " << stime
        //     << " seconds to run." << std::endl;
        // std::cout << "The parallel process took " << ptime
        //     << " seconds to run." << std::endl;
        // std::cout << "The speedup is " << stime - ptime
        //     << " seconds." << std::endl;
        bool flag = true;

        for (int i = 0; i < ARows * BCols; i++) {
            if (C[i] != Cs[i]) {
                flag = false;
            }
        }
        ASSERT_EQ(flag, true);
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
