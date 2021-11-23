// Copyright 2021 Pudovkin Artem
#include <mpi.h>
#include <cstring>
#include "../../..//modules/task_2/pudovkin_a_allreduce/allreduce.h"

int Allreduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) {
    if (recvbuf == nullptr)
        return MPI_ERR_BUFFER;
    if (count <= 0)
        return MPI_ERR_COUNT;
    if ((datatype != MPI_INT) && (datatype != MPI_FLOAT) && (datatype != MPI_DOUBLE))
        return MPI_ERR_TYPE;
    if ((op != MPI_MAX) && (op != MPI_MIN) && (op != MPI_SUM))
        return MPI_ERR_OP;

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* bufferInt;
    float* bufferFloat;
    double* bufferDouble;

    if (rank != 0) {
        MPI_Send(sendbuf, count, datatype, 0, 0, comm);
    }

    if (rank == 0) {
        if (datatype == MPI_INT) memcpy(recvbuf, sendbuf, count * sizeof(int));
        else if (datatype == MPI_FLOAT) memcpy(recvbuf, sendbuf, count * sizeof(float));
        else if (datatype == MPI_DOUBLE) memcpy(recvbuf, sendbuf, count * sizeof(double));

        if (datatype == MPI_INT) {
            bufferInt = new int[count];
        } else if (datatype == MPI_FLOAT) {
            bufferFloat = new float[count];
        } else if (datatype == MPI_DOUBLE) {
            bufferDouble = new double[count];
        }

        for (int proc = 1; proc < size; proc++) {
            MPI_Status status;
            if (datatype == MPI_INT)
                MPI_Recv(bufferInt, count, datatype, proc, 0, comm, &status);
            if (datatype == MPI_FLOAT)
                MPI_Recv(bufferFloat, count, datatype, proc, 0, comm, &status);
            if (datatype == MPI_DOUBLE)
                MPI_Recv(bufferDouble, count, datatype, proc, 0, comm, &status);

            if (op == MPI_MAX) {
                for (int i = 0; i < count; i++) {
                    if (datatype == MPI_INT) 
                        static_cast<int*>(recvbuf)[i] = std::max(static_cast<int*>(recvbuf)[i], bufferInt[i]);
                    if (datatype == MPI_FLOAT) 
                        static_cast<float*>(recvbuf)[i] = std::max(static_cast<float*>(recvbuf)[i], bufferFloat[i]);
                    if (datatype == MPI_DOUBLE) 
                        static_cast<double*>(recvbuf)[i] = std::max(static_cast<double*>(recvbuf)[i], bufferDouble[i]);
                }
            }
            if (op == MPI_MIN) {
                for (int i = 0; i < count; i++) {
                    if (datatype == MPI_INT) 
                        static_cast<int*>(recvbuf)[i] = std::min(static_cast<int*>(recvbuf)[i], bufferInt[i]);
                    if (datatype == MPI_FLOAT) 
                        static_cast<float*>(recvbuf)[i] = std::min(static_cast<float*>(recvbuf)[i], bufferFloat[i]);
                    if (datatype == MPI_DOUBLE) 
                        static_cast<double*>(recvbuf)[i] = std::min(static_cast<double*>(recvbuf)[i], bufferDouble[i]);
                }
            }
            if (op == MPI_SUM) {
                for (int i = 0; i < count; i++) {
                    if (datatype == MPI_INT) static_cast<int*>(recvbuf)[i] += bufferInt[i];
                    if (datatype == MPI_FLOAT) static_cast<float*>(recvbuf)[i] += bufferFloat[i];
                    if (datatype == MPI_DOUBLE) static_cast<double*>(recvbuf)[i] += bufferDouble[i];
                }
            }
        }

        for (int proc = 1; proc < size; proc++) {
            MPI_Send(recvbuf, count, datatype, proc, 0, comm);
        }
    }

    if (rank != 0) {
        MPI_Status status;
        MPI_Recv(recvbuf, count, datatype, 0, 0, comm, &status);
    }

    return MPI_SUCCESS;
}
