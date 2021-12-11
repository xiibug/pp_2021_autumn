// Copyright 2021 Tyrina Anastasia
#include <mpi.h>
#include <vector>
#include <random>
#include <algorithm>
#include "../../../modules/task_1/tyrina_a_vector_max/vector_max.h"

std::vector<int> getRandomVector(int sz) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(sz);
    for (int  i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

int getSequentialMax(std::vector<int> vec) {
    const int  sz = vec.size();
    int reduction_elem = 0;

    reduction_elem = vec[0];
    for (int i = 1; i < sz; i++) {
        reduction_elem = std::max(reduction_elem, vec[i]);
    }

    return reduction_elem;
}

int getParallelMax(std::vector<int> global_vec, int count_size_vector) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta = count_size_vector / size;
    const int rem = count_size_vector % size;

    int global_max = 0;

    if (delta) {
        if (rank == 0) {
            for (int proc = 1; proc < size; proc++) {
                MPI_Send(global_vec.data() + proc * delta, delta,
                    MPI_INT, proc, 0, MPI_COMM_WORLD);
            }
        }

        std::vector<int> local_vec(delta);
        if (rank == 0) {
            local_vec = std::vector<int>(global_vec.begin(),
                global_vec.begin() + delta);
        } else {
            MPI_Status status;
            MPI_Recv(local_vec.data(), delta, MPI_INT,
                0, 0, MPI_COMM_WORLD, &status);
        }

        int local_max = getSequentialMax(local_vec);

        MPI_Reduce(&local_max, &global_max, 1, MPI_INT,
            MPI_MAX, 0, MPI_COMM_WORLD);
    } else {
        if (rank == 0) {
            global_max = global_vec[0];
        }
    }

    if (rank == 0) {
        for (int i = delta * size; i < delta * size + rem; i++) {
            global_max = std::max(global_max, global_vec[i]);
        }
    }

    return global_max;
}
