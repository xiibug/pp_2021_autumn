// Copyright 2021 Nazarov Nikita
#include "../../../modules/task_3/nazarov_n_fox_algorithm/fox_algorithm.h"

std::vector<double> GetRandomMatrix(int n) {
  if (n <= 0) {
    throw "ERROR!!!!!!";
  }
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_real_distribution<> urd(-100, 100);
  std::vector<double> vec(n * n);
  for (int i = 0; i < n * n; i++) {
    vec[i] = urd(gen);
  }
  return vec;
}

void Multiplication(std::vector<double> A, std::vector<double> B,
                    std::vector<double> C, int data) {
  for (int i = 0; i < data; i++) {
    for (int j = 0; j < data; j++) {
      for (int k = 0; k < data; k++) {
        C[i * data + j] += A[i * data + k] * B[k * data + j];
      }
    }
  }
}

void FoxAlgorithm(std::vector<double> A, std::vector<double> B,
                  std::vector<double> C, int data) {
  if (data <= 0) throw "ERROR!!!!!!";
  MPI_Comm comm_blockmatrix;
  MPI_Comm comm_col;
  MPI_Comm comm_row;
  int coordinates[2], my_row, my_col, blocks, ProcNum, ProcRank, source,
      destination, size_blockmatrix, periods_blockmatrix[2] = {1, 1},
                                     subdimensions_row[2] = {0, 1},
                                     subdimensions_col[2] = {1, 0};
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  blocks = sqrt(ProcNum);
  int dimensions_blockmatrix[2] = {blocks, blocks};
  if (ProcRank == 0) {
    size_blockmatrix = data / blocks;
  }
  MPI_Bcast(&size_blockmatrix, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions_blockmatrix,
                  periods_blockmatrix, false, &comm_blockmatrix);
  MPI_Cart_coords(comm_blockmatrix, ProcRank, 2, coordinates);
  my_row = coordinates[0];
  my_col = coordinates[1];
  MPI_Cart_sub(comm_blockmatrix, subdimensions_row, &comm_row);
  MPI_Cart_sub(comm_blockmatrix, subdimensions_col, &comm_col);

  std::vector<double> A_blockmatrix(size_blockmatrix * size_blockmatrix),
      t_blockmatrix(size_blockmatrix * size_blockmatrix),
      B_blockmatrix(size_blockmatrix * size_blockmatrix),
      C_blockmatrix(size_blockmatrix * size_blockmatrix);

  for (int i = 0; i < size_blockmatrix * size_blockmatrix; i++) {
    C_blockmatrix[i] = 0;
  }

  MPI_Datatype MY_TYPE;
  MPI_Type_vector(size_blockmatrix, size_blockmatrix, size_blockmatrix * blocks,
                  MPI_DOUBLE, &MY_TYPE);
  MPI_Type_commit(&MY_TYPE);

  if (ProcRank == 0) {
    for (int i = 0; i < size_blockmatrix; i++) {
      for (int j = 0; j < size_blockmatrix; j++) {
        A_blockmatrix[i * size_blockmatrix + j] = A[i * data + j];
        B_blockmatrix[i * size_blockmatrix + j] = B[i * data + j];
      }
    }
    for (int i = 1; i < ProcNum; i++) {
      MPI_Send(A.data() + (i / blocks) * data * size_blockmatrix +
                   (i % blocks) * size_blockmatrix,
               1, MY_TYPE, i, 0, comm_blockmatrix);
      MPI_Send(B.data() + (i / blocks) * data * size_blockmatrix +
                   (i % blocks) * size_blockmatrix,
               1, MY_TYPE, i, 1, comm_blockmatrix);
    }
  } else {
    MPI_Status status;
    MPI_Recv(A_blockmatrix.data(), size_blockmatrix * size_blockmatrix,
             MPI_DOUBLE, 0, 0, comm_blockmatrix, &status);
    MPI_Recv(B_blockmatrix.data(), size_blockmatrix * size_blockmatrix,
             MPI_DOUBLE, 0, 1, comm_blockmatrix, &status);
  }

  for (int i = 0; i < blocks; i++) {
    int j = (my_row + i) % blocks;
    if (j == my_col) {
      for (int i = 0; i < size_blockmatrix * size_blockmatrix; i++) {
        t_blockmatrix[i] = A_blockmatrix[i];
      }
      MPI_Bcast(t_blockmatrix.data(), size_blockmatrix * size_blockmatrix,
                MPI_DOUBLE, j, comm_row);
      Multiplication(t_blockmatrix, B_blockmatrix, C_blockmatrix,
                     size_blockmatrix);
    } else {
      MPI_Bcast(t_blockmatrix.data(), size_blockmatrix * size_blockmatrix,
                MPI_DOUBLE, j, comm_row);
      Multiplication(t_blockmatrix, B_blockmatrix, C_blockmatrix,
                     size_blockmatrix);
    }

    source = (my_row + 1) % blocks;
    destination = (my_row - 1 + blocks) % blocks;

    MPI_Status status;
    MPI_Sendrecv_replace(B_blockmatrix.data(),
                         size_blockmatrix * size_blockmatrix, MPI_DOUBLE,
                         destination, 0, source, 0, comm_col, &status);
  }

  if (ProcRank == 0) {
    for (int i = 0; i < size_blockmatrix; i++) {
      for (int j = 0; j < size_blockmatrix; j++) {
        C[i * data + j] = C_blockmatrix[i * size_blockmatrix + j];
      }
    }
    for (int i = 1; i < ProcNum; i++) {
      MPI_Status status;
      MPI_Recv(C.data() + (i / blocks) * data * size_blockmatrix +
                   (i % blocks) * size_blockmatrix,
               size_blockmatrix * size_blockmatrix, MY_TYPE, i, 3,
               comm_blockmatrix, &status);
    }
  } else {
    MPI_Send(C_blockmatrix.data(), size_blockmatrix * size_blockmatrix,
             MPI_DOUBLE, 0, 3, comm_blockmatrix);
  }

  MPI_Type_free(&MY_TYPE);
}
