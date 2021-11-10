// Copyright 2021 Zarubin Mikhail
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_2/zarubin_m_bubble_sort_even_odd_algorithm/bubble_sort_even_odd_algorithm.h"


void generateRandomVector(std::vector<int>* vector,
    std::vector<int>::size_type size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    for (std::vector<int>::size_type i = 0; i < size; i++) {
        (*vector)[i] = gen() % 100;
    }
}

void getSequentialOperations(std::vector<int>::iterator begin,
    std::vector<int>::iterator end) {
    if (end - begin < 2)
        return;

    int stop_flag{ 0 }, current_iter{ 0 }, swap_flag{ 0 };
    std::vector<int>::size_type start_value{ 0 };

    while (stop_flag != 2) {
        if (current_iter % 2) {
            stop_flag = 0;
            start_value = 0;
        } else {
            start_value = 1;
        }

        swap_flag = 0;
        for (auto iterator = begin + start_value; iterator + 1 < end; ++iterator) {
            if (*iterator > *(iterator + 1)) {
                std::swap(*iterator, *(iterator + 1));
                swap_flag = 1;
            }
        }

        if (swap_flag == 0)
            ++stop_flag;

        ++current_iter;
    }
}

std::vector<int>::size_type calculate_begin(int rank,
    std::vector<int>::size_type local_size,
    std::vector<int>::size_type remains) {
    return rank == 0 ? 0 : local_size * rank + remains;
}

std::vector<int>::size_type calculate_end(int rank,
    std::vector<int>::size_type local_size,
    std::vector<int>::size_type remains) {
    return rank == 0 ? local_size + remains : calculate_begin(rank, local_size, remains) + local_size;
}

std::vector<int> getParallelOperations(const std::vector<int>& global_vector,
    std::vector<int>::size_type global_size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int>::size_type local_size = global_size / size;
    std::vector<int>::size_type remains_size = global_size % size;

    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            std::vector<int>::size_type step = proc * local_size;
            if (remains_size != 0) {
                step += remains_size;
            }
            MPI_Send(global_vector.data() + step, static_cast<int>(local_size),
                MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }

    std::vector<int> local_vector(global_size, 0);
    std::vector<int>::size_type local_begin = calculate_begin(rank, local_size, remains_size);
    std::vector<int>::size_type local_end = calculate_end(rank, local_size, remains_size);

    if (rank == 0) {
        for (std::vector<int>::size_type i = 0; i < local_size + remains_size; i++) {
            local_vector[i] = global_vector[i];
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_vector.data() + local_begin, static_cast<int>(local_size),
            MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    getSequentialOperations(local_vector.begin() + local_begin, local_vector.begin() + local_end);

    std::vector<int> result(global_size, 0);
    MPI_Allreduce(local_vector.data(), result.data(), static_cast<int>(global_size),
        MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    std::vector<int>::size_type sort_size = local_size;
    int required_rank = size / 2;

    if (size % 2 != 0)
        remains_size += local_size;

    while (sort_size + remains_size != global_size && rank < required_rank) {
        local_size *= 2;

        std::vector<int>::size_type sort_begin = calculate_begin(rank, local_size, remains_size);
        std::vector<int>::size_type sort_end = calculate_end(rank, local_size, remains_size);

        getSequentialOperations(result.begin() + sort_begin, result.begin() + sort_end);

        if (required_rank % 2 != 0)
            remains_size += local_size;

        sort_size *= 2;
        required_rank /= 2;
    }

    return result;
}
