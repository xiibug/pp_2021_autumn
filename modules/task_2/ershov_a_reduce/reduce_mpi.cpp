// Copyright 2021 Ershov Alexey
#include "./reduce_mpi.h"

#include <mpi.h>

#include <random>

template <typename T>
T* getRandomVector(size_t size) {
  T* vec = new T[size];
  std::random_device dev;
  std::mt19937 gen(dev());
  for (size_t i = 0; i < size; ++i) {
    vec[i] = gen() % 100;
  }
  return vec;
}

int reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype type,
           MPI_Op op, int root, MPI_Comm comm) {
  int rank;
  int size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Barrier(comm);

  if (rank == root) {
    int typeSize = 0;
    if (type == MPI_INT) {
      typeSize = sizeof(int);
    } else if (type == MPI_DOUBLE) {
      typeSize = sizeof(double);
    } else if (type == MPI_FLOAT) {
      typeSize = sizeof(float);
    }

    size_t memSize = (typeSize * count);

    void* buf = (void*)malloc(memSize);
    void* tmp = (void*)malloc(memSize);

    int counter = 0;
    if (type == MPI_INT) {
      for (size_t i = 0; i < size; ++i) {
        if (i != root) {
          MPI_Recv(buf, count, type, MPI_ANY_SOURCE, 1, comm,
                   MPI_STATUS_IGNORE);
        } else {
          for (size_t j = 0; j < count; ++j) {
            (reinterpret_cast<int*>(buf))[j] =
                (reinterpret_cast<int*>(sendbuf))[j];
          }
        }
        if (counter == 0) {
          for (int j = 0; j < count; ++j) {
            (reinterpret_cast<int*>(tmp))[j] = (reinterpret_cast<int*>(buf))[j];
          }
          counter++;
        } else {
          if (op == MPI_SUM) {
            for (int j = 0; j < count; ++j) {
              (reinterpret_cast<int*>(tmp))[j] +=
                  (reinterpret_cast<int*>(buf))[j];
            }
          } else if (op == MPI_MAX) {
            for (int j = 0; j < count; ++j) {
              if ((reinterpret_cast<int*>(buf))[j] >=
                  (reinterpret_cast<int*>(tmp))[j]) {
                (reinterpret_cast<int*>(tmp))[j] =
                    (reinterpret_cast<int*>(buf))[j];
              }
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; ++j) {
              if ((reinterpret_cast<int*>(buf))[j] <=
                  (reinterpret_cast<int*>(tmp))[j]) {
                (reinterpret_cast<int*>(tmp))[j] =
                    (reinterpret_cast<int*>(buf))[j];
              }
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; ++j) {
              (reinterpret_cast<int*>(tmp))[j] *=
                  (reinterpret_cast<int*>(buf))[j];
            }
          }
        }
      }
      for (int i = 0; i < count; ++i) {
        (reinterpret_cast<int*>(recvbuf))[i] = (reinterpret_cast<int*>(tmp))[i];
      }
      free(buf);
      free(tmp);
      buf = nullptr;
      tmp = nullptr;
    } else if (type == MPI_DOUBLE) {
      for (int i = 0; i < size; ++i) {
        if (i != root) {
          MPI_Recv(buf, count, type, MPI_ANY_SOURCE, 1, comm,
                   MPI_STATUS_IGNORE);
        } else {
          for (int j = 0; j < count; ++j) {
            (reinterpret_cast<double*>(buf))[j] =
                (reinterpret_cast<double*>(sendbuf))[j];
          }
        }
        if (counter == 0) {
          for (int j = 0; j < count; ++j) {
            (reinterpret_cast<double*>(tmp))[j] =
                (reinterpret_cast<double*>(buf))[j];
          }
          counter++;
        } else {
          if (op == MPI_SUM) {
            for (int j = 0; j < count; ++j) {
              (reinterpret_cast<double*>(tmp))[j] +=
                  (reinterpret_cast<double*>(buf))[j];
            }
          } else if (op == MPI_MAX) {
            for (int j = 0; j < count; ++j) {
              if ((reinterpret_cast<double*>(buf))[j] >=
                  (reinterpret_cast<double*>(tmp))[j]) {
                (reinterpret_cast<double*>(tmp))[j] =
                    (reinterpret_cast<double*>(buf))[j];
              }
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; ++j) {
              if ((reinterpret_cast<double*>(buf))[j] <=
                  (reinterpret_cast<double*>(tmp))[j]) {
                (reinterpret_cast<double*>(tmp))[j] =
                    (reinterpret_cast<double*>(buf))[j];
              }
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; ++j) {
              (reinterpret_cast<double*>(tmp))[j] *=
                  (reinterpret_cast<double*>(buf))[j];
            }
          }
        }
      }
      for (int i = 0; i < count; ++i) {
        (reinterpret_cast<double*>(recvbuf))[i] =
            (reinterpret_cast<double*>(tmp))[i];
      }
      free(buf);
      free(tmp);
      buf = nullptr;
      tmp = nullptr;
    } else if (type == MPI_FLOAT) {
      for (int i = 0; i < size; ++i) {
        if (i != root) {
          MPI_Recv(buf, count, type, MPI_ANY_SOURCE, 1, comm,
                   MPI_STATUS_IGNORE);
        } else {
          for (int j = 0; j < count; ++j) {
            (reinterpret_cast<float*>(buf))[j] =
                (reinterpret_cast<float*>(sendbuf))[j];
          }
        }
        if (counter == 0) {
          for (int j = 0; j < count; ++j) {
            (reinterpret_cast<float*>(tmp))[j] =
                (reinterpret_cast<float*>(buf))[j];
          }
          counter++;
        } else {
          if (op == MPI_SUM) {
            for (int j = 0; j < count; ++j) {
              (reinterpret_cast<float*>(tmp))[j] +=
                  (reinterpret_cast<float*>(buf))[j];
            }
          } else if (op == MPI_MAX) {
            for (int j = 0; j < count; ++j) {
              if ((reinterpret_cast<float*>(buf))[j] >=
                  (reinterpret_cast<float*>(tmp))[j]) {
                (reinterpret_cast<float*>(tmp))[j] =
                    (reinterpret_cast<float*>(buf))[j];
              }
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; ++j) {
              if ((reinterpret_cast<float*>(buf))[j] <=
                  (reinterpret_cast<float*>(tmp))[j]) {
                (reinterpret_cast<float*>(tmp))[j] =
                    (reinterpret_cast<float*>(buf))[j];
              }
            }
          } else if (op == MPI_PROD) {
            for (int i = 0; i < count; ++i) {
              (reinterpret_cast<float*>(tmp))[i] *=
                  (reinterpret_cast<float*>(buf))[i];
            }
          }
        }
      }
      for (int i = 0; i < count; ++i) {
        (reinterpret_cast<float*>(recvbuf))[i] = (reinterpret_cast<float*>(tmp))[i];
      }
      free(buf);
      free(tmp);
      buf = nullptr;
      tmp = nullptr;
    }
  } else {
    MPI_Send(sendbuf, count, type, root, 1, comm);
  }
  return 0;
}

template int* getRandomVector(size_t size);

template double* getRandomVector(size_t size);

template float* getRandomVector(size_t size);
