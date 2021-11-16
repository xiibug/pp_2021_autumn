// Copyright 2021 TexHik620953
#include <mpi.h>
#include <list>
#include <cstring>
#include <iostream>
#include <random>
#include "../../../modules/task_2/rodionov_n_broadcast_message/broadcast_message.h"


int BroadcastSum(
    void* sendbuf,
    void* outSum,
    int count,
    int root,
    MPI_Datatype type
) {
    int commSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == root) {
        for (int i = 0; i < commSize; i++) {
            if (i != root) {
                MPI_Send(sendbuf, count * commSize, type, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    double* recvbuf = new double[count * commSize];
    if (rank != root) {
        MPI_Status status{};
        MPI_Recv(recvbuf, count * commSize, type, root, 0, MPI_COMM_WORLD, &status);
    }
    else {
        recvbuf = (double*)sendbuf;
    }
    //Now all processes has same data in recvbuffer
    //Calculate summ
    double local_sum = 0;
    for (int i = 0; i < count; i++) {
        local_sum += recvbuf[rank * count + i];
    }
    if (rank != root) {
        //Send data to root process
        MPI_Send(&local_sum, 1, type, root, 1, MPI_COMM_WORLD);
    }
    
    //Receive and summ data
    if (rank == root) {
        double global_sum = local_sum;
        //Receive data from non-root
        for (int i = 0; i < commSize; i++) {
            if (i != root) {
                double process_sum = 0;
                MPI_Status status{};
                MPI_Recv(&process_sum, 1, type, i, 1, MPI_COMM_WORLD, &status);
                global_sum += process_sum;
            }
        }

        *reinterpret_cast<double*>(outSum) = global_sum;
    }
    return 0;
}

template<typename T>
T sumSeq(T* arr, int length) {
    T sum = 0;
    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }
    return sum;
}

template<typename T>
T* zerosArray(int length) {
    T* arr = new T[length];
    for (int i = 0; i < length; i++) {
        arr[i] = 0;
    }
    return arr;
}

template<typename T>
T* filledArray(int length, T value) {
    T* arr = new T[length];
    for (int i = 0; i < length; i++) {
        arr[i] = value;
    }
    return arr;
}