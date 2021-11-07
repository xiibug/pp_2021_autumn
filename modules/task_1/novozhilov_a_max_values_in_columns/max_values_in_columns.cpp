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
	for (long unsigned int i = 0; i < matrix[0].size(); i++)
	{
		int max = matrix[0][i];
		for (long unsigned int j = 0; j < matrix.size(); j++)
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
	int size = 0, rank = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int rows_per_proc = rows / size;
	if (rank == 0) {
		for (int proc = 1; proc < size; proc++) {
			for (int i = 0; i < rows_per_proc; i++)
			{
				MPI_Send(matrix[proc * rows_per_proc + i].data(), cols, MPI_INT, proc, 0, MPI_COMM_WORLD);
			}
		}
	}

	std::vector<int> local_vec(cols);
	std::vector<std::vector<int>> local_matrix;
	std::vector<int> global_vec(cols);
	if (rank == 0) {
		for (int i = 0; i < rows_per_proc; i++)
		{
			local_matrix.push_back(matrix[i]);
		}
		if (rows % size != 0)
		{
			for (long unsigned int i = matrix.size() - rows % size; i < matrix.size(); i++)
			{
				local_matrix.push_back(matrix[i]);
			}
		}
		local_vec = maxValuesInColumnsSequential(local_matrix);
	}
	else {
		MPI_Status status;
		for (int i = 0; i < rows_per_proc; i++)
		{
			MPI_Recv(local_vec.data(), cols, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			local_matrix.push_back(local_vec);
		}
		local_vec = maxValuesInColumnsSequential(local_matrix);
	}

	MPI_Reduce(local_vec.data(), global_vec.data(), cols, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	return global_vec;
}

void printVector(std::vector<int> vector)
{
	for (long unsigned int i = 0; i < vector.size(); i++)
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
