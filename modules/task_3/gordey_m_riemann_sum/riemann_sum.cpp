// Copyright 2021 Gordey Maria
#include "../../../modules/task_3/gordey_m_riemann_sum/riemann_sum.h"

#include <mpi.h>

double getSequentialIntegrals(
    const int n, const std::vector<std::pair<double, double>>& limits,
    const std::function<double(std::vector<double>)>& f) {
  int dimension = static_cast<int>(limits.size());
  size_t count = 1;
  std::vector<double> h(dimension);
  for (int i = 0; i < dimension; i++) {
    h[i] = (limits[i].second - limits[i].first) / n;
    count = count * n;
  }

  double result = 0.0;
  std::vector<double> combinations(dimension);
  for (size_t j = 0; j < count; j++) {
    for (int i = 0; i < dimension; i++) {
      combinations[i] = limits[i].first + (j % n) * h[i] + h[i] * 0.5;
    }
    result += f(combinations);
  }

  for (int i = 0; i < dimension; i++) {
    result *= h[i];
  }

  return result;
}

double getParallelIntegrals(
    const int n, const std::vector<std::pair<double, double>>& limits,
    const std::function<double(std::vector<double>)>& f) {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int dimension = static_cast<int>(limits.size());
  std::vector<double> h(n);
  int count;

  if (rank == 0) {
    count = 1;
    for (int i = 0; i < dimension; i++) {
      h[i] = (limits[i].second - limits[i].first) / n;
    }
    int j = 0;
    while (j != dimension - 1) {
      count *= n;
      j++;
    }
  }

  MPI_Bcast(&count, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  MPI_Bcast(h.data(), dimension, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  size_t delta = static_cast<size_t>(count / size);

  if (rank < count % size) {
    delta += 1;
  }

  std::vector<std::vector<double>> combinations(delta);
  double local_result = 0.0;
  for (size_t i = 0; i < delta; i++) {
    int number = static_cast<int>(rank * delta + i);
    for (int j = 0; j < dimension; j++) {
      combinations[i].push_back(limits[j].first + h[j] * (number % n) +
                                h[j] * 0.5);
    }

    local_result += f(combinations[i]) * n;
  }

  double global_result = 0.0;
  MPI_Reduce(&local_result, &global_result, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < dimension; i++) {
      global_result *= h[i];
    }
  }

  return global_result;
}
