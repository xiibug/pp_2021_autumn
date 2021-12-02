// Copyright 2021 Utyugov Denis
#include "../../../modules/task_2/utyugov_d_transfer_all_to_one/transfer_all_to_one.h"

#include <mpi.h>

#include <random>
#include <string>
#include <vector>

std::vector<int> getRandomVector(int sz) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = gen() % 100;
  }
  return vec;
}

// only MPI_Send and MPI_Recv.
// Must realise MPI_INT, MPI_DOUBLE, MPI_FLOAT.

int MY_Reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype,
              MPI_Op op, int root, MPI_Comm comm) {
  int size, rank;
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);

  if (rank == root) {
    if (datatype == MPI_INT) {
      if (op == MPI_SUM || op == MPI_MAX) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<int*>(recvbuf)[i] = 0;
        }
      } else if (op == MPI_PROD) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<int*>(recvbuf)[i] = 1;
        }
      } else if (op == MPI_MIN) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<int*>(recvbuf)[i] = 10000;
        }
      }
      for (int k = 0; k < size; k++) {
        if (k != root) {
          MPI_Recv(sendbuf, count, datatype, MPI_ANY_SOURCE, 0, comm,
                   MPI_STATUS_IGNORE);
        }

        if (op == MPI_SUM) {
          for (int i = 0; i < count; i++) {
            reinterpret_cast<int*>(recvbuf)[i] +=
                reinterpret_cast<int*>(sendbuf)[i];
          }
        } else if (op == MPI_PROD) {
          for (int i = 0; i < count; i++) {
            reinterpret_cast<int*>(recvbuf)[i] *=
                reinterpret_cast<int*>(sendbuf)[i];
          }
        } else if (op == MPI_MAX) {
          for (int i = 0; i < count; i++) {
            if (reinterpret_cast<int*>(recvbuf)[i] <
                reinterpret_cast<int*>(sendbuf)[i])
              reinterpret_cast<int*>(recvbuf)[i] =
                  reinterpret_cast<int*>(sendbuf)[i];
          }
        } else if (op == MPI_MIN) {
          for (int i = 0; i < count; i++) {
            if (reinterpret_cast<int*>(recvbuf)[i] >
                reinterpret_cast<int*>(sendbuf)[i])
              reinterpret_cast<int*>(recvbuf)[i] =
                  reinterpret_cast<int*>(sendbuf)[i];
          }
        }
      }

    } else if (datatype == MPI_FLOAT) {
      if (op == MPI_SUM || op == MPI_MAX) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<float*>(recvbuf)[i] = 0;
        }
      } else if (op == MPI_PROD) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<float*>(recvbuf)[i] = 1;
        }
      } else if (op == MPI_MIN) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<float*>(recvbuf)[i] = 10000;
        }
      }

      for (int k = 0; k < size; k++) {
        if (k != root) {
          MPI_Recv(sendbuf, count, datatype, MPI_ANY_SOURCE, 0, comm,
                   MPI_STATUS_IGNORE);
        }

        if (op == MPI_SUM) {
          for (int i = 0; i < count; i++) {
            reinterpret_cast<float*>(recvbuf)[i] +=
                reinterpret_cast<float*>(sendbuf)[i];
          }
        } else if (op == MPI_PROD) {
          for (int i = 0; i < count; i++) {
            reinterpret_cast<float*>(recvbuf)[i] *=
                reinterpret_cast<float*>(sendbuf)[i];
          }
        } else if (op == MPI_MAX) {
          for (int i = 0; i < count; i++) {
            if (reinterpret_cast<float*>(recvbuf)[i] <
                reinterpret_cast<float*>(sendbuf)[i])
              reinterpret_cast<float*>(recvbuf)[i] =
                  reinterpret_cast<float*>(sendbuf)[i];
          }
        } else if (op == MPI_MIN) {
          for (int i = 0; i < count; i++) {
            if (reinterpret_cast<float*>(recvbuf)[i] >
                reinterpret_cast<float*>(sendbuf)[i])
              reinterpret_cast<float*>(recvbuf)[i] =
                  reinterpret_cast<float*>(sendbuf)[i];
          }
        }
      }

    } else {  // double
      if (op == MPI_SUM || op == MPI_MAX) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<double*>(recvbuf)[i] = 0;
        }
      } else if (op == MPI_PROD) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<double*>(recvbuf)[i] = 1;
        }
      } else if (op == MPI_MIN) {
        for (int i = 0; i < count; i++) {
          reinterpret_cast<double*>(recvbuf)[i] = 10000;
        }
      }

      for (int k = 0; k < size; k++) {
        if (k != root) {
          MPI_Recv(sendbuf, count, datatype, MPI_ANY_SOURCE, 0, comm,
                   MPI_STATUS_IGNORE);
        }

        if (op == MPI_SUM) {
          for (int i = 0; i < count; i++) {
            reinterpret_cast<double*>(recvbuf)[i] +=
                reinterpret_cast<double*>(sendbuf)[i];
          }
        } else if (op == MPI_PROD) {
          for (int i = 0; i < count; i++) {
            reinterpret_cast<double*>(recvbuf)[i] *=
                reinterpret_cast<double*>(sendbuf)[i];
          }
        } else if (op == MPI_MAX) {
          for (int i = 0; i < count; i++) {
            if (reinterpret_cast<double*>(recvbuf)[i] <
                reinterpret_cast<double*>(sendbuf)[i])
              reinterpret_cast<double*>(recvbuf)[i] =
                  reinterpret_cast<double*>(sendbuf)[i];
          }
        } else if (op == MPI_MIN) {
          for (int i = 0; i < count; i++) {
            if (reinterpret_cast<double*>(recvbuf)[i] >
                reinterpret_cast<double*>(sendbuf)[i])
              reinterpret_cast<double*>(recvbuf)[i] =
                  reinterpret_cast<double*>(sendbuf)[i];
          }
        }
      }
    }
  }
  if (rank != root) {
    MPI_Send(sendbuf, count, datatype, root, 0, comm);
  }

  return 0;
}
