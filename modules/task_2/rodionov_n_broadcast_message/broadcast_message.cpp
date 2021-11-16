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
                MPI_Send(sendbuf, count, type, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    void* recvbuf;
    switch (type)
    {
    case MPI_INT:
        recvbuf = new int[count];
        break;
    case MPI_DOUBLE:
        recvbuf = new double[count];
        break;
    case MPI_FLOAT:
        recvbuf = new float[count];
        break;
    }
    if (rank != root) {

        MPI_Status status{};
        MPI_Recv(recvbuf, count, type, root, 0, MPI_COMM_WORLD, &status);
        if (type == MPI_INT) {
            int val = 0;
            for (int i = 0; i < count; i++) {
                val += reinterpret_cast<int*>(recvbuf)[i];
            }
            MPI_Send(&val, 1, type, root, 1, MPI_COMM_WORLD);
        }
        else if (type == MPI_FLOAT) {
            float val = 0;
            for (int i = 0; i < count; i++) {
                val += reinterpret_cast<float*>(recvbuf)[i];
            }
            MPI_Send(&val, 1, type, root, 1, MPI_COMM_WORLD);
        }
        else if (type == MPI_DOUBLE) {
            double val = 0;
            for (int i = 0; i < count; i++) {
                val += reinterpret_cast<double*>(recvbuf)[i];
            }
            MPI_Send(&val, 1, type, root, 1, MPI_COMM_WORLD);
        }
    }
    else {
        if (type == MPI_INT) {
            int val = 0;
            for (int i = 0; i < count; i++) {
                val += reinterpret_cast<int*>(recvbuf)[i];
            }
        }
        else if (type == MPI_FLOAT) {
            float val = 0;
            for (int i = 0; i < count; i++) {
                val += reinterpret_cast<float*>(recvbuf)[i];
            }
        }
        else if (type == MPI_DOUBLE) {
            double val = 0;
            for (int i = 0; i < count; i++) {
                val += reinterpret_cast<double*>(recvbuf)[i];
            }
        }
    }

    if (rank == root) {
        if (type == MPI_INT) {
            int* result = new int[commSize];
            for (int i = 1; i < commSize; i++) {
                result[i] = 0;
                if (i != root) {
                    MPI_Status status{};
                    MPI_Recv(result + i, 1, type, i, 1, MPI_COMM_WORLD, &status);
                }
            }
            int sum = 0;
            for (int i = 0; i < commSize; i++) {
                sum += result[i];
            }
            *reinterpret_cast<int*>(outSum) = sum;
        }
        else if (type == MPI_FLOAT) {
            float* result = new float[commSize];
            for (int i = 1; i < commSize; i++) {
                result[i] = 0;
                if (i != root) {
                    MPI_Status status{};
                    MPI_Recv(result + i, 1, type, i, 1, MPI_COMM_WORLD, &status);
                }
            }
            float sum = 0;
            for (int i = 1; i < commSize; i++) {
                sum += result[i];
            }
            *reinterpret_cast<float*>(outSum) = sum;
        }
        else if (type == MPI_DOUBLE) {
            double* result = new double[commSize];

            for (int i = 0; i < commSize; i++) {
                result[i] = 0;
                if (i != root) {
                    MPI_Status status{};
                    MPI_Recv(result + i, 1, type, i, 1, MPI_COMM_WORLD, &status);
                }
            }
            double sum = 0;
            for (int i = 0; i < commSize; i++) {
                sum += result[i];
            }
            *reinterpret_cast<double*>(outSum) = sum;
        }

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