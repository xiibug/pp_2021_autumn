// Copyright 2021 Kolosova Alena
#include <mpi.h>
#include <cmath>
#include <cstring>
#include <climits>
#include <algorithm>
#include <random>
#include "gtest/gtest.h"
#include "../../../modules/task_1/kolosova_a_compare_string/compare_string.h"


char* generateString(int sz, int spread) {
    std::random_device dev;
    std::mt19937 rgen(dev());
    // add random component to str length
    if (spread)
        sz = sz + rgen() % spread;
    char* str = new char[sz];
    for (int i = 0; i < sz - 1; i++) {
        str[i] = rgen() % 52 + 'A';
    }
    str[sz - 1] = 0;
    return str;
}

int parCompareString(const char* str1, const char* str2) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::cerr << "[          ] comm_size = " << size << std::endl;

    int len = (strlen(str1) < strlen(str2)) ? strlen(str1) : strlen(str2);
    int blocksize = len / size;
    int leftover = len % size;

    char* rbuf1 = new char[blocksize];
    char* rbuf2 = new char[blocksize];

    int* results = new int[size + 1];

    MPI_Scatter(str1 + leftover, blocksize, MPI_CHAR,
        rbuf1, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2 + leftover, blocksize, MPI_CHAR,
        rbuf2, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);

    // std::cerr << "[          ] rank = " << rank << "rbuf1 = " << rbuf1 << std::endl;
    // std::cerr << "[          ] rank = " << rank << "rbuf2 = " << rbuf2 << std::endl;

    int local_res = seqCompareString(rbuf1, rbuf2);

    if (rank != 0)
        MPI_Send(&local_res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Status stat;
            MPI_Recv(results + 1 + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &stat);
        }
        results[1] = local_res;
        
        int i = 1;

        if (leftover) {
            i = 0;
            char* strlft1 = new char[leftover];
            char* strlft2 = new char[leftover];
            memcpy(strlft1, str1, leftover * sizeof(char));
            memcpy(strlft2, str2, leftover * sizeof(char));

            results[0] = seqCompareString(strlft1, strlft2);
        }

        for (; i <= size; i++) {
            if (!results[i]) return results[i];
        }
        if (strlen(str1) < strlen(str2))
            return -1;
        if (strlen(str1) > strlen(str2))
            return 1;
        return 0;
    }
    return 2;
}

int seqCompareString(const char* str1, const char* str2) {
    int ans = strcmp(str1, str2);
    if (ans) {
        ans /= abs(ans);
    }
    return ans;
}

