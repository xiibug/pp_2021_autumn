// Copyright 2021 Uglinskii Bogdan
#include "../../../modules/task_2/uglinskii_b_grid_torus_topology/grid_torus_topology.h"

MPI_Comm CreateGridTorusTopology(int width, int height) {
  int ProcNum, ProcRank;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  if (height > 0 && width > 0 && (height * width > ProcNum)) {
    return MPI_COMM_NULL;
  }
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  int dimensions[2] = {width, height};

  MPI_Comm grid_torus_comm;
  int periods[2] = {true, true};
  MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions, periods, false,
                  &grid_torus_comm);

  MPI_Comm_rank(grid_torus_comm, &ProcRank);
  int my_coords[2];
  MPI_Cart_coords(grid_torus_comm, ProcRank, 2, my_coords);
  return grid_torus_comm;
}

bool IsExpectedGridTorus(const MPI_Comm grid_torus_comm, const int exp_dims_count, const int* exp_dims_vals) {
  int topology_type = 0;
  MPI_Topo_test(grid_torus_comm, &topology_type);
  if (topology_type != MPI_CART) {
    return false;
  }

  int real_dims_count;
  MPI_Cartdim_get(grid_torus_comm, &real_dims_count);
  if (real_dims_count != exp_dims_count) {
    return false;
  } else {
    int* topology_dims = new int[real_dims_count];
    int* topology_periods = new int[real_dims_count];
    int* proc_coords = new int[real_dims_count];

    MPI_Cart_get(grid_torus_comm, 2, topology_dims, topology_periods, proc_coords);

    for (size_t i = 0; i < real_dims_count; i++) {
      if ((topology_dims[i] != exp_dims_vals[i]) ||
          (topology_periods[i] != true)) {
        return false;
      }
    }
  }

  return true;
}
