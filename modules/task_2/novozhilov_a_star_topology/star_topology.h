// Copyright 2021 Novozhilov Alexander
#ifndef MODULES_TASK_2_NOVOZHILOV_A_STAR_TOPOLOGY_STAR_TOPOLOGY_H_
#define MODULES_TASK_2_NOVOZHILOV_A_STAR_TOPOLOGY_STAR_TOPOLOGY_H_
#include <vector>
#include <mpi.h>
MPI_Comm createStarTopology(MPI_Comm comm, int size);
#endif  // MODULES_TASK_2_NOVOZHILOV_A_STAR_TOPOLOGY_STAR_TOPOLOGY_H_
