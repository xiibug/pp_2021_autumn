/// Copyright 2021 Shmanalov Alexander
#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include "./iterative_jacobi_method.h"
#include <gtest-mpi-listener.hpp>

TEST(iterativeJacobiMethod, dimension_5) {
    const double epsilon = 0.001;
    int rank, equationsNumber = 5;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrixA = 0;
    int* matrixB = 0;
    double* resultParallel = 0;
    if (rank == 0) {
        matrixA = new int[equationsNumber * equationsNumber];
        matrixB = new int[equationsNumber];
        resultParallel = new double[equationsNumber];
        generationRandomData(matrixA, matrixB, equationsNumber);
        /*for (int i = 0; i < equationsNumber; i++) {
            for (int j = 0; j < equationsNumber; j++) {
                std::cout << matrixA[i * equationsNumber + j] << ' ';
            }
            std::cout << "= " << matrixB[i] << std::endl;
        }*/
    }
    parallelJacobi(matrixA, matrixB, resultParallel, epsilon, equationsNumber);
    if (rank == 0) {
        double* reference = new double[equationsNumber];
        for (int i = 0; i < equationsNumber; i++) {
            double tempRef = 0;
            for (int j = 0; j < equationsNumber; j++) {
                tempRef += matrixA[i * equationsNumber + j] * resultParallel[j];
                reference[i] = tempRef;
            }
        }
        for (int i = 0; i < equationsNumber; i++) {
            ASSERT_EQ(round(reference[i]), matrixB[i]);
        }
    }
}

TEST(iterativeJacobiMethod, dimension_10) {
    const double epsilon = 0.001;
    int rank, equationsNumber = 10;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrixA = 0;
    int* matrixB = 0;
    double* resultParallel = 0;
    if (rank == 0) {
        matrixA = new int[equationsNumber * equationsNumber];
        matrixB = new int[equationsNumber];
        resultParallel = new double[equationsNumber];
        generationRandomData(matrixA, matrixB, equationsNumber);
    }
    parallelJacobi(matrixA, matrixB, resultParallel, epsilon, equationsNumber);
    if (rank == 0) {
        double* reference = new double[equationsNumber];
        for (int i = 0; i < equationsNumber; i++) {
            double tempRef = 0;
            for (int j = 0; j < equationsNumber; j++) {
                tempRef += matrixA[i * equationsNumber + j] * resultParallel[j];
                reference[i] = tempRef;
            }
        }
        for (int i = 0; i < equationsNumber; i++) {
            ASSERT_EQ(round(reference[i]), matrixB[i]);
        }
    }
}

TEST(iterativeJacobiMethod, dimension_15) {
    const double epsilon = 0.001;
    int rank, equationsNumber = 15;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrixA = 0;
    int* matrixB = 0;
    double* resultParallel = 0;
    if (rank == 0) {
        matrixA = new int[equationsNumber * equationsNumber];
        matrixB = new int[equationsNumber];
        resultParallel = new double[equationsNumber];
        generationRandomData(matrixA, matrixB, equationsNumber);
    }
    parallelJacobi(matrixA, matrixB, resultParallel, epsilon, equationsNumber);
    if (rank == 0) {
        double* reference = new double[equationsNumber];
        for (int i = 0; i < equationsNumber; i++) {
            double tempRef = 0;
            for (int j = 0; j < equationsNumber; j++) {
                tempRef += matrixA[i * equationsNumber + j] * resultParallel[j];
                reference[i] = tempRef;
            }
        }
        for (int i = 0; i < equationsNumber; i++) {
            ASSERT_EQ(round(reference[i]), matrixB[i]);
        }
    }
}

TEST(iterativeJacobiMethod, dimension_20) {
    const double epsilon = 0.001;
    int rank, equationsNumber = 20;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrixA = 0;
    int* matrixB = 0;
    double* resultParallel = 0;
    if (rank == 0) {
        matrixA = new int[equationsNumber * equationsNumber];
        matrixB = new int[equationsNumber];
        resultParallel = new double[equationsNumber];
        generationRandomData(matrixA, matrixB, equationsNumber);
    }
    parallelJacobi(matrixA, matrixB, resultParallel, epsilon, equationsNumber);
    if (rank == 0) {
        double* reference = new double[equationsNumber];
        for (int i = 0; i < equationsNumber; i++) {
            double tempRef = 0;
            for (int j = 0; j < equationsNumber; j++) {
                tempRef += matrixA[i * equationsNumber + j] * resultParallel[j];
                reference[i] = tempRef;
            }
        }
        for (int i = 0; i < equationsNumber; i++) {
            ASSERT_EQ(round(reference[i]), matrixB[i]);
        }
    }
}

TEST(iterativeJacobiMethod, dimension_50) {
    const double epsilon = 0.001;
    int rank, equationsNumber = 50;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* matrixA = 0;
    int* matrixB = 0;
    double* resultParallel = 0;
    if (rank == 0) {
        matrixA = new int[equationsNumber * equationsNumber];
        matrixB = new int[equationsNumber];
        resultParallel = new double[equationsNumber];
        generationRandomData(matrixA, matrixB, equationsNumber);
    }
    parallelJacobi(matrixA, matrixB, resultParallel, epsilon, equationsNumber);
    if (rank == 0) {
        double* reference = new double[equationsNumber];
        for (int i = 0; i < equationsNumber; i++) {
            double tempRef = 0;
            for (int j = 0; j < equationsNumber; j++) {
                tempRef += matrixA[i * equationsNumber + j] * resultParallel[j];
                reference[i] = tempRef;
            }
        }
        for (int i = 0; i < equationsNumber; i++) {
            ASSERT_EQ(round(reference[i]), matrixB[i]);
        }
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
