// Copyright 2021 Zharkov Andrey


#include <mpi.h>
#include <random>
#include "../../../modules/task_1/zharkov_a_vec_min/vec_min.h"

double* getRandomVector(double* arr, int n, int interval) {
    std::random_device dev;
    std::mt19937 gen(dev());
    arr = new double[n];
    for (int i = 0; i < n; i++)
        arr[i] = gen() % interval;
    return arr;
}

double Get_Min(double* arr, int n) {
    double min = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

double ParallCulc(double* a, int n) {
    int* sendcounts = nullptr;
    int* loc_start = nullptr;
    int size, rank, buf_size;
    double loc_min, gl_min;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        sendcounts = new int[size];
        loc_start = new int[size];
        int ost = n % size;
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sendcounts[i] = (n / size);
            if (ost > 0) {
                sendcounts[i] += 1;
                ost--;
            }
            loc_start[i] = sum;
            sum += sendcounts[i];
        }
    }

    MPI_Scatter(sendcounts, 1, MPI_INT, &buf_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double* buf = new double[buf_size];

    MPI_Scatterv(a, sendcounts, loc_start, MPI_DOUBLE, buf, buf_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    loc_min = Get_Min(buf, buf_size);

    MPI_Reduce(&loc_min, &gl_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        delete[] loc_start;
        delete[] sendcounts;
    }
    delete[] buf;

    return gl_min;
}
