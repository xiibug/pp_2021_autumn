// Copyright 2021 Burdukov Mikhail

#include "../../../modules/task_2/burdukov_m_topology_star/topology_star.hpp"

MPI_Comm create_graph_star() {
  int pcount;
  MPI_Comm_size(MPI_COMM_WORLD, &pcount);
  MPI_Comm result;
  int *index = new int[pcount];
  int *edges = new int[2 * (pcount - 1)];
  index[0] = pcount - 1;
  for (int i = 1; i < pcount; i++) index[i] = index[i - 1] + 1;
  for (int i = 0; i < pcount - 1; i++) edges[i] = i + 1;
  for (int i = pcount - 1; i < 2 * (pcount - 1); i++) edges[i] = 0;

  MPI_Graph_create(MPI_COMM_WORLD, pcount, index, edges, 0, &result);
  delete[] index;
  delete[] edges;
  return result;
}
