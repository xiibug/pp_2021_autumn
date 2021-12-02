// Copyright 2021 Pinezhanin Evgeny
#include <mpi.h>
#include <random>
#include <vector>
#include <algorithm>
#include "../../../modules/task_2/pinezhanin_e_bubble_sort_odd_even/bubble_sort_odd_even.h"

std::vector<int> getRandomVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int  i = 0; i < size; i++) {
        vec[i] = gen() % 1000;
    }
    return vec;
}

std::vector<int> BubbleSortOddEvenParallel(std::vector<int> vec) {
    int size, rank;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int sendCounts[size], displs[size], n;

    n = vec.size();
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < size; i++) {
        sendCounts[i] = n / size;
    }
    for (int i = 0; i < n % size; i++) {
        sendCounts[i] += 1;
    }
    displs[0] = 0;
    for (int i = 1; i < size; i++) {
        displs[i] = displs[i - 1] + sendCounts[i - 1];
    }

    int part_vec[sendCounts[rank]];
    int odd, a;
    MPI_Scatterv(vec.data(), sendCounts, displs, MPI_INT, part_vec, sendCounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            odd = !(displs[rank] % 2);
        } else {
            odd = displs[rank] % 2;
        }
        for (int j = odd; j < sendCounts[rank]; j += 2) {
            if (j == sendCounts[rank] - 1) {
                if (rank != size - 1) {
                    MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                    if (part_vec[sendCounts[rank] - 1] > a) std::swap(part_vec[sendCounts[rank] - 1], a);
                    MPI_Send(&a, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                }
                break;
            }
            if (part_vec[j] > part_vec[j + 1]) {
                std::swap(part_vec[j], part_vec[j + 1]);
            }
        }
        if (odd && rank != 0) {
            MPI_Send(&(part_vec[0]), 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&(part_vec[0]), 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Gatherv(part_vec, sendCounts[rank], MPI_INT, vec.data(), sendCounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    return vec;
}

std::vector<int> BubbleSortOddEvenSequential(std::vector<int> vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            for (int j = 1; j < n - 1; j += 2) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        } else {
            for (int j = 0; j < n - 1; j += 2) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }
    return vec;
}
