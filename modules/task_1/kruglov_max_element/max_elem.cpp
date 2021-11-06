// Copyright 2021 Kruglov Aleksei
#include "../../../modules/task_1/kruglov_max_element/max_elem.h"
#include <mpi.h>
#include <random>
#include <algorithm>
#include <iostream>
#include <climits>

std::vector<int> get_random_vector(std::size_t size, int max_possible) {
    std::random_device device;
    std::mt19937 gen(device());
    std::vector<int> vec(size);
    for (std::size_t i = 0; i < vec.size(); i++)
        vec[i] = gen() % max_possible;
    return vec;
}

int get_max_element(const std::vector<int>& vec, std::size_t size) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    int cur_elems_count = size / proc_num;
    int above_average = size % proc_num;

    if (proc_rank < above_average)
        cur_elems_count++;

    std::vector<int> count_sends;
    std::vector<int> offset;
    std::vector<int> receive_data(cur_elems_count);

    if (proc_rank == 0) {
        auto elemsPerProc = vec.size() / proc_num;
        count_sends.assign(proc_num, elemsPerProc);
        offset.resize(proc_num);

        for (int i = 0; i < above_average; i++)
            count_sends[i]++;
        for (int i = 1; i < proc_num; i++)
            offset[i] = offset[i - 1] + count_sends[i - 1];
    }
    MPI_Scatterv(reinterpret_cast<const void*>(vec.data()), count_sends.data(), offset.data(),
                 MPI_INT, receive_data.data(), cur_elems_count, MPI_INT, 0, MPI_COMM_WORLD);

    int global_max = INT_MIN;
    int local_max = INT_MIN;

    // situation when proc_num > input size
    if (!receive_data.empty())
        local_max = *std::max_element(receive_data.begin(), receive_data.end());
    MPI_Reduce(reinterpret_cast<void*>(&local_max), reinterpret_cast<void*>(&global_max), 1, MPI_INT,
               MPI_MAX, 0, MPI_COMM_WORLD);

    return global_max;
}
