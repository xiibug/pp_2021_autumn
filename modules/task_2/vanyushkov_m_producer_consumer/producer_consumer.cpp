// Copyright 2021 Vanyushkov Maxim
#include "producer_consumer.h"
#include <stdio.h>
#include <stdlib.h>

void Consumer::RequestResource() {
    MPI_Send(&info, 3, MPI_INT, MANAGER, 0, MPI_COMM_WORLD);
}

void Consumer::RecieveResource() {
    int resource = 0;
    MPI_Status status;
    MPI_Recv(&resource, 1, MPI_INT, MANAGER, 3, MPI_COMM_WORLD, &status);
    if (resource == -1) {
        throw "Error";
    }
    if (resource != 0) {
        resources.push(resource);
        resources_to_consume--;
        // fprintf(stdout, "Consumer %d: i\'ve got resource %d\n", info.procRank, resources.back());
        // fflush(stdout);
    }
}

Consumer::Consumer(int in_rank, int in_resource_num) {
    resources_to_consume = in_resource_num;
    info.procRank = in_rank;
    info.whatDoYouNeed = GET_RESOURCE;
}

void Consumer::Run() {
    while (resources_to_consume) {
        RequestResource();
        RecieveResource();
    }
    info.whatDoYouNeed = EXITC;
    MPI_Send(&info, 3, MPI_INT, MANAGER, 0, MPI_COMM_WORLD);
}

bool Producer::SendResourceToManager() {
    info.res = resources.front();
    int answer;
    MPI_Send(&info, 3, MPI_INT, MANAGER, 0, MPI_COMM_WORLD);
    MPI_Recv(&answer, 1, MPI_INT, MANAGER, 1, MPI_COMM_WORLD, &status);
    if (answer == -1) {
        return false;
    }
    if (answer == 0) {
        // fprintf(stdout, "Producer %d: sending resource %d in buffer\n", info.procRank, info.res);
        // fflush(stdout);
        resources.pop();
    }
    // else {
    //     fprintf(stdout, "Producer %d: buffer is full. Failed to put the resource %d in buffer\n", info.procRank, info.res);
    //     fflush(stdout);
    // }
    return true;
}

void Producer::CreateResource() {
    int resource = k - resources_to_produce + (info.procRank - 1) * 5 + 1;
    resources.push(resource);
    resources_to_produce--;
}

Producer::Producer(int in_rank, int num) {
    info.procRank = in_rank;
    resources_to_produce = num;
    info.whatDoYouNeed = PUT_RESOURCE;
    k = resources_to_produce;
}

void Producer::Run() {
    bool flag = true;
    while (resources_to_produce && flag) {
        CreateResource();
        flag = SendResourceToManager();
    }
    while (!resources.empty() && flag) {
        flag = SendResourceToManager();
    }
    info.whatDoYouNeed = EXITP;
    MPI_Send(&info, 3, MPI_INT, MANAGER, 0, MPI_COMM_WORLD);
}

void Manager::Put(int producer_id, int resource) {
    int answer = 1;
    for (int i = 0; i < N; i++) {
        if (buffer[i] == 0) {
            answer = 0;
            buffer[i] = resource;
            break;
        }
    }
    if (answer == 0) {
        fprintf(stdout, "Manager: producer %d put resource %d\n", producer_id, resource);
        fflush(stdout);
    }
    MPI_Send(&answer, 1, MPI_INT, producer_id, 1, MPI_COMM_WORLD);
}

void Manager::Get(int consumer_id) {
    int resource = 0;
    for (int i = 0; i < N; i++) {
        if (buffer[i] != 0) {
            resource = buffer[i];
            buffer[i] = 0;
            break;
        }
    }
    if (resource == 0) {
        if (prod == 0) {
            Stop();
        }
    }
    else {
        fprintf(stdout, "Manager: consumer %d get resource %d\n", consumer_id, resource);
        fflush(stdout);
    }
    MPI_Send(&resource, 1, MPI_INT, consumer_id, 3, MPI_COMM_WORLD);
}

void Manager::Stop() {
    for (int i = 1; i < p_size; i++) {
        MPI_Send(&STOP, 1, MPI_INT, i, ((i % 2) ? 1 : 3), MPI_COMM_WORLD);
    }
}

Manager::Manager(int in_total_resources, int proc_size, int p, int c) {
    total_resources = in_total_resources;
    p_size = proc_size;
    N = total_resources;
    cons = c;
    prod = p;
    buffer = new int[total_resources];
    for (int i = 0; i < total_resources; i++) {
        buffer[i] = 0;
    }
}

void Manager::Run() {
    if (cons == 0) {
        Stop();
        return;
    }
    while (true) {
        MPI_Recv(&info, 3, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if (info.whatDoYouNeed == EXITP) {
            prod--;
        }
        if (info.whatDoYouNeed == EXITC) {
            cons--;
            if (cons == 0) {
                Stop();
                break;
            }
        }

        if (info.whatDoYouNeed == PUT_RESOURCE) {
            Put(info.procRank, info.res);
        }
        if (info.whatDoYouNeed == GET_RESOURCE) {
            Get(info.procRank);
        }
    }
}
