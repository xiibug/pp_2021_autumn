// Copyright 2021 Zarubin Mikhail
#include <algorithm>
#include <mpi.h>
#include <random>
#include <vector>
#include "../../../modules/task_1/zarubin_m_sum_values_on_rows_matrix/sum_values_on_rows_matrix.h"


void getRandomMatrix(std::vector<int>& matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column) {
    std::random_device dev;
    std::mt19937 gen(dev());
    for (std::vector<int>::size_type i = 0; i < count_row; i++) {
        for (std::vector<int>::size_type j = 0; j < count_column; j++) {
            matrix[i * count_column + j] = gen() % 100;
        } 
    }
}

std::vector<int> transposeMatrix(const std::vector<int>& matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column) {
    std::vector<int> transposed_matrix(count_row * count_column);
    for (std::vector<int>::size_type i = 0; i < count_column; i++) {
        for (std::vector<int>::size_type j = 0; j < count_row; j++) {
            transposed_matrix[i * count_row + j] = matrix[j * count_column + i];
        }
    }
    return transposed_matrix;
}

std::vector<int> getSequentialOperations(const std::vector<int>& matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column) {
    std::vector<int> result(count_row);
    for (std::vector<int>::size_type i = 0; i < count_row; i++) {
        for (std::vector<int>::size_type j = 0; j < count_column; j++) {
            result[i] += matrix[i * count_column + j];
        }
    }
    return result;
}

std::vector<int> getParallelOperations(const std::vector<int>& global_matrix, std::vector<int>::size_type count_row, std::vector<int>::size_type count_column) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> transposed_matrix = transposeMatrix(global_matrix, count_row, count_column);
    std::vector<int>::size_type count_proc_column = count_column / size;

    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            std::vector<int>::size_type step = proc * count_proc_column * count_row;
            if (count_column % size != 0) {
                step += (count_column % size) * count_row;
            }
            MPI_Send(transposed_matrix.data() + step, static_cast<int>(count_row * count_proc_column),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0 && count_column % size != 0) {
        count_proc_column += count_column % size;
    }

    std::vector<int> local_matrix(count_row * count_proc_column);
    if (rank == 0) {
        for (std::vector<int>::size_type i = 0; i < count_row * count_proc_column;  i++) {
            local_matrix[i] = transposed_matrix[i];
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_matrix.data(), static_cast<int>(count_proc_column * count_row),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    local_matrix = transposeMatrix(local_matrix, count_proc_column, count_row);

    std::vector<int> global_sum(count_row);
    std::vector<int> local_sum = getSequentialOperations(local_matrix, count_row, count_proc_column);

    /*printf("ProcNum = %i, LocalSum\n", rank);
    for (auto i : local_sum)
    {
        printf("%i ", i);
    }
    printf("\n");*/

    MPI_Reduce(local_sum.data(), global_sum.data(), static_cast<int>(local_sum.size()), MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum;
}
