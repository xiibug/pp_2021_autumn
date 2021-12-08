// Copyright 2021 Pinezhanin Evgeny
#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_3/pinezhanin_e_linear_histogram_stretching/linear_histogram_stretching.h"

std::vector<std::vector<uchar>> getRandomMatrix(int height, int width, uchar a, uchar b) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<std::vector<uchar>> matrix;
    matrix.resize(height);
    for (int i = 0; i < height; i++) {
        matrix[i].resize(width);
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = gen() % (b - a) + a;
        }
    }
    return matrix;
}

std::vector<std::vector<uchar>> LinearHistogramStretchingParallel(std::vector<std::vector<uchar>> image) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    return image;
}

std::vector<std::vector<uchar>> LinearHistogramStretchingSequential(std::vector<std::vector<uchar>> image) {
    return image;
}
