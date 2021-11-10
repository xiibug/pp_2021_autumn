// Copyright 2021 Nazarov Nikita
#ifndef MODULES_TASK_2_NAZAROV_N_STAR_TOPOLOGY_STAR_TOPOLOGY_H_
#define MODULES_TASK_2_NAZAROV_N_STAR_TOPOLOGY_STAR_TOPOLOGY_H_

#include <mpi.h>
#include <vector>

MPI_Comm Star(const MPI_Comm comm);
bool IsStar(const MPI_Comm star);

#endif // MODULES_TASK_2_NAZAROV_N_STAR_TOPOLOGY_STAR_TOPOLOGY_H_