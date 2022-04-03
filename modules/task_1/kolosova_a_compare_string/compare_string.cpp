// Copyright 2021 Kolosova Alena
#include <mpi.h>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/kolosova_a_compare_string/compare_string.h"


char* generateString(int sz, int spread) {
    std::srand(std::time(0));
    //add random component to str length
    sz = sz + rand() % spread];
    char* str = new char[sz];
    for (int i = 0; i < sz - 1; i++) {
        str[i] = std::rand() % CHAR_MAX;
    }
    str[sz - 1] = 0;
    return str;
}

bool parCompareString(const char* str1, const char* str2) { 
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int len = (strlen(str1) < strlen(str2)) ? strlen(str1) : strlen(str2);
    int blocksize = len / size;
    int leftover = len % size;
    
    char* rbuf1 = new char[blocksize];
    char* rbuf2 = new char[blocksize];

    bool* results = new bool[size + 1];
    for (int i = 0; i <= size; i++)
        results[i] = 0;

    MPI_Scatter(str1 + leftover, blocksize, MPI_CHAR, 
        rbuf1, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2 + leftover, blocksize, MPI_CHAR, 
        rbuf2, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);

    bool local_res = seq_compare_string(rbuf1, rbuf2);

    if(rank != 0)
        MPI_Send(&local_res, 1, MPI_CXX_BOOL, 0, 0, MPI_COMM_WORLD);

    if(rank==0) {
        for (int i = 1; i < size; i++) {
            MPI_Status stat;
            MPI_Recv(results + 1 + i, 1, MPI_CXX_BOOL, i, 0, MPI_COMM_WORLD, &stat);
        }
        results[1] = local_res;

        char* strlft1 = new char[leftover];
        char* strlft2 = new char[leftover];
        memcpy(strlft1, str1, leftover * sizeof(char));
        memcpy(strlft2, str2, leftover * sizeof(char));

        results[0]= seq_compare_string(strlft1, strlft2);
    }

    for (int i = 0; i <= size; i++) {
        if (!results[i]) return false;
    }
    return true;
}

bool seqCompareString(const char* str1, const char* str2) {
    int len = (strlen(str1) < strlen(str2)) ? strlen(str1) : strlen(str2);
    for (int i = 0; i < len; i++) {
        if (str1[i] > str2[i]) return false;
    }
    if (strlen(str1) > strlen(str2)) return false;
    return true;
}

