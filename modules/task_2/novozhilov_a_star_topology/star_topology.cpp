// Copyright 2021 Novozhilov Alexander
#include <mpi.h>
#include <vector>
#include "../../../modules/task_2/novozhilov_a_star_topology/star_topology.h"

MPI_Comm createStarTopology(MPI_Comm comm, int size) {
    std::vector<int> index;
    std::vector<int> edges;
    index.push_back(size - 1);
    for (int i = 0; i < size - 1; i++) {
        index.push_back(index[static_cast<int>(index.size())-1] + 1);
    }
    for (int i = 1; i <= size - 1; i++) {
        edges.push_back(i);
    }
    for (int i = 0; i < size - 1; i++) {
        edges.push_back(0);
    }
    if (edges.size() == 0) {
        edges.push_back(0);
    }
    MPI_Comm star;
    MPI_Graph_create(comm, size, index.data(), edges.data(), 0, &star);
    return star;
}
