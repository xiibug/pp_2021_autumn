// Copyright 2021 Sablin Alexander
#include <random>
#include "../../../modules/task_2/sablin_a_all_reduce/all_reduce.h"
#include <mpi.h>
#include <iostream>

int Allreduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype type,
    MPI_Op Op, MPI_Comm Comm)
{
    int FuncNum, FuncRank;
    int root;
    MPI_Comm_size(MPI_COMM_WORLD, &FuncNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &FuncRank);
    if (FuncRank == 0) {

        //  do
        //  {
        //    std::cout << "Enter a root: " << std::endl;
        //    std::cin >> root;
        //  } while ((root >= FuncNum) || (root < 0));

        std::random_device dev;
        std::mt19937 gen(dev());
        root = gen() % FuncNum;
    }
    MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (FuncRank == root) {
        int type_num;
        switch (type) {
        case MPI_INT: type_num = sizeof(int); break;
        case MPI_DOUBLE: type_num = sizeof(double); break;
        case MPI_FLOAT: type_num = sizeof(float); break;
        }
        void* buf = new char[type_num * count];
        void* tmp = new char[type_num * count];

        int counter = 0;
        if (type == MPI_INT) {
            for (int iter = 0; iter < FuncNum; iter++) {
                if (iter != root) {
                    MPI_Recv(buf, count, type, MPI_ANY_SOURCE, 1, Comm, MPI_STATUS_IGNORE);
                } else {
                    for (int i = 0; i < count; i++) {
                        ((int*)buf)[i] = ((int*)sendbuf)[i];
                    }
                }
                if (counter == 0) {
                    for (int i = 0; i < count; i++) {
                        ((int*)tmp)[i] = ((int*)buf)[i];
                    }
                    counter++;
                } else {
                    switch (Op) {
                    case MPI_SUM: {
                        for (int i = 0; i < count; i++) {
                            ((int*)tmp)[i] += ((int*)buf)[i];
                        }
                    } break;
                    case MPI_MAX: {
                        for (int i = 0; i < count; i++) {
                            if (((int*)buf)[i] > ((int*)tmp)[i]) {
                                ((int*)tmp)[i] = ((int*)buf)[i];
                            }
                        }
                    } break;
                    case MPI_MIN: {
                        for (int i = 0; i < count; i++) {
                            if (((int*)buf)[i] < ((int*)tmp)[i]) {
                                ((int*)tmp)[i] = ((int*)buf)[i];
                            }
                        }
                    } break;
                    case MPI_PROD: {
                        for (int i = 0; i < count; i++) {
                            ((int*)tmp)[i] *= ((int*)buf)[i];
                        }
                    } break;
                    }
                }
            }
            for (int i = 0; i < count; i++) {
                ((int*)recvbuf)[i] = ((int*)tmp)[i];
            }
        } else if (type == MPI_DOUBLE) {
            for (int iter = 0; iter < FuncNum; iter++) {
                if (iter != root) {
                    MPI_Recv(buf, count, type, MPI_ANY_SOURCE, 1, Comm, MPI_STATUS_IGNORE);
                } else {
                    for (int i = 0; i < count; i++) {
                        ((double*)buf)[i] = ((double*)sendbuf)[i];
                    }
                }
                if (counter == 0) {
                    for (int i = 0; i < count; i++) {
                        ((double*)tmp)[i] = ((double*)buf)[i];
                    }
                    counter++;
                } else {
                    switch (Op) {
                    case MPI_SUM: {
                        for (int i = 0; i < count; i++) {
                            ((double*)tmp)[i] += ((double*)buf)[i];
                        }
                    } break;
                    case MPI_MAX: {
                        for (int i = 0; i < count; i++) {
                            if (((double*)buf)[i] > ((double*)tmp)[i]) {
                                ((double*)tmp)[i] = ((double*)buf)[i];
                            }
                        }
                    } break;
                    case MPI_MIN: {
                        for (int i = 0; i < count; i++) {
                            if (((double*)buf)[i] < ((double*)tmp)[i]) {
                                ((double*)tmp)[i] = ((double*)buf)[i];
                            }
                        }
                    } break;
                    case MPI_PROD: {
                        for (int i = 0; i < count; i++) {
                            ((double*)tmp)[i] *= ((double*)buf)[i];
                        }
                    } break;
                    }
                }
            }
            for (int i = 0; i < count; i++) {
                ((double*)recvbuf)[i] = ((double*)tmp)[i];
            }
        } else {
            for (int iter = 0; iter < FuncNum; iter++) {
                if (iter != root) {
                    MPI_Recv(buf, count, type, MPI_ANY_SOURCE, 1, Comm, MPI_STATUS_IGNORE);
                } else {
                    for (int i = 0; i < count; i++) {
                        ((float*)buf)[i] = ((float*)sendbuf)[i];
                    }
                }
                if (counter == 0) {
                    for (int i = 0; i < count; i++) {
                        ((float*)tmp)[i] = ((float*)buf)[i];
                    }
                    counter++;
                } else {
                    switch (Op) {
                    case MPI_SUM: {
                        for (int i = 0; i < count; i++) {
                            ((float*)tmp)[i] += ((float*)buf)[i];
                        }
                    } break;
                    case MPI_MAX: {
                        for (int i = 0; i < count; i++) {
                            if (((float*)buf)[i] > ((float*)tmp)[i]) {
                                ((float*)tmp)[i] = ((float*)buf)[i];
                            }
                        }
                    } break;
                    case MPI_MIN: {
                        for (int i = 0; i < count; i++) {
                            if (((float*)buf)[i] < ((float*)tmp)[i]) {
                                ((float*)tmp)[i] = ((float*)buf)[i];
                            }
                        }
                    } break;
                    case MPI_PROD: {
                        for (int i = 0; i < count; i++) {
                            ((float*)tmp)[i] *= ((float*)buf)[i];
                        }
                    } break;
                    }
                }
            }
            for (int i = 0; i < count; i++) {
                ((float*)recvbuf)[i] = ((float*)tmp)[i];
            }
        }
        delete[] buf;
        delete[] tmp;
    }
    else {
        MPI_Send(sendbuf, count, type, root, 1, Comm);
        MPI_Recv(recvbuf, count, type, MPI_ANY_SOURCE, 1, Comm, MPI_STATUS_IGNORE);
    }
    int dif = FuncRank - root;
    if (dif < 0) {
        dif = FuncNum + dif;
    }
    int ui = ceil(log(dif + 1) / log(2));
    for (int i = ui; ((int)pow(2, i) + dif < FuncNum); i++) {
        int num = (int)pow(2, i) + dif + root;
        if (num >= FuncNum) {
            num = num - FuncNum;
        }
        MPI_Send(recvbuf, count, type, num, 1, Comm);
    }
    return 0;
}

template<typename T>
T* getRandomVector(T* rand_vec, int n, int dia, bool flag) {
    rand_vec = new T[n];
    if (flag) {
        std::random_device dev;
        std::mt19937 gen(dev());
        for (int i = 0; i < n; i++) {
            rand_vec[i] = static_cast<T>(gen() % dia);
        }
    }
    return rand_vec;
}

template
int* getRandomVector<int>(int* rand_vec, int n, int dia, bool flag);

template
double* getRandomVector<double>(double* rand_vec, int n, int dia, bool flag);

template
float* getRandomVector<float>(float* rand_vec, int n, int dia, bool flag);
