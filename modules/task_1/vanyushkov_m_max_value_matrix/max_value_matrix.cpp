// Copyright 2021 Vanyushkov Maxim
#include <mpi.h>
#include <random>
#include "../../../modules/task_1/vanyushkov_m_max_value_matrix/max_value_matrix.h"

// we will store the matrix in the form of a vector
// referring to the elements of the matrix has the form:
// matrix[a][b] -> matrix[i] <=> i = a * size + b

// fill matrix with random values
void fillMatrixRandValue(int* matrix, int len) {
    if (matrix == nullptr)
        throw "matrix is not allocated";
    // https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distInt(0, 0xFFFFFFFF);
    for (int i = 0; i < len; i++) {
        matrix[i] = static_cast<int>(distInt(rng));
    }
}

// standard search for max element
int sequentialMax(const int* matrix, int len) {
    int maxValue = matrix[0];
    for (int i = 1; i < len; i++) {
        if (matrix[i] > maxValue) {
            maxValue = matrix[i];
        }
    }
    return maxValue;
}

// parallel search for max element
int parallelMax(const int* matrix, int len) {
    // get MPI info
    int procCount = 0, procRank = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    // scattering the matrix
    int elemsForProc = len / procCount + (procRank < len % procCount ? 1 : 0);
    
    int* scnts = nullptr, * displs = nullptr;
    int* rcount = new int[elemsForProc];
    if (procRank == 0) {
        scnts = new int[procCount];
        for (int i = 0; i < procCount; scnts[i++] = len / procCount) {}
        for (int i = 0; i < len % procCount; ++scnts[i++]) {}
        displs = new int[procCount];
        displs[0] = 0;
        for (int i = 1; i < procCount; i++) {
            displs[i] = displs[i - 1] + scnts[i - 1];
        }
    }

    MPI_Scatterv(reinterpret_cast<const void*>(matrix), scnts, displs,
        MPI_INT, rcount, elemsForProc, MPI_INT, 0, MPI_COMM_WORLD);

    // max elements
    int localAlternations = sequentialMax(rcount, elemsForProc);
    int globalAlterations = 0;
    MPI_Reduce(reinterpret_cast<void*>(&localAlternations), reinterpret_cast<void*>(&globalAlterations),
        1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    // releasing memory
    if (procRank == 0) {
        delete[] scnts;
        delete[] displs;
    }

    delete[] rcount;
    return globalAlterations;
}

