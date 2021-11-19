// Copyright 2021 Chelebaev Artem
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_1/chelebaev_a_symbol_frequency/symbol_frequency.h"




//--------------------------------------------------------------

double parFrequency(char* symbol, std::string text) {
    int my_rank, tasks, ccount = 0;    // variables for the rank of ongoing process,
                                       // number of processes and symbol count respectively

    double freq = 0;    // variable representing the frequency of a desired symbol
    const int N = text.length();    // length of the incoming string

    MPI_Status Status;
    MPI_Comm_size(MPI_COMM_WORLD, &tasks);    // stating the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);    // stating the rank of ongoing process

    if (N < tasks) {
        throw (-1);
    }

    if (N < tasks) {    // in case there is less data than the number of processes, we terminate the program
        throw "There is less data than the number of processes!";
    }
    int k = N / tasks;    // distribute the data between processes
    int i1 = k * my_rank;    // state the first index
    int i2 = k * (my_rank + 1);    // state second index
    int count = 0;    // number of symbol entries in the string

    if (my_rank == (tasks - 1)) {    // if current process is the last one, change the second index
                                    // so that the last process gets a bit more data than the others
        i2 = N;
    }
    for (int i = i1; i < i2; i++) {    // look for symbol entries
        if (text[i] == *symbol || text[i] == *symbol - 32)
            count++;
    }

    if (my_rank == 0) {    // if current process is the first one, receive data from the other processes
        ccount = count;
        for (int i = 1; i < tasks; i++) {
            MPI_Recv(&count, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &Status);
            ccount += count;
        }
    } else {    // else send the data to the first process
        MPI_Send(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (my_rank == 0) {    // if current process is the first one, compute the frequency
        freq = (static_cast<double>(ccount) / static_cast<double>(N)) * 100;
    }
    return freq;
}

double seqFrequency(char* symbol, std::string text) {
    int N = text.length();
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (text[i] == *symbol || text[i] == *symbol - 32) {
            count++;
        }
    }
    double freq = (static_cast<double>(count) / static_cast<double>(N)) * 100;
    return freq;
}

//-----------------------------------------------------------------


