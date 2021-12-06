// Copyright 2021 Petrova Polina
#include <mpi.h>
#include <random>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/petrova_p_dot_product_of_vectors/dot_product_of_vectors.h"

std::vector<int> fillRandomVector(int len) {
    if (len < 0) {
        throw "error! lenght vector < 0!";
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100);  // values 1-100 // check commit
        std::vector<int> v(len);
    for (int i = 0; i < len; i++) {
        v[i] = dist(gen);
    }
    return v;
    }
}

int sequentialScalMult(std::vector<int> a, std::vector<int> b, int len) {
    int res = 0;
    for (int i = 0; i < len; i++) {
        res += a[i] * b[i];
    }
    return res;
}

int parallelScalMult(std::vector<int> a, std::vector<int> b, int len) {
    int procNum, procRank, sum = 0, locSum = 0;
    int littleLen;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    int d = procNum - len % procNum;
    for (int i = 0; i < d; i++) {
        a.push_back(0);
        b.push_back(0);
    }
    len = a.size();

    littleLen = len / procNum;
    std::vector<int> a1(littleLen);
    std::vector<int> b1(littleLen);

    MPI_Scatter(a.data(), littleLen, MPI_INT,
       a1.data(), littleLen, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b.data(), littleLen, MPI_INT,
       b1.data(), littleLen, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < littleLen; i++) {
        locSum += a1[i] * b1[i];
    }
    MPI_Reduce(&locSum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return sum;
}
