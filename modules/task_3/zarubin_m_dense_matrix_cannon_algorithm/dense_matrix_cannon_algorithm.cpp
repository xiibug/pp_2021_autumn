// Copyright 2021 Zarubin Mikhail
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_3/zarubin_m_dense_matrix_cannon_algorithm/dense_matrix_cannon_algorithm.h"


void generateRandomMatrix(std::vector<double>* matrix,
    std::vector<double>::size_type size, 
    int left_border, int right_border) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<> urd(left_border, right_border);
    for (std::vector<double>::size_type i = 0; i < size * size; i++) {
        (*matrix)[i] = urd(gen);
    }
}

void getSequentialOperations(const std::vector<double>& first_matrix,
    const std::vector<double>& second_matrix,
    std::vector<double>* answer,
    std::vector<double>::size_type size) {
    for (std::vector<double>::size_type i = 0; i < size; ++i) {
        for (std::vector<double>::size_type j = 0; j < size; ++j) {
            for (std::vector<double>::size_type k = 0; k < size; ++k) {
                (*answer)[i * size + j] += first_matrix[i * size + k] * second_matrix[j + k * size];
            }
        }
    }
}

int calculateActualSize(int old_size,
    std::vector<double>::size_type matrix_size) {
    int sqrt_size = static_cast<int>(sqrt(old_size));
    for (; matrix_size % sqrt_size && sqrt_size >= 2; --sqrt_size);
    return sqrt_size * sqrt_size;
}

void getPartMatrix(const std::vector<double>& orig_matrix,
    std::vector<double>::size_type matrix_size,
    std::vector<double>* part_matrix,
    std::vector<double>::size_type local_size,
    std::vector<double>::size_type count_parts,
    std::vector<double>::size_type start_offset) {
    for (std::vector<double>::size_type i = 0; i < local_size * local_size; ++i) {
        std::vector<double>::size_type global_offset = matrix_size * (i / local_size);
        std::vector<double>::size_type local_offset = i % local_size;

        (*part_matrix)[i] = orig_matrix[start_offset + local_offset + global_offset];
    }

}

std::vector<double> getParallelOperations(const std::vector<double>& first_matrix,
    const std::vector<double>& second_matrix,
    std::vector<double>::size_type matrix_size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int actual_size = calculateActualSize(size, matrix_size);

    MPI_Group MPI_GROUP, MPI_ACTUAL_GROUP;
    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP);

    std::vector<int> actual_proc_vector(actual_size);
    for (int i = 0; i < actual_size; ++i)
        actual_proc_vector[i] = i;

    MPI_Comm MPI_ACTUAL_PROC;
    MPI_Group_incl(MPI_GROUP, actual_size, actual_proc_vector.data(), &MPI_ACTUAL_GROUP);
    MPI_Comm_create(MPI_COMM_WORLD, MPI_ACTUAL_GROUP, &MPI_ACTUAL_PROC);

    std::vector<double> global_answer(matrix_size * matrix_size, 0.0);
    if (size < 4 || actual_size < 4) {

        if (rank == 0)
            getSequentialOperations(first_matrix, second_matrix, &global_answer, matrix_size);

        return global_answer;
    }

    if (rank >= actual_size)
        return global_answer;

    int count_parts = static_cast<int>(sqrt(actual_size));
    std::vector<double>::size_type local_size = matrix_size / count_parts;

    if (rank == 0) {
        for (int proc = 1; proc < actual_size; ++proc) {
            std::vector<double>::size_type step = (proc / count_parts) * matrix_size * local_size +
                proc % count_parts * local_size;

            std::vector<double> part_first_matrix(local_size * local_size, 0.0);
            std::vector<double> part_second_matrix(local_size * local_size, 0.0);

            getPartMatrix(first_matrix, matrix_size, &part_first_matrix, local_size, count_parts, step);
            getPartMatrix(second_matrix, matrix_size, &part_second_matrix, local_size, count_parts, step);

            MPI_Send(part_first_matrix.data(), static_cast<int>(local_size * local_size),
                MPI_DOUBLE, proc, 1, MPI_ACTUAL_PROC);
            MPI_Send(part_second_matrix.data(), static_cast<int>(local_size * local_size),
                MPI_DOUBLE, proc, 2, MPI_ACTUAL_PROC);
        }
    }

    std::vector<double> local_first_matrix(local_size * local_size, 0.0);
    std::vector<double> local_second_matrix(local_size * local_size, 0.0);

    if (rank == 0) {
        getPartMatrix(first_matrix, matrix_size, &local_first_matrix, local_size, count_parts, 0);
        getPartMatrix(second_matrix, matrix_size, &local_second_matrix, local_size, count_parts, 0);
    }
    else {
        MPI_Status status;
        MPI_Recv(local_first_matrix.data(), static_cast<int>(local_size * local_size),
            MPI_DOUBLE, 0, 1, MPI_ACTUAL_PROC, &status);
        MPI_Recv(local_second_matrix.data(), static_cast<int>(local_size * local_size),
            MPI_DOUBLE, 0, 2, MPI_ACTUAL_PROC, &status);
    }

    std::vector<double> local_answer_vector(local_size * local_size, 0.0);
    std::vector<double> local_answer_matrix(matrix_size * matrix_size, 0.0);

    int proc_number_row = rank / count_parts;
    int proc_number_column = rank % count_parts;

    int init_recipient_a = ((rank - proc_number_row) / count_parts == proc_number_row && rank - proc_number_row >= 0) ? rank - proc_number_row : rank + count_parts - proc_number_row;
    int init_recipient_b = rank - proc_number_column * count_parts >= 0 ? rank - proc_number_column * count_parts : actual_size + (rank - proc_number_column * count_parts);
    int init_sender_a = (rank + proc_number_row) / count_parts == proc_number_row ? rank + proc_number_row : rank - count_parts + proc_number_row;
    int init_sender_b = rank + proc_number_column * count_parts < actual_size ? rank + proc_number_column * count_parts : (rank + proc_number_column * count_parts) - actual_size;

    MPI_Status status;

    if (proc_number_row > 0) {
        MPI_Sendrecv_replace(local_first_matrix.data(), static_cast<int>(local_size * local_size),
            MPI_DOUBLE, init_recipient_a, 1, init_sender_a, 1, MPI_ACTUAL_PROC, &status);
    }

    if (proc_number_column > 0) {
        MPI_Sendrecv_replace(local_second_matrix.data(), static_cast<int>(local_size * local_size),
            MPI_DOUBLE, init_recipient_b, 2, init_sender_b, 2, MPI_ACTUAL_PROC, &status);
    }

    int recipient_a = ((rank - 1) / count_parts == proc_number_row && rank - 1 >= 0) ? rank - 1 : rank + count_parts - 1;
    int recipient_b = rank - count_parts >= 0 ? rank - count_parts : actual_size + (rank - count_parts);
    int sender_a = (rank + 1) / count_parts == proc_number_row ? rank + 1 : rank - count_parts + 1;
    int sender_b = rank + count_parts < actual_size ? rank + count_parts : (rank + count_parts) - actual_size;

    for (int i = 0; i < count_parts; ++i) {
        getSequentialOperations(local_first_matrix, local_second_matrix, &local_answer_vector, local_size);

        MPI_Sendrecv_replace(local_first_matrix.data(), static_cast<int>(local_size * local_size),
            MPI_DOUBLE, recipient_a, 1, sender_a, 1, MPI_ACTUAL_PROC, &status);
        MPI_Sendrecv_replace(local_second_matrix.data(), static_cast<int>(local_size * local_size),
            MPI_DOUBLE, recipient_b, 2, sender_b, 2, MPI_ACTUAL_PROC, &status);
    }

    for (std::vector<double>::size_type i = 0; i < local_answer_vector.size(); i++) {
        int row = (rank / count_parts) * local_size + i / local_size;
        int column = (rank % count_parts) * local_size + i % local_size;
        
        local_answer_matrix[row * matrix_size + column] = local_answer_vector[i];
    }

    MPI_Reduce(local_answer_matrix.data(), global_answer.data(), static_cast<int>(matrix_size * matrix_size),
        MPI_DOUBLE, MPI_SUM, 0, MPI_ACTUAL_PROC);

    return global_answer;
}
