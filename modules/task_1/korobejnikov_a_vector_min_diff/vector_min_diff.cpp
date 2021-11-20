#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "vector_min_diff.h"

std::pair<int, int> sequentialCount(std::vector<int> vec, int len) {
    int min = abs(vec[1] - vec[0]);
    int sum = vec[1] + vec[0];
    std::pair<int, int> p{vec[0], vec[1]};
    for (int i = 2; i < len; ++i) {
        if (abs(vec[i] - vec[i - 1]) < min) {
            min = abs(vec[i] - vec[i - 1]);
            sum = vec[i] + vec[i - 1];
            p = std::make_pair(vec[i - 1], vec[i]);
        }
        if (abs(vec[i] - vec[i - 1]) == min) {
            if (vec[i] + vec[i - 1] > sum){
                sum = vec[i] + vec[i - 1];
                p = std::make_pair(vec[i - 1], vec[i]);
            }
        }
    }
    return p;
}

std::vector<int> getRandomVector(int sz){
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

void my_func(std::pair<int, int> *a, std::pair<int, int> *b, int *len, MPI_Datatype *datatype){
    if (abs(a->first - a->second) < abs(b->first - b->second)){
        b = a;
    }
    if (abs(a->first - a->second) < abs(b->first - b->second)){
        if ((a->first + a->second) > (b->first + b->second)){
            b = a;
        }
    }
}

std::pair<int, int> parallelCount(std::vector<int> vec, int len) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int n = len / size;
    std::vector<int> local_vec(n);
    
    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            MPI_Send(vec.data() + proc * n, n,
        	    MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }
    
    if (rank == 0) {
        local_vec = std::vector<int>(vec.begin(), vec.begin()+n);
    }
    else {
        MPI_Status status;
        MPI_Recv(local_vec.data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
    
    std::pair<int, int> my_p = sequentialCount(local_vec, n);
    std::pair<int, int> global_p;
    MPI_Datatype ptype;
    MPI_Type_contiguous( 2, MPI_INT, &ptype );
    MPI_Type_commit( &ptype );
    MPI_Op myOp;
    MPI_Op_create((MPI_User_function *)my_func, 1, &myOp);
    MPI_Reduce(&my_p, &global_p, 1, ptype, myOp, 0, MPI_COMM_WORLD);
    
    return global_p;	
}
