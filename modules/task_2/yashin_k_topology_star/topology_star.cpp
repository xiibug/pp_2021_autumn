// Copyright 2021 Yashin Kirill

#include <mpi.h>
#include <algorithm>
#include <random>
#include "../../../modules/task_2/yashin_k_topology_star/topology_star.h"

int getRand(int min, int max) {
    if (min == max) {
        return max;
    } else {
        std::mt19937 gen;
    std::uniform_int_distribution<> distr{min, max};
    return distr(gen);
    }
}

MPI_Comm Star(int ProcNum) {
    MPI_Comm starcomm;

    int* index = new int[ProcNum];
    int* edges = new int[2 * ProcNum - 2];

    for (int i = 0; i < ProcNum-1; i++) {
        index[i] = 1;
    }

    index[ProcNum - 1] = ProcNum - 1;

    for (int i = 0; i < ProcNum - 1; i++) {
        edges[i] = 0;
    }

    for (int i = ProcNum - 1; i < 2 * ProcNum - 2; i++) {
        edges[i] = i - ProcNum + 2;
    }

    MPI_Graph_create(MPI_COMM_WORLD, ProcNum, index, edges, 0, &starcomm);
    return starcomm;
}
