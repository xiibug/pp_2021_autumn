// Copyright 2021 Lebedev Alexey
#include "../../../modules/task_3/lebedev_a_lsd_sort/lsd_sort.h"

#include <mpi.h>
#include <math.h>

#include <algorithm>
#include <cstring>
#include <string>


#define MIN_JOB 100

size_t get_max_digits(const std::vector<int>& v) {
    size_t max_digit = 0;
    for(const int& num: v) {
        size_t digit = (num < 0) ? std::to_string(num).size() - 1 : std::to_string(num).size();
        if (digit > max_digit) {
            max_digit = digit;
        }
    }
    return max_digit;
}

void lsd_sort(std::vector<int>& v) {
    const static size_t range = 19;
    std::vector<int> containers[range];
    size_t max_digits = get_max_digits(v);
    int ten_pow_dig = 1;
    for (size_t cur_dig = 0; cur_dig < max_digits; cur_dig++) {
        for (int& num: v) {
            containers[num / ten_pow_dig % 10 + 9].push_back(num);
        }
        ten_pow_dig *= 10;
        int* write_it = v.data();
        for (size_t i = 0; i < range; i++) {
            std::memcpy(write_it, containers[i].data(), containers[i].size() * sizeof(int));
            write_it += containers[i].size();
            containers[i].clear();
        }
    }
}

void lsd_sort_parallel(std::vector<int>& v) {
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        int max_size = (v.size() % MIN_JOB == 0) ? v.size() / MIN_JOB : v.size() / MIN_JOB + 1;
        size = std::min(size, max_size);
    }

    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Comm NEW_WORLD;
    int color = (rank < size) ? 0 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &NEW_WORLD);
    if (NEW_WORLD == MPI_COMM_NULL) {
        return;
    }

    std::vector<int> local_v{0};

    if (rank == 0) {
        int jobs_per_proc = v.size() / size;
        int last_jobs = v.size() % size;
        int local_size = (last_jobs == 0) ? jobs_per_proc : jobs_per_proc + 1;
        local_v.resize(local_size);
        int offset = local_size;
        for (int pid = 1; pid < size; pid++) {
            int count = (pid < last_jobs) ? jobs_per_proc + 1 : jobs_per_proc;
            MPI_Send(v.data() + offset, count, MPI_INT, pid, 0, NEW_WORLD);
            offset += count;
        }
    } else {
        int local_size;
        MPI_Status status;
        MPI_Probe(0, 0, NEW_WORLD, &status);
        MPI_Get_count(&status, MPI_FLOAT, &local_size);
        local_v.resize(local_size);
        MPI_Recv(local_v.data(), local_size, MPI_INT, 0, 0, NEW_WORLD, &status);
    }

    lsd_sort(local_v);

    if (rank == 0) {
        std::vector<int> tmp(v.size());
        std::memcpy(tmp.data(), local_v.data(), local_v.size() * sizeof(int));
        auto last_merged = tmp.begin() + local_v.size();
        for (int i = 1; i < size; i++) {
            int count;
            MPI_Status status;
            MPI_Probe(i, 0, NEW_WORLD, &status);
            MPI_Get_count(&status, MPI_FLOAT, &count);
            MPI_Recv(last_merged.base(), count, MPI_INT, i, 0, NEW_WORLD, &status);
            std::merge(tmp.begin(), last_merged, last_merged, last_merged + count, v.begin());
            tmp = v;
            last_merged += count;
        }
    } else {
        MPI_Send(local_v.data(), local_v.size(), MPI_INT, 0, 0, NEW_WORLD);
    }

    MPI_Comm_free(&NEW_WORLD);
}