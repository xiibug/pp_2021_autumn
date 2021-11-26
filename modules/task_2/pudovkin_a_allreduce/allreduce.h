// Copyright 2021 Pudovkin Artem
#ifndef MODULES_TASK_2_PUDOVKIN_A_ALLREDUCE_ALLREDUCE_H_
#define MODULES_TASK_2_PUDOVKIN_A_ALLREDUCE_ALLREDUCE_H_

#include <mpi.h>
#include <numeric>
#include <algorithm>
#include <random>
#include <vector>

using std::vector;

int Allreduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);

template<typename type>
vector<type> getRandomVector(const size_t size)  {
    vector<type> vec(size);
    std::random_device dev;
    std::mt19937 gen(dev());

    for (size_t i = 0; i < size; ++i) {
        vec[i] = static_cast<type>(gen() % 100);
    }
    return vec;
}

template<typename type>
type maxVector(const vector<type>& vec) {
    return *std::max_element(vec.begin(), vec.end());
}
template<typename type>
type minVector(const vector<type>& vec) {
    return *std::min_element(vec.begin(), vec.end());
}
template<typename type>
type sumVector(const vector<type>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0);
}

template<typename type>
MPI_Datatype selectMPIDatatype() {
    MPI_Datatype datatype = MPI_DATATYPE_NULL;

    if (std::is_same<type, int>::value) {
        datatype = MPI_INT;
    } else if (std::is_same<type, float>::value) {
        datatype = MPI_FLOAT;
    } else if (std::is_same<type, double>::value) {
        datatype = MPI_DOUBLE;
    }

    return datatype;
}

template<typename type>
type parallelMax(const vector<type>& vec, const size_t sizeVec) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Datatype datatype = selectMPIDatatype<type>();
    const int delta = sizeVec / size;
    vector<type> localVec(delta);
    type localMax = 0, globalMax = 0;

    MPI_Scatter(vec.data(), delta, datatype,
        localVec.data(), delta, datatype, 0, MPI_COMM_WORLD);

    localMax = maxVector<type>(localVec);

    Allreduce(&localMax, &globalMax, 1, datatype, MPI_MAX, MPI_COMM_WORLD);

    if (rank == 0) {
        if (size != 1) {
            int tail = sizeVec - size * delta;
            if (tail) {
                localVec = vector<type>(vec.begin() + (sizeVec - tail), vec.end());
                localMax = maxVector<type>(localVec);

                if (localMax > globalMax) {
                    globalMax = localMax;
                }
            }
        }
    }

    return globalMax;
}
template<typename type>
type parallelMin(const vector<type>& vec, const size_t sizeVec) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Datatype datatype = selectMPIDatatype<type>();

    const int delta = sizeVec / size;
    vector<type> localVec(delta);
    type localMin = 0, globalMin = 0;

    MPI_Scatter(vec.data(), delta, datatype,
        localVec.data(), delta, datatype, 0, MPI_COMM_WORLD);

    localMin = minVector<type>(localVec);

    Allreduce(&localMin, &globalMin, 1, datatype, MPI_MIN, MPI_COMM_WORLD);

    if (rank == 0) {
        if (size != 1) {
            int tail = sizeVec - size * delta;
            if (tail) {
                localVec = vector<type>(vec.begin() + (sizeVec - tail), vec.end());
                localMin = minVector<type>(localVec);

                if (localMin < globalMin) {
                    globalMin = localMin;
                }
            }
        }
    }
    return globalMin;
}
template<typename type>
type parallelSum(const vector<type>& vec, const size_t sizeVec) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Datatype datatype = selectMPIDatatype<type>();

    const int delta = sizeVec / size;
    vector<type> localVec(delta);
    type localSum = 0, globalSum = 0;

    MPI_Scatter(vec.data(), delta, datatype,
        localVec.data(), delta, datatype, 0, MPI_COMM_WORLD);

    localSum = sumVector<type>(localVec);

    Allreduce(&localSum, &globalSum, 1, datatype, MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0) {
        if (size != 1) {
            int tail = sizeVec - size * delta;
            if (tail) {
                localVec = vector<type>(vec.begin() + (sizeVec - tail), vec.end());
                localSum = sumVector<type>(localVec);

                globalSum += localSum;
            }
        }
    }
    return globalSum;
}

#endif  // MODULES_TASK_2_PUDOVKIN_A_ALLREDUCE_ALLREDUCE_H_
