// Copyright 2021 Myasnikova Varvara

#include <mpi.h>
#include <iostream>
#include "../../../modules/task_1/myasnikova_counting_symbols/myasnikova_counting_symbols.h"

// Parallel
int pCountingSymbols(char s, std::string text) {
  int procRank = 0;  // Process number
  int procNum = 0;  // Number of processes
  const int length = text.length();  // Length of the text
  int quantity = 0;  // Total number of counted symbols
  int tmpQuantity = 0;  // Number of symbols counted by each process
  int amount = 0;  // Number of symbols to count for each process
  int remains = 0;  // Remaining symbols

  MPI_Comm_size(MPI_COMM_WORLD, &procNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

  if (procRank == 0) {
    if (procNum > length)
      throw(-1);

    if (procNum == 1) {
      amount = length;
    } else {
      amount = length / (procNum - 1);
      remains = length % (procNum - 1);
    }

    // Sending data to all processes except the main one
    for (int i = 1; i < procNum; i++) {
      MPI_Send(&amount, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
  }

  if (procRank != 0) {
    MPI_Status status;
    MPI_Recv(&amount, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    for (int i = amount * (procRank - 1); i < amount * procRank; i++) {
      if (text[i] == s || text[i] == s - 32) {
        tmpQuantity++;
      }
    }
  } else {
    int t = 0;
    if (procNum != 1) {
      t = length - remains;
    }
    for (int i = t; i < length; i++) {
      if (text[i] == s || text[i] == s - 32) {
        tmpQuantity++;
      }
    }
  }

  MPI_Reduce(&tmpQuantity, &quantity, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  return quantity;
}

// Serial
int sCountingSymbols(char s, std::string text) {
  int quantity = 0;
  int length = text.length();
  for (int i = 0; i < length; i++) {
    if (text[i] == s || text[i] == s - 32) {
      quantity++;
    }
  }

  return quantity;
}
