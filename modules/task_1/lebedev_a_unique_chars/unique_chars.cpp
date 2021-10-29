#include <algorithm>
#include <random>
#include <memory>
#include <cstring>
#include <iostream>
#include <mpi.h>
#include "unique_chars.h"

std::string getRandomString(size_t size) {
    std::string random_str;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(97, 122);

    for(size_t i = 0; i < size; i++) {
        random_str.push_back(distrib(gen));
    }
    return random_str;
}

int CountUnique(const std::string& str, size_t pos, size_t substr_size, const std::string& compare_str) {
    int result = 0;
    for(size_t i = pos; i < pos + substr_size; i++) {
        if(compare_str.find(str[i]) == std::string::npos) {
            if(str.find_first_of(str[i]) == i){
                result ++;
            }
        }
    }
    return result;
}

int UniqueCharsSequential(const std::string& str1, const std::string& str2) {
    return CountUnique(str1, 0, str1.size(), str2) + CountUnique(str2, 0, str2.size(), str1);
}

void DistributeJobs(int local_rank, int jobs, int total_size, int& pos, int& substr_size) {
    substr_size = total_size / jobs;
    int first_step = (total_size % jobs == 0) ? substr_size : substr_size + 1;
    if (local_rank == 0) {
        pos = 0;
        substr_size = first_step;
    } else {
        pos = first_step + (local_rank - 1) * substr_size;
    }
}

int UniqueCharsParallel(const std::string& str1, const std::string& str2) {
    int global_size, global_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &global_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);

    MPI_Comm local_comm;
    MPI_Comm_split(MPI_COMM_WORLD, global_rank % 2, global_rank, &local_comm);

    int local_size, local_rank;
    MPI_Comm_size(local_comm, &local_size);
    MPI_Comm_rank(local_comm, &local_rank);

    std::string str1_local, str2_local;

    if (global_rank != 0 && local_rank == 0) {
        MPI_Send(&global_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (global_rank == 0) {
        str1_local = str1;
        str2_local = str2;
        if (global_size > 1) {
            int dst_pid;
            MPI_Status status;
            MPI_Recv(&dst_pid, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

            MPI_Send(str2.c_str(), str2.size(), MPI_CHAR, dst_pid, 1, MPI_COMM_WORLD);
            MPI_Send(str1.c_str(), str1.size(), MPI_CHAR, dst_pid, 2, MPI_COMM_WORLD);
        }
    }
    else if (local_rank == 0) {
        MPI_Status status;
        int str_size;

        MPI_Probe(0, 1, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &str_size);
        str1_local.resize(str_size);
        MPI_Recv(&str1_local[0], str_size, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        MPI_Probe(0, 2, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &str_size);
        str2_local.resize(str_size);
        MPI_Recv(&str2_local[0], str_size, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
    }

    int str1_size, str2_size;
    if (local_rank == 0) {
        str1_size = str1_local.size();
        str2_size = str2_local.size();
    }

    MPI_Bcast(&str1_size, 1, MPI_INT, 0, local_comm);
    MPI_Bcast(&str2_size, 1, MPI_INT, 0, local_comm);

    str1_local.resize(str1_size);
    str2_local.resize(str2_size);

    MPI_Bcast(&str1_local[0], str1_size, MPI_CHAR, 0, local_comm);
    MPI_Bcast(&str2_local[0], str2_size, MPI_CHAR, 0, local_comm);

    int pos, substr_size;
    DistributeJobs(local_rank, local_size, str1_size, pos, substr_size);
    int local_count = CountUnique(str1_local, pos, substr_size, str2_local);

    if(global_size == 1) {
        DistributeJobs(local_rank, local_size, str2_size, pos, substr_size);
        local_count += CountUnique(str2_local, pos, substr_size, str1_local);
    }

    int global_count = 0;
    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return global_count;
}
