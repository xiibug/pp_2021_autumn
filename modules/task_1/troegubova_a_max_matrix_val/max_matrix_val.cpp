// Copyright 2021 Troegubova Alexandra
#include <mpi.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_1/troegubova_a_max_matrix_val/max_matrix_val.h"

//the matrix has the form matrix[i][j]: = vector[(i - 1) * columns + j - 1 ], 
//range of values of matrix elements: [-200; 200]
std::vector<int> getRandomMatrix(int lines, int columns) {
	srand(time(NULL));
	int matrix_size = lines * columns;
	std::vector<int> matrix(matrix_size);
	for (int i = 0; i < matrix_size; i++) { 
		matrix[i] = rand() % 401 - 200; }
	return matrix;
}

int getSequentialMax(const std::vector<int> &matrix) 
{
	const int  matrix_size = matrix.size();
	int max_elem = matrix[0];
	for (int i = 1; i < matrix_size; i++){
		max_elem = std::max(max_elem, matrix[i]);
	}
	return max_elem;
}

int getParallelMax(const std::vector<int> &matrix, const int matrix_size) {
	int count, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &count);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int whole = matrix_size / count;
	const int remains = matrix_size % count;
	const int num_elem_block = whole + (rank < remains ? 1 : 0);
	int first_elem, local_max;
	std::vector<int> local_matrix(num_elem_block);
	
	if (rank == 0) {
		local_matrix = std::vector<int>(matrix.begin(), matrix.begin() + num_elem_block);
		if (remains) {
			for(int proc = 1; proc < remains; proc++) {
				MPI_Send(matrix.data() + proc * num_elem_block, num_elem_block, MPI_INT, proc, 0, MPI_COMM_WORLD);
			}
			if (whole) {
				for (int proc = remains, i = 0; proc < count; proc++, i++) {
					MPI_Send(matrix.data() + remains * num_elem_block + i * (num_elem_block - 1), num_elem_block - 1, MPI_INT, proc, 0, MPI_COMM_WORLD);
				}
			}
			else{
				for (int proc = remains, i = 0; proc < count; proc++, i++) {
					MPI_Send(matrix.data(), 1, MPI_INT, proc, 0, MPI_COMM_WORLD);
				}
			}
		}
		else
		{
			for (int proc = 1; proc < count; proc++) {
				MPI_Send(matrix.data() + proc * num_elem_block, num_elem_block, MPI_INT, proc, 0, MPI_COMM_WORLD);
			}
		}
		local_max = getSequentialMax(local_matrix);
	}
	else {
		if (whole) {
			MPI_Status status;
			MPI_Recv(local_matrix.data(), num_elem_block, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			local_max = getSequentialMax(local_matrix);
		}
		else {
			if (rank < remains) {
				MPI_Status status;
				MPI_Recv(local_matrix.data(), num_elem_block, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
				local_max = getSequentialMax(local_matrix);
			}
			else {
				MPI_Status status;
				MPI_Recv(&first_elem, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
				local_max = first_elem;
			}	
		}
	}

	int global_max;
	MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	return global_max;
}

