// Copyright 2021 Denisova Julia

#include <mpi.h>
#include <random>
#include "../../../modules/task_2/denisova_ribbon_horizont_scheme/ribbon_horizont_scheme.h"


void multipl(int* bigmas, int* mas, int str, int col, int* tmpres) {
    for (int i = 0; i < str; i++) {
        tmpres[i] = 0;
        for (int j = 0; j < col; j++) {
            tmpres[i] += bigmas[i * col + j] * mas[j];
        }
    }
}

void random_matrix(int str, int col, int* matrix) {
    std::random_device dev;
    std::mt19937 gen(dev());
	for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
           matrix[i * col + j] = gen() % 10;
        }
    }
}

void random_vector(int str, int* vector) {
    std::random_device dev;
    std::mt19937 gen(dev());
	for (int i = 0; i < str; i++) {
        vector[i] = gen() % 10;
    }
}

void pharal_alg(int str, int col, int* bigmas, int* mas, int* resbuf) {
    int procCount = 0, procRank = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int count = str / procCount;
    int tmpcount = str % procCount;
    int* p_count = nullptr;
    int* p_displ = nullptr;
    int numelems = 0;
    if (procRank == 0) {
        p_count = new int[procCount];
        p_displ = new int[procCount];
        for (int i = 0; i < procCount; i++) {
             p_count[i] = count * col;
        }
        if (tmpcount != 0) {
            for (int i = 0; i < tmpcount; i++) {
                 p_count[i] += col;
            }
        }
        p_displ[0] = 0;
        for (int i = 1; i < procCount; i++) {
             p_displ[i] = p_displ[i - 1] + p_count[i - 1];
        }
    }
    numelems = count * col;
    if ((tmpcount != 0) && (procRank < tmpcount)) {
       numelems += col;
    }
    int* rbuf = new int[numelems];
    MPI_Bcast(mas, str, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatterv(bigmas, p_count, p_displ, MPI_INT, rbuf, numelems, MPI_INT, 0, MPI_COMM_WORLD);
    int blok = numelems / col;
    int* tmpres = new int[blok];
    multipl(rbuf, mas, blok, col, tmpres);
    if (procRank == 0) {
        for (int i = 0; i < procCount; i++) {
            p_count[i] = p_count[i] / col;
            p_displ[i] = p_displ[i] / col;
        }
    }
    MPI_Gatherv(tmpres, blok, MPI_INT, resbuf, p_count, p_displ, MPI_INT, 0, MPI_COMM_WORLD);
    if (procRank == 0) {
        delete[] p_count;
        delete[] p_displ;
    }
    delete[] rbuf;
    delete[] tmpres;
}
