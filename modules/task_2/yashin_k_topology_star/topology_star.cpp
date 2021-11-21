// Copyright 2021 Yashin Kirill

#include <mpi.h>
#include <algorithm>
#include <random>
#include "../../../modules/task_2/yashin_k_topology_star/topology_star.h"

int getRand(std::size_t min, std::size_t max) {
    return (min + rand_r() % (max - min));
}

MPI_Comm Star(std::size_t ProcNum) {
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
