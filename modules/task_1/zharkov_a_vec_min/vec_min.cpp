// Copyright 2021 Zharkov Andrey
#include <mpi.h>
#include <random>
#include "../../../modules/task_1/zharkov_a_vec_min/vec_min.h"


int getSequentialOperations(std::vector<int> vec) {
    const int  sz = vec.size();
    int reduction_elem = vec[0];
    for (int i = 1; i < sz; i++) {
        reduction_elem = std::min(reduction_elem, vec[i]);
    }

    return reduction_elem;
}

std::vector<int> getRandomVector(int sz) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

int getParallelOperations(std::vector<int> global_vec, int count_size_vector) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta = count_size_vector / size;

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
        MPI_Recv(local_vec.data(), delta, MPI_INT, 0, 0,
            MPI_COMM_WORLD, &status);
    }

    int global_min = 0;
    int local_min = getSequentialOperations(local_vec);
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    return global_min;
}
