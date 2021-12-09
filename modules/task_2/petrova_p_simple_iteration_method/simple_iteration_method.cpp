// Copyright 2021 Petrova Polina
#include <mpi.h>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include"../../../modules/task_2/petrova_p_simple_iteration_method/simple_iteration_method.h"

std::vector<double> fillRandomVector(int len) {
    if (len < 0) {
        throw "error! lenght vector < 0!";
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 10);  // values 1-100 // check commit
        std::vector<double> v(len);
        for (int i = 0; i < len; i++) {
            v[i] = dist(gen);
        }
        return v;
    }
}
std::vector< std::vector<double>> fillRandomMatrix(int n) {
    if (n < 0) {
        throw "error! lenght vector < 0!";
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 10);  //  values 1-10
        std::uniform_int_distribution<> dist1(10, 20);  //  for diagonal
        std::vector<std::vector<double>> v(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    v[i].push_back(dist1(gen));
                v[i].push_back(dist(gen));
            }
        }
        return v;
    }
}
std::vector<double> seqMethod(std::vector< std::vector<double>> mat, std::vector<double> b, int n) {
    std::vector<double> firstSolv(n, 0.0);
    int it = 0;
    double eps = 0.0001;
    while (true) {
        it++;
        if (it == 1000)
            break;
        std::vector<double> currentSol(n, 0.0);
        for (int i = 0; i < n; i++) {
            currentSol[i] = mat[i][n] / mat[i][i];
            for (int j = 0; j < n; j++) {
                if (i != j)
                    currentSol[i] = currentSol[i] - mat[i][j] / mat[i][i] * firstSolv[i];
            }
        }
        double err = 0.0;
        for (int i = 0; i < n; i++) {
            err = err + std::abs(currentSol[i] - firstSolv[i]);
        }
        if (err < eps)
            break;
        firstSolv = currentSol;
    }
    return firstSolv;
}
std::vector<double> parallelMethod(std::vector<std::vector <double> > mat, std::vector<double> b, int n) {
    int procNum, procRank;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    if ((n < procNum) || (procNum == 1)) {
        if (procRank == 0) {
            return seqMethod(mat, b, n);
        } else {
            return std::vector<double>();
        }
    }
    std::vector<double> firstSolv(n, 0.0);
    int littleLen = n / procNum;
    int startI;
    std::vector< std::vector<double> > locMat;
    int count = littleLen;
    if (procRank == 0) {
        locMat = mat;
        locMat.resize(mat[0][0] + littleLen * n);
        for (int i = 1; i < procNum; i++) {
            startI = littleLen * i;
            if (i == procNum - 1)
                count = n - startI;
            MPI_Send(mat[startI].data(), n * count, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        if (procNum == procNum - 1)
            count = n - littleLen * (procNum - 1);
        locMat = mat;
        locMat.resize(count);
        MPI_Recv(locMat[0].data(), n * count, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    }
    std::vector<int> resCount(procNum);
    std::vector<int> extra(procNum);
    for (int i = 0; i < procNum; i++) {
        if (i == procNum - 1)
            resCount[i] = n - littleLen * (procNum - 1);
        else
            resCount[i] = littleLen;
        if (i == 0)
            extra[i] = 0;
        else
            extra[i] = extra[i - 1] + littleLen;
    }

    int it = 0;
    double eps = 0.0001;
    while (true) {
        it++;
        if (it == 1000) {
            break;
        }
        std::vector<double> currentSolv(n, 0.0);
        for (int i; i < locMat.size(); i++) {
            currentSolv[i] = locMat[i][locMat.size() - 1]
                / locMat[i][i + procRank * littleLen];
            for (int j = 0; j < locMat.size() - 1; j++) {
                if (i + procRank * littleLen != j)
                    currentSolv[i] = currentSolv[i] - (locMat[i][j]
                        / locMat[i][i + procRank * littleLen]) * firstSolv[j];
            }
        }
        double err = 0.0;
        for (int i = 0; i < locMat.size(); i++) {
            err = err + std::abs(currentSolv[i] - firstSolv[i + procRank * littleLen]);
        }
        MPI_Allreduce(MPI_IN_PLACE, &err, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        if (err < eps) {
            break;
        }
        MPI_Allgatherv(currentSolv.data(), count, MPI_DOUBLE, firstSolv.data(),
            resCount.data(), extra.data(), MPI_DOUBLE, MPI_COMM_WORLD);
    }
    return firstSolv;
}
