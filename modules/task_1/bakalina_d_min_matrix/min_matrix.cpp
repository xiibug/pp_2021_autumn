// Copyright 2021 Bakalina Darya

#include <mpi.h>
#include <iostream>
#include <random>
#include "./min_matrix.h"


int lin_search(const int* v, const int len) {
    int min;
    if (len > 0) {
        min = v[0];
        for (int i = 0; i < len; ++i) {
             if (min > v[i])
                 min = v[i];
        }
    }
    else
      throw "wrong size";
    return min;
}

void create_random_matrix(int*& mtrx, const unsigned int& size_n, const unsigned int& size_m) {
    std::random_device dev;
    std::mt19937 gen(dev());
    mtrx = new int[size_n * size_m];
    for (unsigned int i = 0; i < size_n * size_m; i++) {
        mtrx[i] = gen() % 1000;
		// mtrx[i] = rand() % 10000;
    }
}

int pharal_search(int* mtrx, int size_n, int size_m) {
    int ProcNum, ProcRank;
    int quotient, resd;
    int* rcvbufF, * sd_counts, * disp;
    int min = 0, glMin = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    quotient = size_n * size_m / ProcNum;
    resd = size_n * size_m % ProcNum;   

    sd_counts = new int[ProcNum];
    disp = new int[ProcNum];

    for (int i = 0; i < ProcNum; i++) {
        sd_counts[i] = quotient;
        disp[i] = i * quotient;
    }
    sd_counts[ProcNum - 1] += resd;

    rcvbufF = new int[sd_counts[ProcRank]];
    MPI_Scatterv(mtrx, sd_counts, disp, MPI_INT, rcvbufF, sd_counts[ProcRank], MPI_INT, 0, MPI_COMM_WORLD);

    min = lin_search(rcvbufF, sd_counts[ProcRank]);

    MPI_Reduce(&min, &glMin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (ProcRank == 0) {
        delete[] sd_counts;
        delete[] disp;
    }
    delete[] rcvbufF;

    return glMin;
}
