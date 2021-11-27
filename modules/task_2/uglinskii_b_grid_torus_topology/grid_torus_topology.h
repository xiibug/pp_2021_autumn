// Copyright 2021 Uglinskii Bogdan
#ifndef MODULES_TASK_2_UGLINSKII_B_GRID_TORUS_TOPOLOGY_H_
#define MODULES_TASK_2_UGLINSKII_B_GRID_TORUS_TOPOLOGY_H_
#include <mpi.h>

MPI_Comm CreateGridTorusTopology(int width, int height);

bool IsExpectedGridTorus(const MPI_Comm grid_torus_comm,const int exp_dims_count, const int* exp_dims_vals);

#endif  // MODULES_TASK_2_UGLINSKII_B_GRID_TORUS_TOPOLOGY_H_