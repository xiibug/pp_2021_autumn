// Copyright 2021 Shurygina Anna
#include <mpi.h>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <random>
#include <iostream>
#include "../../../modules/task_2/shurygina_a_linear_topology/linear_topology.h"

// MPI_GRAPH_CREATE(comm_old, nnodes, degree, edges, reorder, comm_graph),
// comm_old - input communicator without topology(handle)
// nnodes - number of nodes in graph(integer)
// degree - array of integers describing node degrees
// edges - array of integers describing graph edges
// reorder - ranking may be reordered(true) or not (false) (logical)

MPI_Comm createGraphComm(MPI_Comm comm) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm graphcomm;

    // find degree of graph vertices
    // degree[0] - defree of 0 vertex
    // (degree[i] - degree[i-1]) - degree of  i vertex
    int* degree = new int[size];
    int* edges = new int[2 * (size - 1)];
    degree[0] = 1;
    for (int i = 1; i < size - 1; i++) {
        degree[i] = degree[i - 1] + 2;
    }
    degree[size - 1] = degree[size - 2] + 1;
    
    // find edges
    // edges[0] - neghbors of 0 vertex
    // edges[j] - neghbors of i vertex (where degree[i-1]<=j<=degree[i]-1)
    int tmp = 1;
    edges[0] = 1;
    for (int i = 1; i < 2 * (size - 1) - 1; i = i + 2) {
        edges[i] = tmp - 1;
        edges[i + 1] = tmp + 1;
        tmp++;
    }
    edges[2 * (size - 1) - 1] = size - 2;

    // create graph
    MPI_Graph_create(MPI_COMM_WORLD, size, degree, edges, 0, &graphcomm);

    return graphcomm;
}

// int* sendData(int* buf, int count, MPI_Datatype type, int dest,int tag,
//    MPI_Comm comm, int source, int ProcRank)
// buf - memmory buffer
// count - send data size 
// type - data type
// dest - process we send data
// comm - communicator
// source - process which send data
// procRank - calling process
int* sendData(int* buf, int count, MPI_Datatype type, int dest, int tag,
                        MPI_Comm comm, int source, int procRank) {
    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    int* neighbors = new int[2];

    if ((procRank == 0) || (procRank == size - 1)) {
        // Returns the neighbors of a node associated with a graph topology
        MPI_Graph_neighbors(comm, procRank, 1, neighbors);
    } else {
        MPI_Graph_neighbors(comm, procRank, 2, neighbors);
    }

    int* local_buf = new int[count];

    if (procRank == source) {
        for (int i = 0; i < count; i++) {
            local_buf[i] = buf[i];
        }
    }

    if (source < dest) {
        for (int proc = source; proc < dest; proc++) {
            if (procRank == proc) {
                if (procRank == 0) {
                    MPI_Send(&local_buf[0], count, type, neighbors[0], 0, comm);
                } else {
                    MPI_Send(&local_buf[0], count, type, neighbors[1], 0, comm);
                }
            } else if (procRank == proc + 1) {
                    MPI_Recv(&local_buf[0], count, type, neighbors[0], 0, comm, &status);
            }
            MPI_Barrier(comm);
        }
    }

    if (source > dest) {
        for (int proc = source; proc > dest; proc--) {
            if (procRank == proc) {
                    MPI_Send(&local_buf[0], count, type, neighbors[0], 0, comm);
            } else if (procRank == proc - 1) {
                if (procRank == 0) {
                    MPI_Recv(&local_buf[0], count, type, neighbors[0], 0, comm, &status);
                } else {
                    MPI_Recv(&local_buf[0], count, type, neighbors[1], 0, comm, &status);
                }
            }
            MPI_Barrier(comm);
        }
    }
    return local_buf;
}

int* getRandomSequence(int size) {
    std::mt19937 random_generator;
    random_generator.seed(static_cast<unsigned int>(time(0)));
    int* vec = new int[size];
    for (int i = 0; i < size; i++) {
        vec[i] = random_generator() % 100;
    }
    return vec;
}
