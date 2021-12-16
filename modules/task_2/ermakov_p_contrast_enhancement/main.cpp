// Copyright 2021 Ermakov Pavel
#include "./contrast_enhancement.h"

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_9x9) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 9;
    int w = 9;
    int pic_size = h * w;
    double alpha = 1;
    int beta = 15;
    int i = 0;
    std::vector<int> tmp(pic_size);
    std::vector<int> tmp_m(pic_size);
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            tmp[i] = m[x][y];
            i++;
        }
    }
    tmp_m = contrast_enhancement_par(tmp, alpha, beta, h, w);

    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        i = 0;
        for (int x = 0; x < h; x++) {
            for (int y = 0; y < w; y++) {
                res_par[x][y] = res_seq[x][y];
                i++;
            }
        }
        i = 0;
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_91x91) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 91;
    int w = 91;
    int pic_size = h * w;
    double alpha = 1;
    int beta = 15;
    int i = 0;
    std::vector<int> tmp(pic_size);
    std::vector<int> tmp_m(pic_size);
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            tmp[i] = m[x][y];
            i++;
        }
    }
    tmp_m = contrast_enhancement_par(tmp, alpha, beta, h, w);

    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        i = 0;
        for (int x = 0; x < h; x++) {
            for (int y = 0; y < w; y++) {
                res_par[x][y] = res_seq[x][y];
                i++;
            }
        }
        i = 0;
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_100x100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 100;
    int w = 100;
    int pic_size = h * w;
    double alpha = 1;
    int beta = 15;
    int i = 0;
    std::vector<int> tmp(pic_size);
    std::vector<int> tmp_m(pic_size);
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            tmp[i] = m[x][y];
            i++;
        }
    }
    tmp_m = contrast_enhancement_par(tmp, alpha, beta, h, w);

    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        i = 0;
        for (int x = 0; x < h; x++) {
            for (int y = 0; y < w; y++) {
                res_par[x][y] = res_seq[x][y];
                i++;
            }
        }
        i = 0;
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_50x50) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 50;
    int w = 50;
    int pic_size = h * w;
    double alpha = 1;
    int beta = 15;
    int i = 0;
    std::vector<int> tmp(pic_size);
    std::vector<int> tmp_m(pic_size);
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            tmp[i] = m[x][y];
            i++;
        }
    }
    tmp_m = contrast_enhancement_par(tmp, alpha, beta, h, w);

    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        i = 0;
        for (int x = 0; x < h; x++) {
            for (int y = 0; y < w; y++) {
                res_par[x][y] = res_seq[x][y];
                i++;
            }
        }
        i = 0;
        ASSERT_EQ(res_seq, res_par);
    }
}

TEST(Parallel_Operations_MPI, contrast_enhancement_pic_10x10) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int h = 10;
    int w = 10;
    int pic_size = h * w;
    double alpha = 1;
    int beta = 15;
    int i = 0;
    std::vector<int> tmp(pic_size);
    std::vector<int> tmp_m(pic_size);
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_par(h, std::vector<int>(w));
    std::vector<std::vector<int>> res_seq(h, std::vector<int>(w));
    m = pic_gen(h, w);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            tmp[i] = m[x][y];
            i++;
        }
    }
    tmp_m = contrast_enhancement_par(tmp, alpha, beta, h, w);

    if (rank == 0) {
        res_seq = contrast_enhancement_seq(m, alpha, beta);
        i = 0;
        for (int x = 0; x < h; x++) {
            for (int y = 0; y < w; y++) {
                res_par[x][y] = res_seq[x][y];
                i++;
            }
        }
        i = 0;
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
