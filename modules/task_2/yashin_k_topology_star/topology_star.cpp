// Copyright 2021 Yashin Kirill

#include <mpi.h>
#include <algorithm>
#include <random>
#include "../../../modules/task_2/yashin_k_topology_star/topology_star.h"

int getRand(int min, int max) {
    if (min == max) {
        return min;
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

    index[0] = ProcNum - 1;
    for (int i = 1; i < ProcNum; i++) {
        index[i] = index[i - 1] + 1;
    }

    for (int i = 0; i < 2 * ProcNum - 2; i++) {
        if (i < ProcNum - 1) {
            edges[i] = i + 1;

        } else {
            edges[i] = 0;
        }
    }

    MPI_Graph_create(MPI_COMM_WORLD, ProcNum, index, edges, 1, &starcomm);
    return starcomm;
}
