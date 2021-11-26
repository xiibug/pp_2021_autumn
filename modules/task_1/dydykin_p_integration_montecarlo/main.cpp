// Copyright 2021 Dydykin Pavel
#include <gtest/gtest.h>
#include "../../../modules/task_1/dydykin_p_integration_montecarlo/integration_montecarlo.h"
#include <gtest-mpi-listener.hpp>

TEST(Test_MonteCarlo, TestFunc1) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    int a, b, N;
    a = 1;
    b = 3;
    N = 20000;

    double mpi_result = MonteCarloMPI(N, a, b, func1);
    if (ProcRank == 0) {
        double withoutmpi_result = MonteCarloWithOutMPI(N, a, b, func1);
        ASSERT_NEAR(mpi_result, withoutmpi_result, 0.5);
    }
}

TEST(Test_MonteCarlo, TestFunc2) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    int a, b, N;
    a = 4;
    b = 11;
    N = 20000;

    double mpi_result = MonteCarloMPI(N, a, b, func2);
    if (ProcRank == 0) {
        double withoutmpi_result = MonteCarloWithOutMPI(N, a, b, func2);
        ASSERT_NEAR(mpi_result, withoutmpi_result, 0.5);
    }
}

TEST(Test_MonteCarlo, TestFunc3) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    int a, b, N;
    a = 15;
    b = 20;
    N = 20000;

    double mpi_result = MonteCarloMPI(N, a, b, func3);
    if (ProcRank == 0) {
        double withoutmpi_result = MonteCarloWithOutMPI(N, a, b, func3);
        ASSERT_NEAR(mpi_result, withoutmpi_result, 1);
    }
}

TEST(Test_MonteCarlo, TestFunc4) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    int a, b, N;
    a = 5;
    b = 9;
    N = 20000;

    double mpi_result = MonteCarloMPI(N, a, b, func1);
    if (ProcRank == 0) {
        double withoutmpi_result = MonteCarloWithOutMPI(N, a, b, func1);
        ASSERT_NEAR(mpi_result, withoutmpi_result, 0.5);
    }
}

TEST(Test_MonteCarlo, TestFunc5) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    int a, b, N;
    a = 3;
    b = 21;
    N = 20000;

    double mpi_result = MonteCarloMPI(N, a, b, func2);
    if (ProcRank == 0) {
        double withoutmpi_result = MonteCarloWithOutMPI(N, a, b, func2);
        ASSERT_NEAR(mpi_result, withoutmpi_result, 0.5);
    }
}

TEST(Test_MonteCarlo, TestFunc6) {
    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    int a, b, N;
    a = 20;
    b = 10;
    N = 20000;

    ASSERT_ANY_THROW(MonteCarloMPI(N, a, b, func3));
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
