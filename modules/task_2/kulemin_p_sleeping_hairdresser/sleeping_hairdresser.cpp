// Copyright 2021 Shelepin Nikita
#include "../../../modules/task_2/kulemin_p_sleeping_hairdresser/sleeping_hairdresser.h"
#include <mpi.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include <chrono> // NOLINT [build/c++11]
#include <thread> // NOLINT [build/c++11]
#include <sstream>
#include <iostream>
void wait() {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for(std::chrono::milliseconds(10 + gen() % 10));
}
void cut_hair() {
    wait();
}
void customer(int myrank, int total_runs) {
    int in_buffer[1];
    MPI_Status status;
    srand(time(NULL) + myrank);

    int runs = 0;

    while (runs < total_runs) {
       wait();
        MPI_Send(&myrank, 1, MPI_INT, 0, CHAIR_REQUEST, MPI_COMM_WORLD);
        MPI_Recv(in_buffer, 1, MPI_INT, 0, CHAIR_RESPONSE,
          MPI_COMM_WORLD, &status);
        if (in_buffer[0] >= 0) {
            MPI_Send(&runs, 1, MPI_INT, 0, HAIR_CUT_REQUEST, MPI_COMM_WORLD);
        }
        runs += 1;
    }
    return;
}

void barber(int myrank, int chairs_count, int total_runs) {
    int in_buffer[1];
    int out_buffer[1];
    int un_free_chairs = 0;
    int count = 1;
    MPI_Status status;
    for (int i = 0; i < total_runs; i++) {
        MPI_Recv(in_buffer, 1, MPI_INT, MPI_ANY_SOURCE,
        CHAIR_REQUEST, MPI_COMM_WORLD, &status);
        if (un_free_chairs < chairs_count) {
            out_buffer[0] = un_free_chairs;
            MPI_Send(out_buffer, 1, MPI_INT,
            in_buffer[0], CHAIR_RESPONSE, MPI_COMM_WORLD);
            un_free_chairs++;
        } else {
            out_buffer[0] = -1;
           MPI_Send(out_buffer, 1, MPI_INT, in_buffer[0],
           CHAIR_RESPONSE, MPI_COMM_WORLD);
        }
        for (int i = 0; i < un_free_chairs; i++) {
            cut_hair();
            MPI_Recv(in_buffer, 1, MPI_INT, MPI_ANY_SOURCE,
            HAIR_CUT_REQUEST, MPI_COMM_WORLD, &status);
        }
        un_free_chairs = 0;
    }
  return;
}
