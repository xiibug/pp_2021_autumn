// Copyright 2021 Olenin Sergey
#include "../../../modules/task_1/olenin_s_number_of_sentences/number_of_sentences.h"

#include <mpi.h>

#include <string>

int getSequentialNumOfSentences(std::string global_string) {
  const int length = global_string.length();
  int num = 0;
  for (int i = 0; i < length; i++) {
    if (global_string[i] == '.' || global_string[i] == '!' ||
        global_string[i] == '?') {
      num++;
    }
  }
  return num;
}

int getParallelNumOfSentences(std::string global_string) {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int delta, rem;

  if (rank == 0) {
    delta = global_string.length() / size;
    rem = global_string.length() % size;
  }

  MPI_Bcast(&delta, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&rem, 1, MPI_INT, 0, MPI_COMM_WORLD);

  char* buffer = new char[delta + 1];
  MPI_Scatter(global_string.data() + rem, delta, MPI_CHAR, buffer, delta,
              MPI_CHAR, 0, MPI_COMM_WORLD);
  buffer[delta] = '\0';

  std::string local_string = buffer;

  int global_num = 0;
  int local_num = getSequentialNumOfSentences(local_string);

  MPI_Reduce(&local_num, &global_num, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    if (rem) {
      for (int i = 0; i < rem; i++) {
        if (global_string[i] == '.' || global_string[i] == '!' ||
            global_string[i] == '?') {
          global_num++;
        }
      }
    }
  }
  return global_num;
}
