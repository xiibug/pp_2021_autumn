// Copyright 2021 Vanyushkov Maxim
#ifndef MODULES_TASK_2_VANYUSHKOV_M_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_
#define MODULES_TASK_2_VANYUSHKOV_M_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_

#include <queue>
#include <mpi.h>

#define MANAGER 0
#define PRODUCER 2 
#define CONSUMER 1

const int PUT_RESOURCE = 1;
const int GET_RESOURCE = 2;
const int EXITP = 3;
const int EXITC = 4;
const int STOP = -1;

struct info {
    int procRank;
    int whatDoYouNeed;
    int res;
};

class Consumer {
private:
    int resources_to_consume;
    std::queue<int> resources;
    info info;
    MPI_Status status;
private:
    void RequestResource();
    void RecieveResource();

public:
    Consumer(int in_rank, int in_resource_num = 5);
    void Run();
};

class Producer {
private:
    int resources_to_produce;
    std::queue<int> resources;
    MPI_Status status;
    info info;
    int k;

private:
    bool SendResourceToManager();
    void CreateResource();

public:
    Producer(int in_rank, int num = 5);
    void Run();
};

class Manager {
private:
    int total_resources;
    int* buffer;
    int N, p_size, prod, cons;
    MPI_Status status;
    info info;

private:
    void Put(int producer_id, int resource);
    void Get(int consumer_id);
    void Stop();

public:
    Manager(int in_total_resources, int proc_size, int p, int c);
    void Run();
};

#endif  // MODULES_TASK_2_VANYUSHKOV_M_PRODUCER_CONSUMER_PRODUCER_CONSUMER_H_
