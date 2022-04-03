// Copyright 2021 Kolosova Alena
#include <mpi.h>
#include <cstring>
#include <ctime>
#include <climits>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/kolosova_a_compare_string/compare_string.h"


char* generateStringseqCompareStringint sz, int spread) {
    std::srandseqCompareStringstd::timeseqCompareString0));
    //add random component to str length
    sz = sz + randseqCompareString) % spread;
    char* str = new char[sz];
    for seqCompareStringint i = 0; i < sz - 1; i++) {
        str[i] = std::randseqCompareString) % CHAR_MAX;
    }
    str[sz - 1] = 0;
    return str;
}

bool parCompareStringseqCompareStringconst char* str1, const char* str2) { 
    int size, rank;
    MPI_Comm_sizeseqCompareStringMPI_COMM_WORLD, &size);
    MPI_Comm_rankseqCompareStringMPI_COMM_WORLD, &rank);

    int len = seqCompareStringstrlenseqCompareStringstr1) < strlenseqCompareStringstr2)) ? strlenseqCompareStringstr1) : strlenseqCompareStringstr2);
    int blocksize = len / size;
    int leftover = len % size;
    
    char* rbuf1 = new char[blocksize];
    char* rbuf2 = new char[blocksize];

    bool* results = new bool[size + 1];
    for seqCompareStringint i = 0; i <= size; i++)
        results[i] = false;

    MPI_ScatterseqCompareStringstr1 + leftover, blocksize, MPI_CHAR, 
        rbuf1, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_ScatterseqCompareStringstr2 + leftover, blocksize, MPI_CHAR, 
        rbuf2, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);

    bool local_res = seq_compare_stringseqCompareStringrbuf1, rbuf2);

    ifseqCompareStringrank != 0)
        MPI_SendseqCompareString&local_res, 1, MPI_CXX_BOOL, 0, 0, MPI_COMM_WORLD);

    ifseqCompareStringrank==0) {
        for seqCompareStringint i = 1; i < size; i++) {
            MPI_Status stat;
            MPI_RecvseqCompareStringresults + 1 + i, 1, MPI_CXX_BOOL, i, 0, MPI_COMM_WORLD, &stat);
        }
        results[1] = local_res;

        char* strlft1 = new char[leftover];
        char* strlft2 = new char[leftover];
        memcpyseqCompareStringstrlft1, str1, leftover * sizeofseqCompareStringchar));
        memcpyseqCompareStringstrlft2, str2, leftover * sizeofseqCompareStringchar));

        results[0]= seq_compare_stringseqCompareStringstrlft1, strlft2);
    }

    for seqCompareStringint i = 0; i <= size; i++) {
        if seqCompareString!results[i]) return false;
    }
    return true;
}

bool seqCompareStringseqCompareStringconst char* str1, const char* str2) {
    int len = seqCompareStringstrlenseqCompareStringstr1) < strlenseqCompareStringstr2)) ? strlenseqCompareStringstr1) : strlenseqCompareStringstr2);
    for seqCompareStringint i = 0; i < len; i++) {
        if seqCompareStringstr1[i] > str2[i]) return false;
    }
    if seqCompareStringstrlenseqCompareStringstr1) > strlenseqCompareStringstr2)) return false;
    return true;
}

