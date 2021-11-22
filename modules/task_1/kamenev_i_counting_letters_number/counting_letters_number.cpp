// Copyright 2021 Kamenev Ilya
#include "../../../modules/task_1/kamenev_i_counting_letters_number/counting_letters_number.h"
#include <iostream>
#include <random>
#include "mpi.h"

std::string CreateRandomStr(size_t size) {
  std::string str;
  for (size_t i = 0; i < size; i++) {
    str += static_cast<char>(rand() % 119 + 9);
  }
  return str;
}

std::string CreateOnlyLettersStr(size_t size) {
  std::string str;
  static const char alphabet[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  for (size_t i = 0; i < size; i++) {
    str += alphabet[rand() % (sizeof(alphabet) - 1)];
  }
  return str;
}

int CountingLettersSequential(const std::string& str) {
  int a = 0;
  for (char ch : str) {
    if (isalpha(ch)) {
      a++;
    }
  }
  return a;
}

int CountingLettersParallel(const std::string& str) {
  int size;
  int rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  const int delta = str.size() / size;

  if (rank == 0) {
    for (int proc = 1; proc < size; proc++) {
      MPI_Send(str.data() + proc * delta, delta, MPI_CHAR, proc, 0,
               MPI_COMM_WORLD);
    }
  }

  std::string partialStr;
  if (rank == 0) {
    partialStr = std::string(str.begin(), str.begin() + delta);
  } else {
    MPI_Status status;
    MPI_Recv(&partialStr[0], delta, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
  }

  int globalLettersCount = 0;
  int partialLettersCount = CountingLettersSequential(partialStr);
  MPI_Reduce(&partialLettersCount, &globalLettersCount, 1, MPI_INT, MPI_SUM, 0,
             MPI_COMM_WORLD);
  return globalLettersCount;
}