// Copyright 2021 Yashin Kirill

#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_1/yashin_k_vector_sum/vector_sum.h"


std::vector<int> getRandVector(int size, int prom) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> rand_vec(size);
    for (int i = 0; i < size ; i++) {
        rand_vec[i] = gen() % prom;
    }
    return rand_vec;
}

int getSum(std::vector<int> part_vec) {
    int part_sum = 0;
    int part_size = part_vec.size();
    for (int i = 0; i < part_size; i++) {
        part_sum += part_vec[i];
    }
    return part_sum;
}

int getParallelSum(std::vector<int> vec, int size) {
    int ProcNum, ProcRank;

    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    int part = size / ProcNum;
    std::vector<int> part_vec(part);
    if (ProcRank == 0) {
        for (int i = 1; i < ProcNum; i++) {
            MPI_Send(&vec[0] + i * part, part, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
        part_vec = std::vector<int>(vec.begin(), vec.begin() + part);
    } else {
        MPI_Recv(&part_vec[0], part, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    int all_sum = 0;
    int part_sum = getSum(part_vec);
    MPI_Reduce(&part_sum, &all_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return all_sum;
}
