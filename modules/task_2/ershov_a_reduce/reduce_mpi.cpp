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
    int typeSize;
    if (type == MPI_INT) {
      typeSize = sizeof(int);
    } else if (type == MPI_DOUBLE) {
      typeSize = sizeof(double);
    } else if (type == MPI_FLOAT) {
      typeSize = sizeof(float);
    }

    size_t memSize = typeSize * count;

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
            ((int*)(buf))[j] = ((int*)(sendbuf))[j];
          }
        }
        if (counter == 0) {
          for (int j = 0; j < count; ++j) {
            ((int*)(tmp))[j] = ((int*)(buf))[j];
          }
          counter++;
        } else {
          if (op == MPI_SUM) {
            for (int j = 0; j < count; ++j) {
              ((int*)(tmp))[j] += ((int*)(buf))[j];
            }
          } else if (op == MPI_MAX) {
            for (int j = 0; j < count; ++j) {
              if (((int*)(buf))[j] >= ((int*)(tmp))[j]) {
                ((int*)(tmp))[j] = ((int*)(buf))[j];
              }
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; ++j) {
              if (((int*)(buf))[j] <= ((int*)(tmp))[j]) {
                ((int*)(tmp))[j] = ((int*)(buf))[j];
              }
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; ++j) {
              ((int*)(tmp))[j] *= ((int*)(buf))[j];
            }
          }
        }
      }
      for (int i = 0; i < count; ++i) {
        ((int*)(recvbuf))[i] = ((int*)(tmp))[i];
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
            ((double*)(buf))[j] = ((double*)(sendbuf))[j];
          }
        }
        if (counter == 0) {
          for (int j = 0; j < count; ++j) {
            ((double*)(tmp))[j] = ((double*)(buf))[j];
          }
          counter++;
        } else {
          if (op == MPI_SUM) {
            for (int j = 0; j < count; ++j) {
              ((double*)(tmp))[j] += ((double*)(buf))[j];
            }
          } else if (op == MPI_MAX) {
            for (int j = 0; j < count; ++j) {
              if (((double*)(buf))[j] >= ((double*)(tmp))[j]) {
                ((double*)(tmp))[j] = ((double*)(buf))[j];
              }
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; ++j) {
              if (((double*)(buf))[j] <= ((double*)(tmp))[j]) {
                ((double*)(tmp))[j] = ((double*)(buf))[j];
              }
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; ++j) {
              ((double*)(tmp))[j] *= ((double*)(buf))[j];
            }
          }
        }
      }
      for (int i = 0; i < count; ++i) {
        ((double*)(recvbuf))[i] = ((double*)(tmp))[i];
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
            ((float*)(buf))[j] = ((float*)(sendbuf))[j];
          }
        }
        if (counter == 0) {
          for (int j = 0; j < count; ++j) {
            ((float*)(tmp))[j] = ((float*)(buf))[j];
          }
          counter++;
        } else {
          if (op == MPI_SUM) {
            for (int j = 0; j < count; ++j) {
              ((float*)(tmp))[j] += ((float*)(buf))[j];
            }
          } else if (op == MPI_MAX) {
            for (int j = 0; j < count; ++j) {
              if (((float*)(buf))[j] >= ((float*)(tmp))[j]) {
                ((float*)(tmp))[j] = ((float*)(buf))[j];
              }
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; ++j) {
              if (((float*)(buf))[j] <= ((float*)(tmp))[j]) {
                ((float*)(tmp))[j] = ((float*)(buf))[j];
              }
            }
          } else if (op == MPI_PROD) {
            for (int i = 0; i < count; ++i) {
              ((float*)(tmp))[i] *= ((float*)(buf))[i];
            }
          }
        }
      }
      for (int i = 0; i < count; ++i) {
        ((float*)(recvbuf))[i] = ((float*)(tmp))[i];
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