// Copyright 2021 Brazhnik Dmitry

#include <mpi.h>
#include <iostream>
#include <random>
#include "../../../modules/task_1/brazhnik_d_vector_find_min/find_min_element_vector.h"
#include "find_min_element_vector.h"

std::vector<int> fillRandomValToVector(const int size) {
    if (size <= 0)
        throw "Error: The size cannot be negative!"; 

	std::vector<int> data(size);

	for (int i = 0; i < size; i++) {
		data[i] = -10000 + rand() % 100000;
	}
	return data;
}

int defaultFindingMinVal(const std::vector<int>& vector) {
	if (!vector.empty()) {
		int min = vector[0];
		for (int i = 1; i < vector.size(); i++) {
			if (min > vector[i])
				min = vector[i];
		}
		return min;
	}
	return 0;
}

int parallelFindingMinVal(const std::vector<int>& vector, const int size) {  
    int countProcess, rankProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &countProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProcess);

    int sizeBlock = size / countProcess;
    int elementsRemaining = size % countProcess;

    int resMinVal = 0;
    int localMinVal;

    if (rankProcess < elementsRemaining)
        sizeBlock++;

    std::vector<int> countSends;
    std::vector<int> tmp;
    std::vector<int> dataReceived(sizeBlock);

    if (rankProcess == 0) {
        countSends.assign(countProcess, vector.size() / countProcess);
        tmp.resize(countProcess);

        for (size_t i = 0; i < elementsRemaining; i++)
            countSends[i]++;
        for (size_t i = 0; i < countProcess - 1; i++)
            tmp[i + 1] = tmp[i] + countSends[i];
    }
    MPI_Scatterv(reinterpret_cast<const void*>(vector.data()), countSends.data(), tmp.data(),
        MPI_INT, dataReceived.data(), sizeBlock, MPI_INT, 0, MPI_COMM_WORLD);

    localMinVal = defaultFindingMinVal(dataReceived);

    MPI_Reduce(reinterpret_cast<void*>(&localMinVal), reinterpret_cast<void*>(&resMinVal),
        1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    return resMinVal;
}

