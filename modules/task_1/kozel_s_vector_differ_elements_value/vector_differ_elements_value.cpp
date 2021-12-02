// Copyright 2021 Kozel Svetlana
#include <mpi.h>
#include <random>
#include "../../../modules/task_1/kozel_s_vector_differ_elements_value/vector_differ_elements_value.h"

std::vector<int> fillVector(const int size_) {
    std::vector<int> vector(size_);
    std::random_device dev;
    std::mt19937 mt(dev());
    for (int i = 0; i < size_; i++) {
        vector[i] = -100 + mt() % 1000;
    }
    return vector;
}

int differElementsValue(const std::vector<int>& vector) {
    if (vector.size() > 1) {
        int max = vector[0];
        for (int i = 0; i < static_cast<int>(vector.size() - 1); i++) {
            int val = abs(vector[i] - vector[i + 1]);
            if (max < val) {
                max = val;
            }
        }
        return max;
    }

    return 0;
}

int paralleldifferElementsValue(const std::vector<int>& vector, const int size) {
    int proc, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int block = size / proc;
    int ostatok = size % proc;

    if (rank < ostatok) {
        block++;
    }

    int localMax = -9999999;
    int globalMax;

    // if proc > size
    if (ostatok > block) {
        if (rank == 0) {
            localMax = differElementsValue(vector);
        }
        return localMax;
    }

    std::vector<int> blockVector(proc);
    std::vector<int> sdvig(proc);
    std::vector<int> resultData(block);
    if (rank == 0) {
        for (int i = 0; i < proc; i++) {
            blockVector[i] = vector.size() / proc;
            if (i < proc - 1) {
                sdvig[i + 1] = sdvig[i] + blockVector[i];
            }
        }
    }
    MPI_Scatterv(reinterpret_cast<const void*>(vector.data()), blockVector.data(), sdvig.data(),
        MPI_INT, resultData.data(), block, MPI_INT, 0, MPI_COMM_WORLD);

    localMax = differElementsValue(resultData);

    MPI_Reduce(reinterpret_cast<void*>(&localMax), reinterpret_cast<void*>(&globalMax),
        1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    return globalMax;
}
