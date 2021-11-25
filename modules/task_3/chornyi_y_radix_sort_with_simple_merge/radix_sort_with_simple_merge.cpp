// Copyright 2021 Chornyi Yurii
#include <mpi.h>
#include <random>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include "../../../modules/task_3/chornyi_y_radix_sort_with_simple_merge/radix_sort_with_simple_merge.h"

using std::vector;
using std::queue;
typedef vector<int>::size_type v_size_t;

v_size_t calculateMaximumRank(const vector<int>& vectorOfValue) {
    int maximumElement = *std::max_element(vectorOfValue.begin(), vectorOfValue.end());
    v_size_t rank = 0;

    while (maximumElement > 9) {
        maximumElement /= 10;
        ++rank;
    }

    return rank;
}
int calculateValueByRank(int value, v_size_t rank) {
    while (value && rank) {
        value /= 10;
        --rank;
    }
    value = value % 10;

    return value;
}
vector<int> simpleMerge(const vector<int>& firstVector, const vector<int>& secondVector) {
    vector<int> resultVector(firstVector.size() + secondVector.size());

    v_size_t firstIt, secondIt, resutIt;
    firstIt = secondIt = resutIt = 0;

    while (firstIt < firstVector.size() && secondIt < secondVector.size()) {
        if (firstVector[firstIt] < secondVector[secondIt]) {
            resultVector[resutIt++] = firstVector[firstIt++];
        }
        else {
            resultVector[resutIt++] = secondVector[secondIt++];
        }
    }

    while (firstIt < firstVector.size()) {
        resultVector[resutIt++] = firstVector[firstIt++];
    }
    while (secondIt < secondVector.size()) {
        resultVector[resutIt++] = secondVector[secondIt++];
    }

    return resultVector;
}

void generateRandomVector(vector<int>* vectorOfValue, v_size_t vectorSize) {
    std::random_device dev;
    std::mt19937 gen(dev());

    vectorOfValue->resize(vectorSize);
    for (v_size_t i = 0; i < vectorSize; ++i) {
        vectorOfValue->at(i) = gen() % 10000;
    }
}

void sequentialRadixSort(vector<int>* vectorOfValue) {
    v_size_t maximumRank = calculateMaximumRank(*vectorOfValue);

    // Pass through ranks from 0 to maximum rank
    for (v_size_t i = 0; i <= maximumRank; ++i) {
        vector<queue<int>> vectorOfQueue(10);  // Vector queue ranks 0...9

        // Distribution of vector elements by queues of the current rank
        for (auto it = vectorOfValue->begin(); it != vectorOfValue->end(); ++it) {
            vectorOfQueue[calculateValueByRank(*it, i)].push(*it);
        }

        // Permutation of vector elements by the current rank
        int currentQueue = 0;
        for (auto it = vectorOfValue->begin(); it != vectorOfValue->end(); ) {
            while (!vectorOfQueue.at(currentQueue).empty()) {
                *it = vectorOfQueue.at(currentQueue).front();
                vectorOfQueue.at(currentQueue).pop();
                ++it;
            }
            ++currentQueue;
        }
    }
}
vector<int> parallelRadixSort(const vector<int>& vectorOfValue, const v_size_t vectorSize) {
    int numberOfProcess, currentRank;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    int dataPackage = vectorSize / numberOfProcess;
    int dataExcess = vectorSize % numberOfProcess;
    vector<int> localVector, globalVector;

    localVector.resize(dataPackage);

    MPI_Scatter(vectorOfValue.data(), dataPackage, MPI_INT, localVector.data(),
                                      dataPackage, MPI_INT, 0, MPI_COMM_WORLD);
    sequentialRadixSort(&localVector);

    if (currentRank != 0) {
        MPI_Send(localVector.data(), dataPackage, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        globalVector = localVector;

        for (int i = 1; i < numberOfProcess; ++i) {
            MPI_Recv(localVector.data(), dataPackage, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            globalVector = simpleMerge(globalVector, localVector);
        }

        if (dataExcess) {
            localVector = vector<int>(vectorOfValue.end() - dataExcess, vectorOfValue.end());
            sequentialRadixSort(&localVector);
            globalVector = simpleMerge(globalVector, localVector);
        }
    }
    
    return globalVector;
}
