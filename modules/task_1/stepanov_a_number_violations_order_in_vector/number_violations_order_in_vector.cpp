// Copyright 2021 Stepanov Alexander
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_1/stepanov_a_number_violations_order_in_vector/number_violations_order_in_vector.h"


void generateRandomVector(std::vector<int>* vector) {
    std::random_device dev;
    std::mt19937 gen(dev());
    for (std::vector<int>::size_type i = 0; i < (*vector).size(); ++i) {
        (*vector)[i] = gen() % 100;
    }
}

int getSequentialOperations(const std::vector<int>& vector) {
    int number_violations = 0;
    for (std::vector<int>::size_type i = 1; i < vector.size(); ++i) {
        if (vector[i - 1] > vector[i])
            ++number_violations;
    }
    return number_violations;
}

int getParallelOperations(const std::vector<int>& global_vector,
    std::vector<int>::size_type global_size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type local_size = global_size / size;
    std::vector<int>::size_type remains = global_size % size;

    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            std::vector<int>::size_type step = proc * local_size + remains;

            MPI_Send(global_vector.data() + step - 1, static_cast<int>(local_size + 1),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }

    local_size = rank == 0 ? local_size + remains : local_size + 1;
    std::vector<int> local_vector(local_size);
    if (rank == 0) {
        for (std::vector<int>::size_type i = 0; i < local_size; i++) {
            local_vector[i] = global_vector[i];
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_vector.data(), static_cast<int>(local_size),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    int local_ans = getSequentialOperations(local_vector);
    int global_ans = 0;

    MPI_Reduce(&local_ans, &global_ans, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_ans;
}
