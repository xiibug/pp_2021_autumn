// Copyright 2021 Korobejnikov Alexander
#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "./vector_min_diff.h"

int sequentialCount(std::vector<int> vec) {
    int len = vec.size();
    int min = abs(vec[1] - vec[0]);
    for (int i = 2; i < len; ++i) {
        if (abs(vec[i] - vec[i - 1]) < min) {
            min = abs(vec[i] - vec[i - 1]);
        }
    }
    return min;
}

std::vector<int> getRandomVector(int sz) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

int parallelCount(std::vector<int> vec, int len) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n = len / size;
    int ost = len % size;
    std::vector<int> local_vec;
    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            MPI_Send(vec.data() + ost + proc * n - 1, n + 1,
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }
    if (rank == 0) {
        local_vec = std::vector<int>(vec.begin(), vec.begin() + n + 1 + ost);
    } else {
        local_vec.resize(n + 1);
        MPI_Status status;
        MPI_Recv(local_vec.data(), n + 1,
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
    int my_p = sequentialCount(local_vec);
    int global_p;
    MPI_Reduce(&my_p, &global_p, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    return global_p;
}
