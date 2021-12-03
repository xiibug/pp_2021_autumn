// Copyright 2021 Ermakov Pavel
#include "./q_sort_odd_even_m_batcher.h"

//TEST(Parallel_Operations_MPI, stopwatch_200000)
//{
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    double start_of_par;
//    double end_of_par;
//    double start_of_seq;
//    double end_of_seq;
//    int size = 200000;
//    std::vector<int> a(size);
//    std::vector<int> t(size);
//
//    a = vec_gen(size);
//    t = a;
//    if (rank == 0) {
//        start_of_par = MPI_Wtime();
//    }
//    q_sort_batcher_par(&a);
//    if (rank == 0) {
//        end_of_par = MPI_Wtime();
//        start_of_seq = MPI_Wtime();
//        q_sort(t, 0, t.size() - 1);
//        end_of_seq = MPI_Wtime();
//        std::cout << end_of_par - start_of_par << " par" << std::endl;
//        std::cout << end_of_seq - start_of_seq << " seq" << std::endl;
//        ASSERT_EQ(a, t);
//    }
//}

TEST(Parallel_Operations_MPI, size_100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 100;
    std::vector<int> a(size);
    std::vector<int> t(size);

    a = vec_gen(size);
    t = a;

    q_sort_batcher_par(&a);
    if (rank == 0) {
        q_sort(t, 0, t.size() - 1);
        ASSERT_EQ(a, t);
    }
}

TEST(Parallel_Operations_MPI, size_1337) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 1337;
    std::vector<int> a(size);
    std::vector<int> t(size);

    a = vec_gen(size);
    t = a;

    q_sort_batcher_par(&a);
    if (rank == 0) {
        q_sort(t, 0, t.size() - 1);
        ASSERT_EQ(a, t);
    }
}

TEST(Parallel_Operations_MPI, size_2077) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 2077;
    std::vector<int> a(size);
    std::vector<int> t(size);

    a = vec_gen(size);
    t = a;

    q_sort_batcher_par(&a);
    if (rank == 0) {
        q_sort(t, 0, t.size() - 1);
        ASSERT_EQ(a, t);
    }
}

TEST(Parallel_Operations_MPI, size_2022) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 2022;
    std::vector<int> a(size);
    std::vector<int> t(size);

    a = vec_gen(size);
    t = a;

    q_sort_batcher_par(&a);
    if (rank == 0) {
        q_sort(t, 0, t.size() - 1);
        ASSERT_EQ(a, t);
    }
}

TEST(Parallel_Operations_MPI, size_20000) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 20000;
    std::vector<int> a(size);
    std::vector<int> t(size);

    a = vec_gen(size);
    t = a;

    q_sort_batcher_par(&a);
    if (rank == 0) {
        q_sort(t, 0, t.size() - 1);
        ASSERT_EQ(a, t);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
