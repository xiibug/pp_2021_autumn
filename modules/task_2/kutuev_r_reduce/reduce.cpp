// Copyright 2021 Kutuev Roman

#include "../../../modules/task_2/kutuev_r_reduce/reduce.h"

int my_reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype,
              MPI_Op op, int root, MPI_Comm comm) {
  if (sendbuf == NULL || recvbuf == NULL) {
    return 0;
  }
  if (count <= 0) {
    return -1;
  }
  if (!(datatype != MPI_DOUBLE || datatype != MPI_FLOAT ||
        datatype != MPI_INT || datatype != MPI_LONG ||
        datatype != MPI_LONG_DOUBLE || datatype != MPI_LONG_LONG_INT ||
        datatype != MPI_SHORT || datatype != MPI_UNSIGNED ||
        datatype != MPI_UNSIGNED_LONG || datatype != MPI_UNSIGNED_SHORT)) {
    return -2;
  }
  if (!(op != MPI_MAX || op != MPI_MIN || op != MPI_SUM || op != MPI_PROD)) {
    return -3;
  }
  if (root < 0) {
    return -4;
  }
  if (comm != MPI_COMM_WORLD) {
    return -5;
  }

  int ProcRank;
  int ProcNum;
  void* buf;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  if (datatype == MPI_CHAR) {
    buf = new char[count];
  } else if (datatype == MPI_DOUBLE) {
    buf = new double[count];
  } else if (datatype == MPI_FLOAT) {
    buf = new float[count];
  } else if (datatype == MPI_INT) {
    buf = new int[count];
  } else if (datatype == MPI_LONG) {
    buf = new long[count];
  } else if (datatype == MPI_LONG_DOUBLE) {
    buf = new long double[count];
  } else if (datatype == MPI_LONG_LONG_INT) {
    buf = new long long int[count];
  } else if (datatype == MPI_SHORT) {
    buf = new short[count];
  } else if (datatype == MPI_UNSIGNED) {
    buf = new unsigned[count];
  } else if (datatype == MPI_UNSIGNED_CHAR) {
    buf = new unsigned char[count];
  } else if (datatype == MPI_UNSIGNED_LONG) {
    buf = new unsigned short[count];
  } else if (datatype == MPI_UNSIGNED_SHORT) {
    buf = new unsigned short[count];
  } else {
    return -6;
  }

  if (ProcRank != root) {
    MPI_Send(sendbuf, count, datatype, root, 0, comm);
  }

  if (ProcRank == root) {
    for (int i = 0; i < ProcNum; i++) {
      if (i == root) {
        if (datatype == MPI_DOUBLE) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<double*>(recvbuf)[j] <
                  static_cast<double*>(sendbuf)[j])
                static_cast<double*>(recvbuf)[j] =
                    static_cast<double*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<double*>(recvbuf)[j] >
                  static_cast<double*>(sendbuf)[j])
                static_cast<double*>(recvbuf)[j] =
                    static_cast<double*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<double*>(recvbuf)[j] +=
                  static_cast<double*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<double*>(recvbuf)[j] *=
                  static_cast<double*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_FLOAT) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<float*>(recvbuf)[j] <
                  static_cast<float*>(sendbuf)[j])
                static_cast<char*>(recvbuf)[j] =
                    static_cast<float*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<float*>(recvbuf)[j] >
                  static_cast<float*>(sendbuf)[j])
                static_cast<float*>(recvbuf)[j] =
                    static_cast<float*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<float*>(recvbuf)[j] +=
                  static_cast<float*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<float*>(recvbuf)[j] +=
                  static_cast<float*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_INT) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<int*>(recvbuf)[j] < static_cast<int*>(sendbuf)[j])
                static_cast<int*>(recvbuf)[j] = static_cast<int*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<int*>(recvbuf)[j] > static_cast<int*>(sendbuf)[j])
                static_cast<int*>(recvbuf)[j] = static_cast<int*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<int*>(recvbuf)[j] += static_cast<int*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<int*>(recvbuf)[j] *= static_cast<int*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_LONG) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<long*>(recvbuf)[j] <
                  static_cast<long*>(sendbuf)[j])
                static_cast<long*>(recvbuf)[j] = static_cast<long*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<long*>(recvbuf)[j] >
                  static_cast<long*>(sendbuf)[j])
                static_cast<long*>(recvbuf)[j] = static_cast<long*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<long*>(recvbuf)[j] += static_cast<long*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<long*>(recvbuf)[j] *= static_cast<long*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_LONG_DOUBLE) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<long double*>(recvbuf)[j] <
                  static_cast<long double*>(sendbuf)[j])
                static_cast<long double*>(recvbuf)[j] =
                    static_cast<long double*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<long double*>(recvbuf)[j] >
                  static_cast<long double*>(sendbuf)[j])
                static_cast<long double*>(recvbuf)[j] =
                    static_cast<long double*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<long double*>(recvbuf)[j] +=
                  static_cast<long double*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<long double*>(recvbuf)[j] *=
                  static_cast<long double*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_LONG_LONG_INT) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<long long int*>(recvbuf)[j] <
                  static_cast<long long int*>(sendbuf)[j])
                static_cast<long long int*>(recvbuf)[j] =
                    static_cast<long long int*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<long long int*>(recvbuf)[j] >
                  static_cast<long long int*>(sendbuf)[j])
                static_cast<long long int*>(recvbuf)[j] =
                    static_cast<long long int*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<long long int*>(recvbuf)[j] +=
                  static_cast<long long int*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<long long int*>(recvbuf)[j] *=
                  static_cast<long long int*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_SHORT) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<short*>(recvbuf)[j] <
                  static_cast<short*>(sendbuf)[j])
                static_cast<short*>(recvbuf)[j] =
                    static_cast<short*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<short*>(recvbuf)[j] >
                  static_cast<short*>(sendbuf)[j])
                static_cast<short*>(recvbuf)[j] =
                    static_cast<short*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<short*>(recvbuf)[j] +=
                  static_cast<short*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<short*>(recvbuf)[j] *=
                  static_cast<short*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_UNSIGNED) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<unsigned*>(recvbuf)[j] <
                  static_cast<unsigned*>(sendbuf)[j])
                static_cast<unsigned*>(recvbuf)[j] =
                    static_cast<unsigned*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<unsigned*>(recvbuf)[j] >
                  static_cast<unsigned*>(sendbuf)[j])
                static_cast<unsigned*>(recvbuf)[j] =
                    static_cast<unsigned*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<unsigned*>(recvbuf)[j] +=
                  static_cast<unsigned*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<unsigned*>(recvbuf)[j] *=
                  static_cast<unsigned*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_UNSIGNED_LONG) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<unsigned long*>(recvbuf)[j] <
                  static_cast<unsigned long*>(sendbuf)[j])
                static_cast<unsigned long*>(recvbuf)[j] =
                    static_cast<unsigned long*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<unsigned long*>(recvbuf)[j] >
                  static_cast<unsigned long*>(sendbuf)[j])
                static_cast<unsigned long*>(recvbuf)[j] =
                    static_cast<unsigned long*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<unsigned long*>(recvbuf)[j] +=
                  static_cast<unsigned long*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<unsigned long*>(recvbuf)[j] *=
                  static_cast<unsigned long*>(sendbuf)[j];
            }
          }
        } else if (datatype == MPI_UNSIGNED_SHORT) {
          if (op == MPI_MAX) {
            for (int j = 0; j < count; j++) {
              if (static_cast<unsigned short*>(recvbuf)[j] <
                  static_cast<unsigned short*>(sendbuf)[j])
                static_cast<unsigned short*>(recvbuf)[j] =
                    static_cast<unsigned short*>(sendbuf)[j];
            }
          } else if (op == MPI_MIN) {
            for (int j = 0; j < count; j++) {
              if (static_cast<unsigned short*>(recvbuf)[j] >
                  static_cast<unsigned short*>(sendbuf)[j])
                static_cast<unsigned short*>(recvbuf)[j] =
                    static_cast<unsigned short*>(sendbuf)[j];
            }
          } else if (op == MPI_SUM) {
            for (int j = 0; j < count; j++) {
              static_cast<unsigned short*>(recvbuf)[j] +=
                  static_cast<unsigned short*>(sendbuf)[j];
            }
          } else if (op == MPI_PROD) {
            for (int j = 0; j < count; j++) {
              static_cast<unsigned short*>(recvbuf)[j] *=
                  static_cast<unsigned short*>(sendbuf)[j];
            }
          }
        }
        continue;
      }

      MPI_Status status;
      MPI_Recv(buf, count, datatype, MPI_ANY_SOURCE, 0, comm, &status);
      if (datatype == MPI_DOUBLE) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<double*>(recvbuf)[j] < static_cast<double*>(buf)[j])
              static_cast<double*>(recvbuf)[j] = static_cast<double*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<double*>(recvbuf)[j] > static_cast<double*>(buf)[j])
              static_cast<double*>(recvbuf)[j] = static_cast<double*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<double*>(recvbuf)[j] += static_cast<double*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<double*>(recvbuf)[j] *= static_cast<double*>(buf)[j];
          }
        }
      } else if (datatype == MPI_FLOAT) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<float*>(recvbuf)[j] < static_cast<float*>(buf)[j])
              static_cast<float*>(recvbuf)[j] = static_cast<float*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<float*>(recvbuf)[j] > static_cast<float*>(buf)[j])
              static_cast<float*>(recvbuf)[j] = static_cast<float*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<float*>(recvbuf)[j] += static_cast<float*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<float*>(recvbuf)[j] *= static_cast<float*>(buf)[j];
          }
        }
      } else if (datatype == MPI_INT) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<int*>(recvbuf)[j] < static_cast<int*>(buf)[j])
              static_cast<int*>(recvbuf)[j] = static_cast<int*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<int*>(recvbuf)[j] > static_cast<int*>(buf)[j])
              static_cast<int*>(recvbuf)[j] = static_cast<int*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<int*>(recvbuf)[j] += static_cast<int*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<int*>(recvbuf)[j] *= static_cast<int*>(buf)[j];
          }
        }
      } /*else if (datatype == MPI_LONG) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<long*>(recvbuf)[j] < static_cast<long*>(buf)[j])
              static_cast<long*>(recvbuf)[j] = static_cast<long*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<long*>(recvbuf)[j] > static_cast<long*>(buf)[j])
              static_cast<long*>(recvbuf)[j] = static_cast<long*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<long*>(recvbuf)[j] += static_cast<long*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<long*>(recvbuf)[j] *= static_cast<long*>(buf)[j];
          }
        }
      } else if (datatype == MPI_LONG_DOUBLE) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<long double*>(recvbuf)[j] <
                static_cast<long double*>(buf)[j])
              static_cast<long double*>(recvbuf)[j] =
                  static_cast<long double*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<long double*>(recvbuf)[j] >
                static_cast<long double*>(buf)[j])
              static_cast<long double*>(recvbuf)[j] =
                  static_cast<long double*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<long double*>(recvbuf)[j] +=
                static_cast<long double*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<long double*>(recvbuf)[j] *=
                static_cast<long double*>(buf)[j];
          }
        }
      } else if (datatype == MPI_LONG_LONG_INT) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<long long int*>(recvbuf)[j] <
                static_cast<long long int*>(buf)[j])
              static_cast<long long int*>(recvbuf)[j] =
                  static_cast<long long int*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<long long int*>(recvbuf)[j] >
                static_cast<long long int*>(buf)[j])
              static_cast<long long int*>(recvbuf)[j] =
                  static_cast<long long int*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<long long int*>(recvbuf)[j] +=
                static_cast<long long int*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<long long int*>(recvbuf)[j] *=
                static_cast<long long int*>(buf)[j];
          }
        }
      } else if (datatype == MPI_SHORT) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<short*>(recvbuf)[j] < static_cast<short*>(buf)[j])
              static_cast<short*>(recvbuf)[j] = static_cast<short*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<short*>(recvbuf)[j] > static_cast<short*>(buf)[j])
              static_cast<short*>(recvbuf)[j] = static_cast<short*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<short*>(recvbuf)[j] += static_cast<short*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<short*>(recvbuf)[j] *= static_cast<short*>(buf)[j];
          }
        }
      } else if (datatype == MPI_UNSIGNED) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<unsigned*>(recvbuf)[j] <
                static_cast<unsigned*>(buf)[j])
              static_cast<unsigned*>(recvbuf)[j] =
                  static_cast<unsigned*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<unsigned*>(recvbuf)[j] >
                static_cast<unsigned*>(buf)[j])
              static_cast<unsigned*>(recvbuf)[j] =
                  static_cast<unsigned*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<unsigned*>(recvbuf)[j] +=
                static_cast<unsigned*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<unsigned*>(recvbuf)[j] *=
                static_cast<unsigned*>(buf)[j];
          }
        }

      } else if (datatype == MPI_UNSIGNED_LONG) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<unsigned long*>(recvbuf)[j] <
                static_cast<unsigned long*>(buf)[j])
              static_cast<unsigned long*>(recvbuf)[j] =
                  static_cast<unsigned long*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<unsigned long*>(recvbuf)[j] >
                static_cast<unsigned long*>(buf)[j])
              static_cast<unsigned long*>(recvbuf)[j] =
                  static_cast<unsigned long*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<unsigned long*>(recvbuf)[j] +=
                static_cast<unsigned long*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<unsigned long*>(recvbuf)[j] *=
                static_cast<unsigned long*>(buf)[j];
          }
        }

      } else if (datatype == MPI_UNSIGNED_SHORT) {
        if (op == MPI_MAX) {
          for (int j = 0; j < count; j++) {
            if (static_cast<unsigned short*>(recvbuf)[j] <
                static_cast<unsigned short*>(buf)[j])
              static_cast<unsigned short*>(recvbuf)[j] =
                  static_cast<unsigned short*>(buf)[j];
          }
        } else if (op == MPI_MIN) {
          for (int j = 0; j < count; j++) {
            if (static_cast<unsigned short*>(recvbuf)[j] >
                static_cast<unsigned short*>(buf)[j])
              static_cast<unsigned short*>(recvbuf)[j] =
                  static_cast<unsigned short*>(buf)[j];
          }
        } else if (op == MPI_SUM) {
          for (int j = 0; j < count; j++) {
            static_cast<unsigned short*>(recvbuf)[j] +=
                static_cast<unsigned short*>(buf)[j];
          }
        } else if (op == MPI_PROD) {
          for (int j = 0; j < count; j++) {
            static_cast<unsigned short*>(recvbuf)[j] *=
                static_cast<unsigned short*>(buf)[j];
          }
        }
      }*/
    }
  }

  if (!(datatype != MPI_INT)) {
    delete[] static_cast<int*>(buf);
  } else if (datatype == MPI_FLOAT) {
    delete[] static_cast<float*>(buf);
  } else if (datatype == MPI_DOUBLE) {
    delete[] static_cast<double*>(buf);
  } else if (datatype == MPI_LONG) {
    delete[] static_cast<double*>(buf);
  } else if (datatype == MPI_LONG_DOUBLE) {
    delete[] static_cast<double*>(buf);
  } else if (datatype == MPI_LONG_LONG_INT) {
    delete[] static_cast<double*>(buf);
  } else if (datatype == MPI_SHORT) {
    delete[] static_cast<double*>(buf);
  } else if (datatype == MPI_UNSIGNED) {
    delete[] static_cast<double*>(buf);
  } else if (datatype == MPI_UNSIGNED_LONG) {
    delete[] static_cast<double*>(buf);
  } else if (datatype == MPI_UNSIGNED_SHORT) {
    delete[] static_cast<double*>(buf);
  }

  return 1;
}
