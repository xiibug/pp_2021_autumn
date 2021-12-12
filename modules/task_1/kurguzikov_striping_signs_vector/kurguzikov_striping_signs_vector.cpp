// Copyright 2021 Kurguzikov Kirill

#include "../../../modules/task_1/kurguzikov_striping_signs_vector/kurguzikov_striping_signs_vector.h"
#include <mpi.h>
#include <random>
#include <iostream>

int sequentialCount(std::vector<int> sequent_vec) {
  int count = 0;

  if (sequent_vec.size() != 0) {
    for (int i = 1; i < sequent_vec.size(); i++)
      if ((sequent_vec[i - 1] > 0 && sequent_vec[i] < 0) ||
        (sequent_vec[i - 1] < 0 && sequent_vec[i] > 0))
        count++;
  }

  return count;
}

std::vector<int> getRandomValue(int len) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-100, 100);

    if (len < 0) { len = 0; }

    std::vector<int> vec(len);
    for (int i = 0; i < len; i++) { vec[i] = dist(gen); }

    return vec;
}

int parallelCount(std::vector<int> vect) {
  int procCount = 0, procRank = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &procCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

  int global_res = 0;
  int local_res = 0;
  int size_vect = vect.size();
  MPI_Bcast(&size_vect, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (size_vect < procCount) {
    return sequentialCount(vect);
  }  

  int* sendcounts = new int[procCount];
  int* displs = new int[procCount];

  int len = size_vect / procCount;
  int rem = size_vect % procCount;

  sendcounts[0] = len + rem;
  displs[0] = 0;

  for (int i = 1; i < procCount; i++) {
    sendcounts[i] = len + 1;
    displs[i] = displs[i - 1] + sendcounts[i - 1] -1;
  }

  std::vector<int>local_vect(sendcounts[procRank]);

  MPI_Scatterv(&vect[0], sendcounts, displs, MPI_INT, &local_vect[0], sendcounts[procRank], MPI_INT, 0, MPI_COMM_WORLD);
  local_res = sequentialCount(local_vect);
  MPI_Reduce(&local_res, &global_res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  return global_res;
}
