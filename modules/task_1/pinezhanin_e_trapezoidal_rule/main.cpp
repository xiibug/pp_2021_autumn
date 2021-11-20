// Copyright 2021 Pinezhanin Evgeny
#include <gtest/gtest.h>
#include "./trapezoidal_rule.h"
#include <gtest-mpi-listener.hpp>

double f1(double x) {
    return x * x;
}

TEST(Trapezoidal_rule_test, one) {

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
