#include "RectangleMethod.h"
#include <vector>
#include <iostream>
#include <iomanip>

std::vector<std::function<double(double)>> functions = {
	[](double x) {return sin(x);},
	[](double x) {return (-x + 3.0);},
	[](double x) {return (x * x + 2.0 * x + 1.0);},
	[](double x) {return (1.5 * x * x * x + x * x + 1.3 * x + 3.0);},
	[](double x) {return cos(x);}
};

double IntegralSequential(double a, double b, int n, int foo_index) {
	double h = (b - a) / n;
	double sum = 0.0;
	for (int i = 0; i < n; i ++) {
		sum += functions[foo_index](a + h * (i + 0.5));
	}
	return (sum*h);
}

double IntegralParallel(double a, double b, int n, int foo_index) {
	double h = (b - a) / n;
	double sum = 0.0;
	double myres, res = 0.0;
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&foo_index, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = rank; i < n; i += size) {
		sum += functions[foo_index](a + h * (i + 0.5));
	}
	myres = sum * h;
	MPI_Reduce(&myres, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	return res;
}
