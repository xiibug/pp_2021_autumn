// Copyright 2021 Preobrazhenskaya Yuliya
#include "../../../modules/task_2/preobrazhenskaya_y_ring_topology/ring_topology.h"

MPI_Comm getRingTopology(const MPI_Comm comm) {
    int size;
    MPI_Comm_size(comm, &size);

    int* index = new int[size];
    int* edges = new int[size];

    for (int i = 0; i < size; i++) {
        index[i] = i + 1;
    }

    for (int i = 0; i < size; i++) {
        if (i != size - 1) {
            edges[i] = i + 1;
        } else {
            edges[i] = 0;
        }
    }

    MPI_Comm ring;

    MPI_Graph_create(comm, size, index, edges, 0, &ring);

    return ring;
}
