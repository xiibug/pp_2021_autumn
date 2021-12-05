// Copyright 2021 Kolesnikov Ilya
#include <mpi.h>
#include <iostream>
#include "../../../modules/task_1/kolesnikov_symbol_in_str/kolesnikov_symbol_in_str.h"

int parallel_find_symbol(char symbol, std::string str) {
    int size = 0, rank = 0, cnt_sym = 0, start = 0, range = 0, sum = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    range = str.size() / size;

    if (rank != 0) {
        start = rank * range;

        MPI_Status status;
        MPI_Recv(&sum, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }

    if (rank == size - 1) {
        range += str.size() % size;
    }

    range += start;

    for (int i(start); i < range; ++i) {
        if (symbol == str[i] || symbol - 32 == str[i]) {
            ++cnt_sym;
        }
    }
    sum += cnt_sym;
    if (rank != size - 1) {
        MPI_Send(&sum, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }
    return sum;
}

int single_find_symbol(char symbol, std::string str) {
    int cnt_sym = 0;
    int size = str.size();
    for (int i(0); i < size; ++i) {
        if (symbol == str[i] || symbol - 32 == str[i]) {
            ++cnt_sym;
        }
    }

    return cnt_sym;
}
