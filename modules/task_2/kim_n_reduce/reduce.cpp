// Copyright 2021 Kim Nikita
#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_2/kim_n_reduce/reduce.h"

template <class T>
std::vector<T> getRandomVector(int size) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<T> res(size);
  for (int i = 0; i < size; i++)
    res[i] = static_cast<T>(gen() % 100);
  return res;
}

template
std::vector<int> getRandomVector<int>(int size);

template
std::vector<float> getRandomVector<float>(int size);

template
std::vector<double> getRandomVector<double>(int size);

int Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype type, MPI_Op op, int root, MPI_Comm comm) {
  int proc_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
  if (proc_rank == root) {
	int proc_num;
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Status status;
	if (type == MPI_INT) {
	  for (int i = 0; i < count; i++)
	    (static_cast<int*>(recvbuf))[i] = (static_cast<int*>(sendbuf))[i];
	  int* tmp = new int[count];
	  for (int i = 0; i < proc_num - 1; i++) {
		MPI_Recv(tmp, count, type, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &status);
		for (int j = 0; j < count; j++) {
		  if (op == MPI_MAX) {
			if (tmp[j] > (static_cast<int*>(recvbuf))[j])
			  (static_cast<int*>(recvbuf))[j] = tmp[j];
		  } else if (op == MPI_MIN) {
			if (tmp[j] < (static_cast<int*>(recvbuf))[j])
			  (static_cast<int*>(recvbuf))[j] = tmp[j];
		  } else if (op == MPI_SUM) {
			(static_cast<int*>(recvbuf))[j] += tmp[j];
		  } else if (op == MPI_PROD)
			(static_cast<int*>(recvbuf))[j] *= tmp[j];
		  else
			return -2;
		}
	  }
	  delete[] tmp;
	}
	else if (type == MPI_FLOAT) {
	  for (int i = 0; i < count; i++)
	    (static_cast<float*>(recvbuf))[i] = (static_cast<float*>(sendbuf))[i];
	  float* tmp = new float[count];
	  for (int i = 0; i < proc_num - 1; i++) {
		MPI_Recv(tmp, count, type, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &status);
		for (int j = 0; j < count; j++) {
		  if (op == MPI_MAX) {
			if (tmp[j] - (static_cast<float*>(recvbuf))[j] > 1e-10)
			  (static_cast<float*>(recvbuf))[j] = tmp[j];
		  } else if (op == MPI_MIN) {
			if ((static_cast<float*>(recvbuf))[j] - tmp[j] > 1e-10 )
			  (static_cast<float*>(recvbuf))[j] = tmp[j];
		  } else if (op == MPI_SUM) {
			(static_cast<float*>(recvbuf))[j] += tmp[j];
		  } else if (op == MPI_PROD)
			(static_cast<float*>(recvbuf))[j] *= tmp[j];
		  else
			return -3;
		}
	  }
	  delete[] tmp;
	}
	else if (type == MPI_DOUBLE) {
	  for (int i = 0; i < count; i++)
	    (static_cast<double*>(recvbuf))[i] = (static_cast<double*>(sendbuf))[i];
	  double* tmp = new double[count];
	  for (int i = 0; i < proc_num - 1; i++) {
		MPI_Recv(tmp, count, type, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &status);
		for (int j = 0; j < count; j++) {
		  if (op == MPI_MAX) {
			if (tmp[j] - (static_cast<double*>(recvbuf))[j] > 1e-10)
			  (static_cast<double*>(recvbuf))[j] = tmp[j];
		  } else if (op == MPI_MIN) {
			if ((static_cast<double*>(recvbuf))[j] - tmp[j] > 1e-10 )
			  (static_cast<double*>(recvbuf))[j] = tmp[j];
		  } else if (op == MPI_SUM) {
			(static_cast<double*>(recvbuf))[j] += tmp[j];
		  } else if (op == MPI_PROD)
			(static_cast<double*>(recvbuf))[j] *= tmp[j];
		  else
			return -4;
		}
	  }
	  delete[] tmp;
	}
	else
	  return -1;
  } else 
	MPI_Send(sendbuf, count, type, root, proc_rank, comm);
  return 0;
}
