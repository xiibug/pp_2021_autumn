// Copyright 2021 Stepanov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./gauss_horizontal_scheme.h"
#include <gtest-mpi-listener.hpp>


TEST(GENERATE_MATRIX, can_generate_random_sle) {
    std::vector<double> matrix(10 * 10);
    std::vector<double> vector(10);
    ASSERT_NO_THROW(generateSLE(&matrix, &vector, 10));
}

TEST(SEQUENTIAL_OPERATIONS, can_run_sequential_gauss) {
    std::vector<double> matrix = { 1, 2, 3,
                                   4, 5, 6,
                                   7, 8, 9 };
    std::vector<double> vector{ 1, 2, 3, 4, 5 };
    ASSERT_NO_THROW(sequentialGaussScheme(matrix, vector, 3));
}

TEST(SEQUENTIAL_OPERATIONS, sequential_gauss_works_correctly) {
    std::vector<double> matrix = { 1, 2, 3,
                                   4, 5, 6,
                                   7, 8, 9 };
    std::vector<double> vector{ 1, 2, 3 };

    auto solution = sequentialGaussScheme(matrix, vector, 3);
    std::vector<double> expected_solution = { -1. / 3., 2. / 3., 0 };

    for (std::vector<double>::size_type i = 0; i < solution.size(); i++) {
        ASSERT_NEAR(solution[i], expected_solution[i], 0.01);
    }
}

TEST(SEQUENTIAL_OPERATIONS, sequential_gauss_works_correctly_with_random_sle) {
    const std::vector<double>::size_type number_unknows = 17;
    std::vector<double> matrix(number_unknows * number_unknows);
    std::vector<double> vector(number_unknows);

    auto expected_solution = generateSLE(&matrix, &vector, number_unknows);
    auto solution = sequentialGaussScheme(matrix, vector, number_unknows);

    for (std::vector<double>::size_type i = 0; i < solution.size(); i++) {
        ASSERT_NEAR(solution[i], expected_solution[i], 0.01);
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
