// "Copyright [2021] <Borisov Maxim>"

#include <mpi.h>
#include <gtest/gtest.h>
#include "./scalar_vector_product.h"
#include <gtest-mpi-listener.hpp>

TEST(parallel_mpi, test_scalar_std) {
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    std::vector<int> vector_a;
    std::vector<int> vector_b;
    if (proc_rank == 0) {
        vector_a.reserve(100);
        vector_b.reserve(100);
        vector_a = get_random_vector(100);
        vector_b = get_random_vector(100);
    }

    int par_result = parallel_product(vector_a, vector_b);

    if (proc_rank == 0) {
        int seq_result = sequential_product_std(vector_a, vector_b);
        ASSERT_EQ(par_result, seq_result);
    }
}


TEST(parallel_mpi, test_scalar_mine) {
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    std::vector<int> vector_a;
    std::vector<int> vector_b;
    if (proc_rank == 0) {
        vector_a.reserve(100);
        vector_b.reserve(100);
        vector_a = get_random_vector(100);
        vector_b = get_random_vector(100);
    }
    int par_result = parallel_product(vector_a, vector_b);

    if (proc_rank == 0) {
        int seq_result = sequential_product(vector_a, vector_b);
        ASSERT_EQ(par_result, seq_result);
    }
}


TEST(parallel_mpi, test_scalar_std_2) {
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    std::vector<int> vector_a;
    std::vector<int> vector_b;
    if (proc_rank == 0) {
        vector_a.reserve(1000);
        vector_b.reserve(1000);
        vector_a = get_random_vector(1000);
        vector_b = get_random_vector(1000);
    }

    int par_result = parallel_product(vector_a, vector_b);

    if (proc_rank == 0) {
        int seq_result = sequential_product_std(vector_a, vector_b);
        ASSERT_EQ(par_result, seq_result);
    }
}


TEST(parallel_mpi, test_scalar_mine_1) {
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    std::vector<int> vector_a;
    std::vector<int> vector_b;
    if (proc_rank == 0) {
        vector_a.reserve(1000);
        vector_b.reserve(1000);
        vector_a = get_random_vector(1000);
        vector_b = get_random_vector(1000);
    }
    int par_result = parallel_product(vector_a, vector_b);

    if (proc_rank == 0) {
        int seq_result = sequential_product(vector_a, vector_b);
        ASSERT_EQ(par_result, seq_result);
    }
}

TEST(parallel_mpi, test_scalar_std_3) {
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    std::vector<int> vector_a;
    std::vector<int> vector_b;
    if (proc_rank == 0) {
        vector_a.reserve(500);
        vector_b.reserve(500);
        vector_a = get_random_vector(500);
        vector_b = get_random_vector(500);
    }

    int par_result = parallel_product(vector_a, vector_b);

    if (proc_rank == 0) {
        int seq_result = sequential_product_std(vector_a, vector_b);
        ASSERT_EQ(par_result, seq_result);
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

