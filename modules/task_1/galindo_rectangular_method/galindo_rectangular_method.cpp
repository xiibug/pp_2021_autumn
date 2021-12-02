#include <mpi.h>
#include <cmath>
#include "galindo_rectangular_method.h"

double def_int(std::function<double(double)> funct, double a, double b, int count) {
	double sfc = 0;
	double h = (b - a) / count;
	for (int i = 0; i < count; i++) {
		sfc += funct(a + i * h);
	}
	double res = h * sfc;
	return res;
}

double parallel_int(std::function<double(double)> funct, double a, double b, int count) {
	int rank, size;
	double sfc = (b - a) / count;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_size(MPI_COMM_WORLD, &rank);
	int l_count = count / size;
	double res = 0, l_res = 0,
		l_a = a + rank * l_count * sfc,
		l_b = l_a + l_count * sfc;
	if (rank != size - 1) {
		l_res = def_int(funct, l_a, l_b, l_count);
	}
	else {
		l_res = def_int(funct, l_a, b, count - l_count * (size - 1));
	}
	MPI_Reduce(&l_res, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	return res;
}
double func(double x) {
	return(2 * x * x * x - 7 * x + 4);
}


