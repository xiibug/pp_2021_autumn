//  Copyright 2021 Maksim Orlov

#include <mpi.h>
#include <vector>
#include <ctime>
#include <iostream>
#include "../../../modules/task_1/orlov_m_order_errors/order_errors.h"

int orderErrors(std::vector<int> v) {
    int procs, rank, rem, pairsPerProc, res = 0, errors = 0;
    int n_ = static_cast<int>(v.size()) - 1;
    int* displs;
    int* scounts;
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    rem = n_ % procs;
    pairsPerProc = n_ / procs;
    displs = new int[procs];
    scounts = new int[procs];
    int offset = 0;
    for (int i = 0; i < procs; i++) {
        displs[i] = offset;
        if (i < rem) {
            offset += pairsPerProc + 1;
            scounts[i] = pairsPerProc + 2;
        } else {
            offset += pairsPerProc;
            scounts[i] = pairsPerProc + 1;
        }
    }
    int* v_ = new int[scounts[rank]];
    //  MPI_Scatterv(v.data(), scounts, displs, MPI_INT, v_, scounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = displs[rank]; i < displs[rank] + scounts[rank] - 1; i++) {
        if (v[i] > v[i + 1])
            errors++;
    }
    MPI_Reduce(&errors, &res, procs, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    delete[] displs;
    delete[] scounts;
    delete[] v_;
    return res;
}
