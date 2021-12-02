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
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int sendCountsEven[size], displsEven[size];
    int sendCountsOdd[size], displsOdd[size];
    if (vec.size() < 2) {
        return vec;
    }

    int n = vec.size();
    for (int i = 0; i < size; i++) {
        sendCountsEven[i] = (n / 2) / size * 2;
    }
    for (int i = 0; i < (n / 2) % size; i++) {
        sendCountsEven[i] += 2;
    }
    displsEven[0] = 0;
    for (int i = 1; i < size; i++) {
        displsEven[i] = displsEven[i - 1] + sendCountsEven[i - 1];
    }

    for (int i = 0; i < size; i++) {
        sendCountsOdd[i] = ((n - 1) / 2) / size * 2;
    }
    for (int i = 0; i < ((n - 1) / 2) % size; i++) {
        sendCountsOdd[i] += 2;
    }
    displsOdd[0] = 1;
    for (int i = 1; i < size - 1; i++) {
        displsOdd[i] = displsOdd[i - 1] + sendCountsOdd[i - 1];
    }

    for (int i = 0; i < n; i++) {
        if (i % 2) {
            MPI_Scatterv(vec.data(), sendCountsOdd, displsOdd, MPI_INT, 
                         (rank == 0) ? MPI_IN_PLACE : vec.data() + displsOdd[rank], 
                         sendCountsOdd[rank], MPI_INT, 0, MPI_COMM_WORLD);
            for (int j = displsOdd[rank]; j < displsOdd[rank] + sendCountsOdd[rank]; j += 2) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
            MPI_Gatherv((rank == 0) ? MPI_IN_PLACE : vec.data() + displsOdd[rank], 
                         sendCountsOdd[rank], MPI_INT, vec.data(), sendCountsOdd, 
                         displsOdd, MPI_INT, 0, MPI_COMM_WORLD);
        } else {
            MPI_Scatterv(vec.data(), sendCountsEven, displsEven, MPI_INT, 
                         (rank == 0) ? MPI_IN_PLACE : vec.data() + displsEven[rank], 
                         sendCountsEven[rank], MPI_INT, 0, MPI_COMM_WORLD);
            for (int j = displsEven[rank]; j < displsEven[rank] + sendCountsEven[rank]; j += 2) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
            MPI_Gatherv((rank == 0) ? MPI_IN_PLACE : vec.data() + displsEven[rank], 
                         sendCountsEven[rank], MPI_INT, vec.data(), sendCountsEven, 
                         displsEven, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }
    return vec;
}

std::vector<int> BubbleSortOddEvenSequential(std::vector<int> vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
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
