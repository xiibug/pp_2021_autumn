// Copyright 2021 Pudovkin Artem
#include <mpi.h>
#include <cstring>
#include "../../..//modules/task_2/pudovkin_a_allreduce/allreduce.h"

void permormMPIOperation(void* buffer, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) {
    if (op == MPI_MAX) {
        for (int i = 0; i < count; i++) {
            if (datatype == MPI_INT)
                static_cast<int*>(recvbuf)[i] = std::max(static_cast<int*>(recvbuf)[i], static_cast<int*>(buffer)[i]);
            if (datatype == MPI_FLOAT)
                static_cast<float*>(recvbuf)[i] = std::max(static_cast<float*>(recvbuf)[i], static_cast<float*>(buffer)[i]);
            if (datatype == MPI_DOUBLE)
                static_cast<double*>(recvbuf)[i] = std::max(static_cast<double*>(recvbuf)[i], static_cast<double*>(buffer)[i]);
        }
    }
    if (op == MPI_MIN) {
        for (int i = 0; i < count; i++) {
            if (datatype == MPI_INT)
                static_cast<int*>(recvbuf)[i] = std::min(static_cast<int*>(recvbuf)[i], static_cast<int*>(buffer)[i]);
            if (datatype == MPI_FLOAT)
                static_cast<float*>(recvbuf)[i] = std::min(static_cast<float*>(recvbuf)[i], static_cast<float*>(buffer)[i]);
            if (datatype == MPI_DOUBLE)
                static_cast<double*>(recvbuf)[i] = std::min(static_cast<double*>(recvbuf)[i], static_cast<double*>(buffer)[i]);
        }
    }
    if (op == MPI_SUM) {
        for (int i = 0; i < count; i++) {
            if (datatype == MPI_INT) static_cast<int*>(recvbuf)[i] += static_cast<int*>(buffer)[i];
            if (datatype == MPI_FLOAT) static_cast<float*>(recvbuf)[i] += static_cast<float*>(buffer)[i];
            if (datatype == MPI_DOUBLE) static_cast<double*>(recvbuf)[i] += static_cast<double*>(buffer)[i];
        }
    }
}

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
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    if (datatype == MPI_INT) memcpy(recvbuf, sendbuf, count * sizeof(int));
    else if (datatype == MPI_FLOAT) memcpy(recvbuf, sendbuf, count * sizeof(float));
    else if (datatype == MPI_DOUBLE) memcpy(recvbuf, sendbuf, count * sizeof(double));

    if (size != 1) {
        int* bufferInt = nullptr;
        float* bufferFloat = nullptr;
        double* bufferDouble = nullptr;

        if (rank != 0) {
            if (datatype == MPI_INT) bufferInt = new int[count];
            else if (datatype == MPI_FLOAT) bufferFloat = new float[count];
            else if (datatype == MPI_DOUBLE) bufferDouble = new double[count];
        }

        if (rank == 0) {
            MPI_Send(recvbuf, count, datatype, rank + 1, 0, comm);
        } else if (rank != size - 1) {
            if (datatype == MPI_INT) {
                MPI_Recv(bufferInt, count, datatype, rank - 1, 0, comm, MPI_STATUSES_IGNORE);
                permormMPIOperation(bufferInt, recvbuf, count, datatype, op, comm);
            } else if (datatype == MPI_FLOAT) {
                MPI_Recv(bufferFloat, count, datatype, rank - 1, 0, comm, MPI_STATUSES_IGNORE);
                permormMPIOperation(bufferFloat, recvbuf, count, datatype, op, comm);
            } else if (datatype == MPI_DOUBLE) {
                MPI_Recv(bufferDouble, count, datatype, rank - 1, 0, comm, MPI_STATUSES_IGNORE);
                permormMPIOperation(bufferDouble, recvbuf, count, datatype, op, comm);
            }
            MPI_Send(recvbuf, count, datatype, rank + 1, 0, comm);
        } else {
            if (datatype == MPI_INT) {
                MPI_Recv(bufferInt, count, datatype, rank - 1, 0, comm, MPI_STATUSES_IGNORE);
                permormMPIOperation(bufferInt, recvbuf, count, datatype, op, comm);
            } else if (datatype == MPI_FLOAT) {
                MPI_Recv(bufferFloat, count, datatype, rank - 1, 0, comm, MPI_STATUSES_IGNORE);
                permormMPIOperation(bufferFloat, recvbuf, count, datatype, op, comm);
            } else if (datatype == MPI_DOUBLE) {
                MPI_Recv(bufferDouble, count, datatype, rank - 1, 0, comm, MPI_STATUSES_IGNORE);
                permormMPIOperation(bufferDouble, recvbuf, count, datatype, op, comm);
            }
        }

        if (rank == size - 1) {
            MPI_Send(recvbuf, count, datatype, rank - 1, 0, comm);
        } else if (rank != 0) {
            MPI_Recv(recvbuf, count, datatype, rank + 1, 0, comm, MPI_STATUSES_IGNORE);
            MPI_Send(recvbuf, count, datatype, rank - 1, 0, comm);
        } else {
            MPI_Recv(recvbuf, count, datatype, rank + 1, 0, comm, MPI_STATUSES_IGNORE);
        }

        if (rank != 0) {
            if (datatype == MPI_INT) delete[] bufferDouble;
            else if (datatype == MPI_FLOAT) delete[] bufferFloat;
            else if (datatype == MPI_DOUBLE) delete[] bufferInt;
        }
    }

    return MPI_SUCCESS;
}
