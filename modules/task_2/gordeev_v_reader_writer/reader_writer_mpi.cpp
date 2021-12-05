// Copyright 2021 Gordeev Viktor
#include "./reader_writer_mpi.h"
#include <mpi.h>
#include <string>
#include <random>
#include <algorithm>
#include <chrono> // NOLINT [build/c++11]
#include <thread> // NOLINT [build/c++11]

void read() {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for(std::chrono::milliseconds(10 + gen() % 10));
}
void wait(int procn) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for
    (std::chrono::milliseconds(procn * (30 + gen() % 10)));
}

void write() {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::this_thread::sleep_for(std::chrono::milliseconds(10 + gen() % 10));
}

void reader(int rank) {
    int RC = 0;
    int inBuffer[1] = { 0 };
    int outBuffer[1] = { 0 };
    MPI_Status status;
    wait(rank);
    // printf(" TRying sending sreq from reader %d to proc 0\n", rank);
    // fflush(stdout);
    while (true) {
        MPI_Send(outBuffer, 1, MPI_INT, 0, SREQUEST, MPI_COMM_WORLD);
        MPI_Recv(inBuffer, 1, MPI_INT, 0, SRESPONSE,
            MPI_COMM_WORLD, &status);
        if (inBuffer[0] != -1)
            break;
        else
            wait(rank);
    }
    MPI_Send(outBuffer, 1, MPI_INT, 0, SRELEASE, MPI_COMM_WORLD);
    while (true) {
        MPI_Send(outBuffer, 1, MPI_INT, 0, RCREQUEST, MPI_COMM_WORLD);
        MPI_Recv(inBuffer, 1, MPI_INT, 0, RCRESPONSE,
            MPI_COMM_WORLD, &status);
        if (inBuffer[0] != -1)
            break;
        else
            wait(rank);
    }
    RC = inBuffer[0];
    RC++;
    if (RC == 1) {
        while (true) {
            MPI_Send(outBuffer, 1, MPI_INT, 0, ACCESSREQUEST, MPI_COMM_WORLD);
            MPI_Recv(inBuffer, 1, MPI_INT, 0, ACCESSRESPONSE,
                MPI_COMM_WORLD, &status);
            if (inBuffer[0] != -1)
                break;
            else
                wait(rank);
        }
    }
    outBuffer[0] = RC;
    MPI_Send(outBuffer, 1, MPI_INT, 0, RCRELEASE, MPI_COMM_WORLD);
    read();
    while (true) {
        MPI_Send(outBuffer, 1, MPI_INT, 0, RCREQUEST, MPI_COMM_WORLD);
        MPI_Recv(inBuffer, 1, MPI_INT, 0, RCRESPONSE,
            MPI_COMM_WORLD, &status);
        if (inBuffer[0] != -1)
            break;
        else
            wait(rank);
    }
    RC = inBuffer[0];
    RC--;
    if (RC == 0) {
        MPI_Send(outBuffer, 1, MPI_INT, 0, ACCESSRELEASE, MPI_COMM_WORLD);
    }
    outBuffer[0] = RC;
    MPI_Send(outBuffer, 1, MPI_INT, 0, RCRELEASE, MPI_COMM_WORLD);
    MPI_Send(outBuffer, 1, MPI_INT, 0, FINISH, MPI_COMM_WORLD);
    return;
}

void writer(int rank) {
    int inBuffer[1]= { 0 };
    int outBuffer[1] = { 0 };
    MPI_Status status;
    wait(rank);
     while (true) {
        MPI_Send(outBuffer, 1, MPI_INT, 0, SREQUEST, MPI_COMM_WORLD);
        MPI_Recv(inBuffer, 1, MPI_INT, 0, SRESPONSE,
            MPI_COMM_WORLD, &status);
        if (inBuffer[0] != -1)
            break;
        else
            wait(rank);
    }
    while (true) {
        MPI_Send(outBuffer, 1, MPI_INT, 0, ACCESSREQUEST, MPI_COMM_WORLD);
        MPI_Recv(inBuffer, 1, MPI_INT, 0, ACCESSRESPONSE,
            MPI_COMM_WORLD, &status);
        if (inBuffer[0] != -1)
            break;
        else
            wait(rank);
    }
    MPI_Send(outBuffer, 1, MPI_INT, 0, SRELEASE, MPI_COMM_WORLD);
    write();
    MPI_Send(outBuffer, 1, MPI_INT, 0, ACCESSRELEASE, MPI_COMM_WORLD);
    MPI_Send(outBuffer, 1, MPI_INT, 0, FINISH, MPI_COMM_WORLD);
    return;
}
// Interaction of readers and writers
void library(int rank, int procs) {
    int inBuffer[1] = { 0 };
    int outBuffer[1] = { 0 };
    int RWnumber;
    MPI_Status status;
    // managing access to the Read Count variable - critical data
    bool RC = true;
    // Controls access to the data of the writer or the first reader
    bool Access = true;
    // Number of active readers
    int ReadCount = 0;
    // Semaphore to prevent starvation of writers and readers
    bool S = true;
    int* runs = new int[procs - 1];
    for (int i = 0; i < procs - 1; i++) {
        runs[i] = 0;
    }
    while (true) {
        if (procs != 1) {
            MPI_Recv(inBuffer, 1, MPI_INT, MPI_ANY_SOURCE,
                MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        } else {
            return;
        }
        RWnumber = status.MPI_SOURCE;
        if (status.MPI_TAG == SREQUEST) {
            if (S == true) {
                S = false;
                // printf(" TRying sending to reader % d\n", RWnumber);
                // fflush(stdout);
                outBuffer[0] = 1;
                MPI_Send(outBuffer, 1, MPI_INT, RWnumber,
                    SRESPONSE, MPI_COMM_WORLD);
            } else {
                // printf("Reader %d cant access SREQUEST\n", RWnumber);
                // fflush(stdout);
                outBuffer[0] = -1;
                MPI_Send(outBuffer, 1, MPI_INT, RWnumber,
                    SRESPONSE, MPI_COMM_WORLD);
            }
        }
       if (status.MPI_TAG == SRELEASE) {
            if (S == false) {
                S = true;
            }
        }
        if (status.MPI_TAG == RCREQUEST) {
            // printf("READ COUNT NUMBER %d\n", ReadCount);
            // fflush(stdout);
            if (RC == true) {
                RC = false;
                outBuffer[0] = ReadCount;
                MPI_Send(outBuffer, 1, MPI_INT, RWnumber,
                    RCRESPONSE, MPI_COMM_WORLD);
            } else {
               // printf("READ COUNT NUMBER %d\n", ReadCount);
                // printf("Reader %d cant access RCREQUEST\n", RWnumber);
                // fflush(stdout);
                outBuffer[0] = -1;
                MPI_Send(outBuffer, 1, MPI_INT, RWnumber,
                    RCRESPONSE, MPI_COMM_WORLD);
            }
        }
        if (status.MPI_TAG == RCRELEASE) {
            // printf("READ COUNT NUMBER %d\n", ReadCount);
            // fflush(stdout);
            if (RC == false) {
                RC = true;
                ReadCount = inBuffer[0];
            }
        }
        if (status.MPI_TAG == ACCESSREQUEST) {
            if (Access == true) {
                Access = false;
                outBuffer[0] = 1;
                MPI_Send(outBuffer, 1, MPI_INT, RWnumber,
                    ACCESSRESPONSE, MPI_COMM_WORLD);
            } else {
                // printf("Reader %d cant access ACCESSREQUEST\n", RWnumber);
                // fflush(stdout);
                outBuffer[0] = -1;
                MPI_Send(outBuffer, 1, MPI_INT, RWnumber,
                    ACCESSRESPONSE, MPI_COMM_WORLD);
            }
        }
        if (status.MPI_TAG == ACCESSRELEASE) {
            if (Access == false) {
                Access = true;
            }
        }
        if (status.MPI_TAG == FINISH) {
          //  printf("RW %d cant access FINISH\n", RWnumber);
          // fflush(stdout);
            runs[RWnumber - 1] += 1;
        }
       int runsCnt = 0;
       for (int i = 0; i < procs - 1; i++) {
            // printf("RW number %d - %d\n", i + 1, runs[i]);
            // fflush(stdout);
            runsCnt += runs[i];
       }
       read();
       if (runsCnt == procs-1) {
          // printf("Break\n");
          // fflush(stdout);
           break;
       }
    }
    return;
}
