#include <random>
#include <iostream>
#include "mpi.h"
#include "../../../modules/task_1/denisova_max_column_matrix/max_column_matrix.h"

using namespace std;

void findmax(int* mas, int col, int str, int* tmpmax) { 
    for (int i = 0; i < col; i++)
    {
        tmpmax[i] = mas[i * str];
        for (int j = 0; j < str; j++) {
			if (mas[i * str + j] >= tmpmax[i]) {
               tmpmax[i] = mas[i * str + j];
            }
        }
    }
}

void random_matrix(int str, int col, int* matrix) {
    std::random_device dev;
    std::mt19937 gen(dev());
	for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i * col + j] = gen() % 100;
        }
    }
}

void swap_matrix(int str, int col, int* matrix, int* bigmas) {
    int k = 0;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < str; j++) {
           bigmas[k++] = matrix[j * str + i];
        }
    }
}

void max_from_columns(int str, int col, int* bigmas, int* resbuf) {
    int procCount = 0;
    int procRank = 0;
    int count = 0; 
    int tmpcount = 0; 
    int* p_count = nullptr;
    int* p_displ = nullptr;
    int numelems = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    count = col / procCount;
    tmpcount = col% procCount;
    if (procRank == 0) {
        p_count = new int[procCount];
        p_displ = new int[procCount];
        for (int i = 0; i < procCount; i++) {
            p_count[i] = count * str;
        }
        if (tmpcount != 0) {
            for (int i = 0; i < tmpcount; i++) {
                p_count[i] += str;
            }
        }
        p_displ[0] = 0;
        for (int i = 1; i < procCount; i++) {
        p_displ[i] = p_displ[i - 1] + p_count[i - 1];
		}
	}
    numelems = count * str;
    if ((tmpcount != 0) && (procRank < tmpcount)) {
        numelems += str;
    }
    int* rbuf = new int[numelems];
    MPI_Scatterv(bigmas, p_count, p_displ, MPI_INT, rbuf, numelems, MPI_INT, 0, MPI_COMM_WORLD);
    int blok = numelems / str;
    int* tmpmax = new int[blok];
    findmax(rbuf, blok, str, tmpmax);
    if (procRank == 0) {
        for (int i = 0; i < procCount; i++) {
            p_count[i] = p_count[i] / str;
            p_displ[i] = p_displ[i] / str;
        }
    }
    MPI_Gatherv(tmpmax, blok, MPI_INT, resbuf, p_count, p_displ, MPI_INT, 0, MPI_COMM_WORLD);
    if (procRank == 0) {
        delete[] p_count;
        delete[] p_displ;
    }
    delete[] rbuf;
    delete[] tmpmax;
}