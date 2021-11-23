// Copyright 2021 Kolesnikov Ilya
#include <iostream>
#include "../../../modules/task_2/kolesnikov_ring_topology/kolesnikov_ring_topology.h"

MPI_Comm topology_ring(const MPI_Comm comm) {
    int size;

    MPI_Comm_size(comm, &size);

    int periods[1] = { 1 }, reorder = 0;
    int dims[1] = { size };

    MPI_Comm ring;

    MPI_Cart_create(comm, 1, dims, periods, reorder, &ring);

    return ring;
}
