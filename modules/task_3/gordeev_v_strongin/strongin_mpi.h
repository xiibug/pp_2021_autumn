// Copyright 2021 Gordeev Viktor
#ifndef MODULES_TASK_3_GORDEEV_V_STRONGIN_STRONGIN_MPI_H_
#define MODULES_TASK_3_GORDEEV_V_STRONGIN_STRONGIN_MPI_H_

#include <math.h>
#include <stdio.h>
#include <mpi.h>
#include <vector>
#include <queue>
#include <list>
#include <string>


struct segment{
    double yi;  // beggining mark(left)
    double yj;  // ending marks(right)
};

struct mpiArtefact {
    double R;  // Characteristic
    int T;  // segment number
};

double R(const double& _m_small, const double& _z_curr, const double& _z_prev,
    const double& _x_curr, const double& _x_prev);
double M(const double& _z_curr, const double& _z_prev, const double& _x_curr,
    const double& _x_prev);
double StronginParallel(const double _left, const double _right,
    const int _N_max, const double _Eps, int procs, int rank);
double StronginSeq(const double _left, const double _right,
    const int _N_max, const double _Eps);
double func(const double& _x);

#endif  // MODULES_TASK_3_GORDEEV_V_STRONGIN_STRONGIN_MPI_H_
