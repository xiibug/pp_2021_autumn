// Copyright 2021 Ermakov Pavel
#include "./contrast_enhancement.h"

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_3x3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 3;
    int w = 3;
    double alpha = 1;
    int beta = 15;
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    res_par = contrast_enhancement_par(m, alpha, beta);
    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_91x91) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 91;
    int w = 91;
    double alpha = 1.5;
    int beta = 15;
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    res_par = contrast_enhancement_par(m, alpha, beta);
    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_100x100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 100;
    int w = 100;
    double alpha = 1.5;
    int beta = 15;
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    res_par = contrast_enhancement_par(m, alpha, beta);
    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_320x240) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 320;
    int w = 240;
    double alpha = 1.5;
    int beta = 15;
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    res_par = contrast_enhancement_par(m, alpha, beta);
    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_1009x1009) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 1009;
    int w = 1009;
    double alpha = 1.5;
    int beta = 15;
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    res_par = contrast_enhancement_par(m, alpha, beta);
    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        ASSERT_EQ(res_seq, res_par);
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
