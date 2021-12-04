// Copyright 2021 Pinezhanin Evgeny
#include <mpi.h>
#include <vector>
#include "../../../modules/task_3/pinezhanin_e_linear_histogram_stretching/linear_histogram_stretching.h"

std::vector<std::vector<int>> LinearHistogramStretchingParallel(std::vector<std::vector<int>> image) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    return image;
}

std::vector<std::vector<int>> LinearHistogramStretchingSequential(std::vector<std::vector<int>> image) {
    return image;
}
