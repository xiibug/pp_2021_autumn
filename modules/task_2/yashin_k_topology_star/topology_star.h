// Copyright 2021 Yashin Kirill
#ifndef MODULES_TASK_2_YASHIN_K_TOPOLOGY_STAR_H_
#define MODULES_TASK_2_YASHIN_K_TOPOLOGY_STAR_H_

#include <mpi.h>
int getRand(std::size_t min, std::size_t max);
MPI_Comm Star(std::size_t ProcNum);
#endif  // MODULES_TASK_2_YASHIN_K_TOPOLOGY_STAR_H_
