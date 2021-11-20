// Copyright 2021 Pinezhanin Evgeny
#include <gtest/gtest.h>
#include "./trapezoidal_rule.h"
#include <gtest-mpi-listener.hpp>

double f1(double x) {
    return x * x;
}

TEST(Trapezoidal_rule_test, x_square) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n = 100;
    double a = -2, b = 2;

    double global_sum = getIntegralTrapezoidalRuleParallel(f1, a, b, n);

    if (rank == 0) {
        double reference_sum = getIntegralTrapezoidalRuleSequential(f1, a, b, n);
        ASSERT_DOUBLE_EQ(reference_sum, global_sum);
    }
}

TEST(Trapezoidal_rule_test, two) {
    
}

TEST(Trapezoidal_rule_test, three) {
    
}

TEST(Trapezoidal_rule_test, four) {
    
}

TEST(Trapezoidal_rule_test, five) {
    
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
