// Copyright 2021 Novozhilov Alexander
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_1/novozhilov_a_max_values_in_columns/max_values_in_columns.h"

std::vector<int> getRandomVector(int sz) {
	std::random_device dev;
	std::mt19937 gen(dev());
	std::vector<int> vec(sz);
	for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
	return vec;
}

std::vector<std::vector<int>> getRandomMatrix(int rows, int cols) {
	std::vector<std::vector<int>> matrix;
	for (int i = 0; i < rows; i++) {
		matrix.push_back(getRandomVector(cols));
	}
	return matrix;
}

std::vector<int> maxValuesInColumnsSequential(std::vector<std::vector<int>> matrix) {
	std::vector<int> result;
	for (int i = 0; i < matrix[0].size(); i++)
	{
		int max = matrix[0][i];
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[j][i] > max) {
				max = matrix[j][i];
			}
		}
		result.push_back(max);
	}
	return result;
}

std::vector<int> maxValuesInColumnsParallel(std::vector<std::vector<int>> matrix, int rows, int cols)
{
	int proc_count = 0, proc_rank = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

	std::vector<int> localResult(cols);
	std::vector<int> globalResult(cols);

	std::cout << "proc"<<proc_rank<<"\n";


	int row_per_proc = rows / proc_count;
	std::vector<std::vector<int>> proc_matrix;
	for (int i = 0; i < row_per_proc; i++)
	{
		proc_matrix.push_back(matrix[i]);
	}
	localResult = maxValuesInColumnsSequential(proc_matrix);

	MPI_Reduce(localResult.data(), globalResult.data(), cols, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (proc_rank == 0) {
		MPI_Reduce(localResult.data(), globalResult.data(), cols, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
		return globalResult;
	}
	

	
}

void printVector(std::vector<int> vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

void printMatrix(std::vector<std::vector<int>> matrix)
{
	for (auto i : matrix) {
		printVector(i);
	}
	std::cout << std::endl;
}
