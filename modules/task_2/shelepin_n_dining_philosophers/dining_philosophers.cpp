// Copyright 2021 Shelepin Nikita
#include "../../../modules/task_2/shelepin_n_dining_philosophers/dining_philosophers.h"
#include <mpi.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include <chrono> // NOLINT [build/c++11]
#include <thread> // NOLINT [build/c++11]

int left(int p, int s) {
    if (p - 1 == 0) {
        return s;
    } else {
        return p - 1;
    }
}

int right(int p, int s) {
    if (p + 1 == s + 1) {
        return 1;
    } else {
        return p + 1;
    }
}

void think() {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for(std::chrono::milliseconds(10 + gen() % 10));
}

void eat() {
    think();
}

void philosopher(int myrank, int total_runs) {
    int in_buffer[1];
    int out_buffer[1] = { 0 };
    MPI_Status status;
    srand(time(NULL) + myrank);

    int runs = 0;

    while (runs < total_runs) {
        think();
        MPI_Send(out_buffer, 1, MPI_INT, 0, FORK_REQUEST, MPI_COMM_WORLD);
        MPI_Recv(in_buffer, 1, MPI_INT, 0, FORK_RESPONSE,
            MPI_COMM_WORLD, &status);
        eat();
        MPI_Send(out_buffer, 1, MPI_INT, 0, FORK_RELEASE, MPI_COMM_WORLD);
        runs += 1;
    }
    return;
}

void table(int myrank, int nprocs, int total_runs) {
    int in_buffer[1];
    int out_buffer[1];
    int philosopher;
    MPI_Status status;

    int* runs = new int[nprocs - 1];
    for (int i = 0; i < nprocs - 1; i++) {
        runs[i] = 0;
    }

    int* state = new int[nprocs - 1];
    for (int i = 0; i < nprocs - 1; i++) {
        state[i] = THINKING;
    }

    while (1) {
        if (nprocs != 1) {
            MPI_Recv(in_buffer, 1, MPI_INT, MPI_ANY_SOURCE,
                MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        } else {
            // printf("No philosophers!\n");
            return;
        }
        philosopher = status.MPI_SOURCE;

        if (status.MPI_TAG == FORK_REQUEST) {
            state[philosopher] = HUNGRY;
            // printf("Philosopher %d is hungry\n", philosopher);
            // fflush(stdout);
            if (state[left(philosopher, nprocs - 1)] != EATING
                && state[right(philosopher, nprocs - 1)] != EATING) {
                state[philosopher] = EATING;
                // printf("Philosopher %d is eating\n", philosopher);
                // fflush(stdout);
                MPI_Send(out_buffer, 1, MPI_REAL, philosopher,
                    FORK_RESPONSE, MPI_COMM_WORLD);
            }
        }

        if (status.MPI_TAG == FORK_RELEASE) {
            state[philosopher] = THINKING;
            // printf("Philosopher %d has finished eating\n", philosopher);
            runs[philosopher - 1] += 1;
            // fflush(stdout);
            if (state[left(philosopher, nprocs - 1)] == HUNGRY &&
                state[left(left(philosopher, nprocs - 1), nprocs - 1)]
                != EATING &&
                state[right(left(philosopher, nprocs - 1), nprocs - 1)]
                != EATING) {
                state[left(philosopher, nprocs - 1)] = EATING;
                MPI_Send(out_buffer, 1, MPI_REAL,
                    left(philosopher, nprocs - 1),
                    FORK_RESPONSE, MPI_COMM_WORLD);
            }
            if (state[right(philosopher, nprocs - 1)] == HUNGRY &&
                state[left(right(philosopher, nprocs - 1), nprocs - 1)]
                != EATING &&
                state[right(right(philosopher, nprocs - 1), nprocs - 1)]
                != EATING) {
                state[right(philosopher, nprocs - 1)] = EATING;
                MPI_Send(out_buffer, 1, MPI_REAL,
                    right(philosopher, nprocs - 1),
                    FORK_RESPONSE, MPI_COMM_WORLD);
            }
        }

        int runs_num = 0;
        for (int i = 0; i < nprocs - 1; i++) {
            // printf("Philosopher no. %d - %d\n", i + 1, runs[i]);
            // fflush(stdout);
            runs_num += runs[i];
        }
        if (runs_num == total_runs * (nprocs - 1)) { break; }
    }
    fflush(stdout);
    return;
}
