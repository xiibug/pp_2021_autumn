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
    float integ;
    float k = static_cast<float>(b) - a;
    float z;

    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<unsigned int> uid(0, RAND_MAX);
    if (N == 0) {
        throw - 1;
    } else {
      for (int i = 0; i < N; i++) {
          z = static_cast<float>(uid(gen) / RAND_MAX);
          x = a + z * (b - a);
          y += func(x);
      }
      integ = (static_cast<float>(1) / N) * k * static_cast<float>(y);
      return integ;
    }
}

double MonteCarloMPI(int N, int a, int b, double(*func)(double)) {
    if (b < a)
        throw - 1;

    double t1, t2;
    float y, z, x, integ, result;
    float k = static_cast<float>(b) - a;

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
      std::mt19937 gen;
      gen.seed(static_cast<unsigned int>(time(0)));
      std::uniform_int_distribution<unsigned int> uid(0, RAND_MAX);
      for (int i = 1; i < count; i++) {
          z = static_cast<float>(uid(gen) / RAND_MAX);
          x = a + z * (b - a);
          y += func(x);
      }
      integ = (static_cast<float>(1) / N) * k * static_cast<float>(y);
      MPI_Reduce(&integ, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
      if (ProcRank == 0) {
          t2 = MPI_Wtime();
          std::cout << t2 - t1 << std::endl;
      }
    }
    return result;
}
