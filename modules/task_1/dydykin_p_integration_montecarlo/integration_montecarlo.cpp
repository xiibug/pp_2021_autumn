// Copyright 2021 Dydykin Pavel
#include "../../../modules/task_1/dydykin_p_integration_montecarlo/integration_montecarlo.h"
#include <mpi.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

double func1(double x) {
    return x / 2 + 1;
}

double func2(double x) {
    return sin(x) / 3;
}

double func3(double x) {
    return (pow(x, 2));
}

double MonteCarloWithOutMPI(int N, int a, int b, double(*func)(double)) {
    if (b < a)
        throw - 1;

    float x;
    float y = 0;
    float Integral;
    float koef = static_cast<float>(b - a);
    float te;

    srand(time(0));
    if (N == 0) {
        throw - 1;
    } else {
      for (int i = 0; i < N; i++) {
          te = (static_cast<float>(rand()) / RAND_MAX);
          x = a + te * (b - a);
          y += func(x);
      }
      Integral = (static_cast<float>(1) / N) * koef * static_cast<float>(y);
      return Integral;
    }
}

double MonteCarloMPI(int N, int a, int b, double(*func)(double)) {
    if (b < a)
        throw - 1;

    double t1, t2;
    float y, te, x, Integral, result;
    float koef = static_cast<float>(b - a);

    int ProcNum, ProcRank;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    t1 = MPI_Wtime();
    MPI_Bcast(&ProcNum, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int count;
    count = N / ProcNum;
    if (ProcRank == 0) {
        count += N % ProcNum;
    }

    if (ProcNum == 0) {
        return 0;
    } else {
      y = 0.0;
      srand(time(0));
      for (int i = 1; i < count; i++) {
          te = (static_cast<float>(rand()) / RAND_MAX);
          x = a + te * (b - a);
          y += func(x);
      }
      Integral = (static_cast<float>(1) / N) * koef * static_cast<float>(y);
      MPI_Reduce(&Integral, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
      if (ProcRank == 0) {
          t2 = MPI_Wtime();
          std::cout << t2 - t1 << std::endl;
      }
    }
    return result;
}
