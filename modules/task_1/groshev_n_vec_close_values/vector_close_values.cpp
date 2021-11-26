// Copyright 2021 Groshev Nickolay
#include <mpi.h>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include "../../../modules/task_1/groshev_n_vec_close_values/vector_close_values.h"

std::vector<int> getRandomVector(int vecSize) {
    std::random_device stage;
    std::vector<int> Vec(vecSize);
    std::mt19937 load(stage());
    for (int i = 0; i < vecSize; i++) {
        Vec[i] = load() % 100;
    }
    return Vec;
}


int getMinDiffByOneProc(std::vector <int> vector) {
    int minDiff = INT_MAX;
    if ((vector.size() == 1) || (vector.size() == 0)) {
        return 0;
    } else {
        for (int i = 0; i < static_cast<int>(vector.size() - 1); i++) {
            if (minDiff > abs(vector[i] - vector[i + 1]))
                minDiff = abs(vector[i] - vector[i + 1]);
        }
    }
    return minDiff;
}

int getMinDiffParallel(std::vector <int> someVector) {
    int minDiff = INT_MAX;
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    int bufSize = someVector.size() - 1;
    int elForProc = bufSize / size;
    int ost = bufSize % size;

    if (rank == 0) {
        if (elForProc > 0) {
            for (int procNum = 1; procNum < size; procNum++)
               MPI_Send(&someVector[ost] + elForProc * procNum,
                   elForProc + 1, MPI_INT, procNum, 0, MPI_COMM_WORLD);
        }
    } else {
        if (elForProc > 0) {
            std::vector<int> tmpVec(elForProc + 1);
            MPI_Recv(&tmpVec[0], elForProc + 1, MPI_INT,
                0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            int tmpMinDiff = getMinDiffByOneProc(tmpVec);
            MPI_Send(&tmpMinDiff, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    if (rank == 0) {
        int tmpMinDiff;
        std::vector<int> tmpVec(someVector.begin(), someVector.begin() + 1 + elForProc + ost);
        minDiff = getMinDiffByOneProc(tmpVec);
        if (elForProc > 0) {
            for (int procNum = 1; procNum < size; procNum++) {
                MPI_Recv(&tmpMinDiff, 1, MPI_INT,
                    procNum, 0, MPI_COMM_WORLD, &status);
                if (minDiff > tmpMinDiff)
                    minDiff = tmpMinDiff;
            }
        }
    }
    return minDiff;
}
