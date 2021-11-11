// Copyright 2021 Sablin Alexander
#include "../../../modules/task_1/sablin_max_el_of_vec/max_el_of_vec.h"
#include <mpi.h>
#include <random>

double* getRandomVector(double* rand_vec, int n, int dia) {
    std::random_device dev;
    std::mt19937 gen(dev());
    rand_vec = new double[n];
    for (int i = 0; i < n; i++)
        rand_vec[i] = gen() % dia;
    return rand_vec;
}

double CalcMaxNumber(double* calc_vec, int n) {
    double max = calc_vec[0];
    for (int i = 0; i < n; i++) {
        if (calc_vec[i] > max)
            max = calc_vec[i];
    }
    return max;
}

double DoParallelComputing(double* a, int n) {
    int* sendcounts = nullptr;
    int* displs = nullptr;
    int ProcNum, ProcRank, cim;
    double max, max_all;

    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == 0) {
        sendcounts = new int[ProcNum];
        displs = new int[ProcNum];
        int ost = n % ProcNum;
        int sum = 0;
        for (int i = 0; i < ProcNum; i++) {
            sendcounts[i] = (n / ProcNum);
            if (ost > 0) {
                sendcounts[i] += 1;
                ost--;
            }
            displs[i] = sum;
            sum += sendcounts[i];
        }
    }

    MPI_Scatter(sendcounts, 1, MPI_INT, &cim, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double* b = new double[cim];

    MPI_Scatterv(a, sendcounts, displs, MPI_DOUBLE, b, cim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    max = CalcMaxNumber(b, cim);

    MPI_Reduce(&max, &max_all, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (ProcRank == 0) {
        delete[] displs;
        delete[] sendcounts;
    }

    delete[] b;

    return max_all;
}
