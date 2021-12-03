// Copyright 2021 Zharkov Andrey
#include "./reader-writer_mpi.h"
#include <mpi.h>
#include <chrono> // NOLINT [build/c++11]
#include <thread> // NOLINT [build/c++11]
#include <string>
#include <algorithm>
#include <random>

void reader(int rank) {
    int RC = 0;
    int get_buf[1] = { 0 };
    int set_buf[1] = { 0 };
    MPI_Status status;
    wait(rank);
    while (true) {
        MPI_Send(set_buf, 1, MPI_INT, 0, S_Request, MPI_COMM_WORLD);
        MPI_Recv(get_buf, 1, MPI_INT, 0, S_Response,
            MPI_COMM_WORLD, &status);
        if (get_buf[0] != -1)
            break;
        else
            wait(rank);
    }
    MPI_Send(set_buf, 1, MPI_INT, 0, S_Release, MPI_COMM_WORLD);
    while (true) {
        MPI_Send(set_buf, 1, MPI_INT, 0, RC_Request, MPI_COMM_WORLD);
        MPI_Recv(get_buf, 1, MPI_INT, 0, RC_Response,
            MPI_COMM_WORLD, &status);
        if (get_buf[0] != -1)
            break;
        else
            wait(rank);
    }
    RC = get_buf[0];
    RC++;
    if (RC == 1) {
        while (true) {
            MPI_Send(set_buf, 1, MPI_INT, 0, Access_Request, MPI_COMM_WORLD);
            MPI_Recv(get_buf, 1, MPI_INT, 0, Access_Response,
                MPI_COMM_WORLD, &status);
            if (get_buf[0] != -1)
                break;
            else
                wait(rank);
        }
    }
    set_buf[0] = RC;
    MPI_Send(set_buf, 1, MPI_INT, 0, RC_Release, MPI_COMM_WORLD);
    read_oper();
    while (true) {
        MPI_Send(set_buf, 1, MPI_INT, 0, RC_Request, MPI_COMM_WORLD);
        MPI_Recv(get_buf, 1, MPI_INT, 0, RC_Response,
            MPI_COMM_WORLD, &status);
        if (get_buf[0] != -1)
            break;
        else
            wait(rank);
    }
    RC = get_buf[0];
    RC--;
    if (RC == 0) {
        MPI_Send(set_buf, 1, MPI_INT, 0, Access_Release, MPI_COMM_WORLD);
    }
    set_buf[0] = RC;
    MPI_Send(set_buf, 1, MPI_INT, 0, RC_Release, MPI_COMM_WORLD);
    MPI_Send(set_buf, 1, MPI_INT, 0, Finish, MPI_COMM_WORLD);
    return;
}

void writer(int rank) {
    int get_buf[1]= { 0 };
    int set_buf[1] = { 0 };
    MPI_Status status;
    wait(rank);
     while (true) {
        MPI_Send(set_buf, 1, MPI_INT, 0, S_Request, MPI_COMM_WORLD);
        MPI_Recv(get_buf, 1, MPI_INT, 0, S_Response,
            MPI_COMM_WORLD, &status);
        if (get_buf[0] != -1)
            break;
        else
            wait(rank);
    }
    while (true) {
        MPI_Send(set_buf, 1, MPI_INT, 0, Access_Request, MPI_COMM_WORLD);
        MPI_Recv(get_buf, 1, MPI_INT, 0, Access_Response,
            MPI_COMM_WORLD, &status);
        if (get_buf[0] != -1)
            break;
        else
            wait(rank);
    }
    MPI_Send(set_buf, 1, MPI_INT, 0, S_Release, MPI_COMM_WORLD);
    write_oper();
    MPI_Send(set_buf, 1, MPI_INT, 0, Access_Release, MPI_COMM_WORLD);
    MPI_Send(set_buf, 1, MPI_INT, 0, Finish, MPI_COMM_WORLD);
    return;
}

void work(int rank, int proc) {
    int get_buf[1] = { 0 };
    int set_buf[1] = { 0 };

    // activ proc
    int Activ_proc;
    // access control to ReadCount
    bool RC = true;
    // access control to data
    bool Access = true;
    // num activ of R
    int activeReaders = 0;
    // semaphore to prevent hunger R and W
    bool S = true;

    int* runs = new int[proc - 1];
    MPI_Status status;

    for (int i = 0; i < proc - 1; i++) {
        runs[i] = 0;
    }
    while (true) {
        if (proc != 1) {
            MPI_Recv(get_buf, 1, MPI_INT, MPI_ANY_SOURCE,
                MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        } else {
            return;
        }
        Activ_proc = status.MPI_SOURCE;
        if (status.MPI_TAG == S_Request) {
            if (S == true) {
                S = false;
                set_buf[0] = 1;
                MPI_Send(set_buf, 1, MPI_INT, Activ_proc,
                    S_Response, MPI_COMM_WORLD);
            } else {
                set_buf[0] = -1;
                MPI_Send(set_buf, 1, MPI_INT, Activ_proc,
                    S_Response, MPI_COMM_WORLD);
            }
        }
        if (status.MPI_TAG == S_Release) {
            if (S == false) {
                S = true;
            }
        }
        if (status.MPI_TAG == Access_Request) {
            if (Access == true) {
                Access = false;
                set_buf[0] = 1;
                MPI_Send(set_buf, 1, MPI_INT, Activ_proc,
                    Access_Response, MPI_COMM_WORLD);
            } else {
                set_buf[0] = -1;
                MPI_Send(set_buf, 1, MPI_INT, Activ_proc,
                    Access_Response, MPI_COMM_WORLD);
            }
        }
        if (status.MPI_TAG == Access_Release) {
            if (Access == false) {
                Access = true;
            }
        }
        if (status.MPI_TAG == RC_Request) {
            if (RC == true) {
                RC = false;
                set_buf[0] = activeReaders;
                MPI_Send(set_buf, 1, MPI_INT, Activ_proc,
                    RC_Response, MPI_COMM_WORLD);
            }
            else {
                set_buf[0] = -1;
                MPI_Send(set_buf, 1, MPI_INT, Activ_proc,
                    RC_Response, MPI_COMM_WORLD);
            }
        }
        if (status.MPI_TAG == RC_Release) {
            if (RC == false) {
                RC = true;
                activeReaders = get_buf[0];
            }
        }
        if (status.MPI_TAG == Finish) {
            runs[Activ_proc - 1] += 1;
        }
        int used = 0;
        for (int i = 0; i < proc - 1; i++) {
           // used proc
           used += runs[i];
        }
        read_oper();
        if (used == proc - 1) {
            break;
        }
    }
    return;
}

void read_oper() {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for(std::chrono::milliseconds(gen() % 20));
}

void write_oper() {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for(std::chrono::milliseconds(gen() % 20));
}

void wait(int proc) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for
    (std::chrono::milliseconds(proc * (30 + gen() % 20)));
}
