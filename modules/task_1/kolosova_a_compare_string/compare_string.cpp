// Copyright 2021 Kolosova Alena
#include <mpi.h>
#include <cmath>
#include <cstring>
#include <ctime>
#include <climits>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/kolosova_a_compare_string/compare_string.h"


char* generateString(int sz, int spread) {
    std::srand(std::time(0));
    // add random component to str length
    sz = sz + rand() % spread;
    char* str = new char[sz];
    for (int i = 0; i < sz - 1; i++) {
        str[i] = std::rand() % CHAR_MAX;
    }
    str[sz - 1] = 0;
    return str;
}

int parCompareString(const char* str1, const char* str2) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

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

    int local_res = seqCompareString(rbuf1, rbuf2);

    if (rank != 0)
        MPI_Send(&local_res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Status stat;
            MPI_Recv(results + 1 + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &stat);
        }
        results[1] = local_res;

        char* strlft1 = new char[leftover];
        char* strlft2 = new char[leftover];
        memcpy(strlft1, str1, leftover * sizeof(char));
        memcpy(strlft2, str2, leftover * sizeof(char));

        results[0]= seqCompareString(strlft1, strlft2);
    }

    bool ans[3] = { true, true, true };

    for (int i = 0; i <= size; i++) {
        if (!results[i]) ans[1]=false;
        if (results[i] > -1) ans[2] = false;
        if (results[i] < 1) ans[0] = false;
    }
    for (int i = 0; i < 3; i++) {
        if (ans[i] == 0) return i - 1;
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

