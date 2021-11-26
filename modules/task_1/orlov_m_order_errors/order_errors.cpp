//  Copyright 2021 Maksim Orlov

#include <mpi.h>
#include <vector>
#include <ctime>
#include <iostream>
#include "./order_errors.h"

int orderErrors(std::vector<int> v) {
    int procs, rank, rem, pairsPerProc, res, errors = 0;
    int n_ = static_cast<int>(v.size()) - 1;
    int* displs;
    int* scounts;
    int* arr = new int[static_cast<int>(v.size())];
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        for (int i = 0; i < static_cast<int>(v.size()); i++) {
            arr[i] = v[i];
        }
    }
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
    MPI_Scatterv(arr, scounts, displs, MPI_INT, v_, scounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < scounts[rank] - 1; i++) {
        if (v_[i] > v_[i + 1])
            errors++;
    }
    MPI_Reduce(&errors, &res, procs, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    delete[] displs;
    delete[] scounts;
    delete[] arr;
    delete[] v_;
    return res;
}
