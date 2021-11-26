// Copyright 2021 Kruglov Aleksei
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_3/kruglov_algorithm_strassen/Strassen_algorithm.h"

TEST(Multiply, matrix_0) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Matrix m1, m2;
    if (proc_rank == 0) {
        int h = 2, w = 2;
        double max_num = 10.0;
        m1 = get_random_matrix(h, w, max_num);
        m2 = get_random_matrix(h, w, max_num);
    }
    auto opt = parallel_multiply(m1, m2);
    if (proc_rank == 0) {
        double threshold = 0.1;
        auto ref = reference_multiply(m1, m2);
        ASSERT_TRUE(is_equal(ref, opt, threshold));
    }
}

TEST(Multiply, matrix_1) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Matrix m1, m2;
    if (proc_rank == 0) {
        int h = 4, w = 4;
        double max_num = 10.0;
        m1 = get_random_matrix(h, w, max_num);
        m2 = get_random_matrix(h, w, max_num);
    }
    auto opt = parallel_multiply(m1, m2);
    if (proc_rank == 0) {
        double threshold = 0.1;
        auto ref = reference_multiply(m1, m2);
        ASSERT_TRUE(is_equal(ref, opt, threshold));
    }
}

TEST(Multiply, matrix_2) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Matrix m1, m2;
    if (proc_rank == 0) {
        int h = 8, w = 8;
        double max_num = 10.0;
        m1 = get_random_matrix(h, w, max_num);
        m2 = get_random_matrix(h, w, max_num);
    }
    auto opt = parallel_multiply(m1, m2);
    if (proc_rank == 0) {
        double threshold = 0.1;
        auto ref = reference_multiply(m1, m2);
        ASSERT_TRUE(is_equal(ref, opt, threshold));
    }
}

TEST(Multiply, matrix_3) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Matrix m1, m2;
    if (proc_rank == 0) {
        int h = 16, w = 16;
        double max_num = 10.0;
        m1 = get_random_matrix(h, w, max_num);
        m2 = get_random_matrix(h, w, max_num);
    }
    auto opt = parallel_multiply(m1, m2);
    if (proc_rank == 0) {
        double threshold = 0.1;
        auto ref = reference_multiply(m1, m2);
        ASSERT_TRUE(is_equal(ref, opt, threshold));
    }
}

TEST(Multiply, matrix_4) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Matrix m1, m2;
    if (proc_rank == 0) {
        int h = 32, w = 32;
        double max_num = 100.0;
        m1 = get_random_matrix(h, w, max_num);
        m2 = get_random_matrix(h, w, max_num);
    }
    auto opt = parallel_multiply(m1, m2);
    if (proc_rank == 0) {
        double threshold = 0.1;
        auto ref = reference_multiply(m1, m2);
        ASSERT_TRUE(is_equal(ref, opt, threshold));
    }
}

TEST(Multiply, matrix_5) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Matrix m1, m2;
    if (proc_rank == 0) {
        int h = 32, w = 32;
        double max_num = 1000;
        m1 = get_random_matrix(h, w, max_num);
        m2 = get_random_matrix(h, w, max_num);
    }
    auto opt = parallel_multiply(m1, m2);
    if (proc_rank == 0) {
        double threshold = 0.1;
        auto ref = reference_multiply(m1, m2);
        ASSERT_TRUE(is_equal(ref, opt, threshold));
    }
}

TEST(Multiply, matrix_6) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Matrix m1, m2;
    if (proc_rank == 0) {
        int h = 32, w = 32;
        double max_num = 1;
        m1 = get_random_matrix(h, w, max_num);
        m2 = get_random_matrix(h, w, max_num);
    }
    auto opt = parallel_multiply(m1, m2);
    if (proc_rank == 0) {
        double threshold = 0.1;
        auto ref = reference_multiply(m1, m2);
        ASSERT_TRUE(is_equal(ref, opt, threshold));
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
