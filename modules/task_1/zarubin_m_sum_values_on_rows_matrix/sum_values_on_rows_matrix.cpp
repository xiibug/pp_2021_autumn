// Copyright 2021 Zarubin Mikhail
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_1/zarubin_m_sum_values_on_rows_matrix/sum_values_on_rows_matrix.h"


void generateRandomMatrix(std::vector<int>* matrix,
    std::vector<int>::size_type count_rows, std::vector<int>::size_type count_columnss) {
    std::random_device dev;
    std::mt19937 gen(dev());
    for (std::vector<int>::size_type i = 0; i < count_rows; i++) {
        for (std::vector<int>::size_type j = 0; j < count_columnss; j++) {
            (*matrix)[i * count_columnss + j] = gen() % 100;
        }
    }
}

std::vector<int> transposeMatrix(const std::vector<int>& matrix,
    std::vector<int>::size_type count_rows, std::vector<int>::size_type count_columns) {
    std::vector<int> transposed_matrix(count_rows * count_columns);
    for (std::vector<int>::size_type i = 0; i < count_columns; i++) {
        for (std::vector<int>::size_type j = 0; j < count_rows; j++) {
            transposed_matrix[i * count_rows + j] = matrix[j * count_columns + i];
        }
    }
    return transposed_matrix;
}

std::vector<int> getSequentialOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type count_rows, std::vector<int>::size_type count_columns) {
    std::vector<int> result(count_rows);
    for (std::vector<int>::size_type i = 0; i < count_rows; i++) {
        for (std::vector<int>::size_type j = 0; j < count_columns; j++) {
            result[i] += matrix[i * count_columns + j];
        }
    }
    return result;
}

std::vector<int> getParallelOperations(const std::vector<int>& global_matrix,
    std::vector<int>::size_type count_rows, std::vector<int>::size_type count_columns) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> transposed_matrix(count_rows * count_columns);
    std::vector<int>::size_type count_proc_column = count_columns / size;

    if (rank == 0) {
        transposed_matrix = transposeMatrix(global_matrix, count_rows, count_columns);
        for (int proc = 1; proc < size; proc++) {
            std::vector<int>::size_type step = proc * count_proc_column * count_rows;
            if (count_columns % size != 0) {
                step += (count_columns % size) * count_rows;
            }
            MPI_Send(transposed_matrix.data() + step, static_cast<int>(count_rows * count_proc_column),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0 && count_columns % size != 0) {
        count_proc_column += count_columns % size;
    }

    std::vector<int> local_matrix(count_rows * count_proc_column);
    if (rank == 0) {
        for (std::vector<int>::size_type i = 0; i < count_rows * count_proc_column;  i++) {
            local_matrix[i] = transposed_matrix[i];
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_matrix.data(), static_cast<int>(count_proc_column * count_rows),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    local_matrix = transposeMatrix(local_matrix, count_proc_column, count_rows);

    std::vector<int> global_sum(count_rows);
    std::vector<int> local_sum = getSequentialOperations(local_matrix, count_rows, count_proc_column);

    MPI_Reduce(local_sum.data(), global_sum.data(), static_cast<int>(local_sum.size()),
        MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum;
}
