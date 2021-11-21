// Copyright 2021 Trevogin Kirill

#include "../../../modules/task_1/trevogin_k_finde_vec/finde_vec.h"

std::vector<int> getRandomVector(int size) {
    std::random_device rn;
    std::mt19937 gen(rn());
    std::uniform_int_distribution<> dist(1, 10);
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}

int getFindeOrderedElements(std::vector<int> vec) {
    int count = 0;
    if (vec.size() == 0)
        return 0;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i - 1] <= vec[i])
            count++;
    }
    return count;
}

int getFindeOrderedElementsParall(std::vector<int> vec, int size_vec) {
    int Size, Rank, end, start;
    int count = 0, count1 = 0;
    std::vector<int> vec1(size_vec);
    MPI_Comm_size(MPI_COMM_WORLD, &Size);
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    int rad = size_vec / Size;
    start = (Rank * rad) + 1;
    if (size_vec == 0)
        return 0;
    if (Rank < Size - 1) {
        end = start + rad;
    } else
        end = size_vec;
    if (Rank == 0) {
        for (int i = 1; i < Size; i++)
            MPI_Send(vec.data(), size_vec, MPI_INT, i, 0, MPI_COMM_WORLD);
        vec1 = vec;
    } else {
        MPI_Status status;
        MPI_Recv(vec1.data(), size_vec, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
    for (int i = start; i < end; i++)
        if (vec1[i - 1] <= vec1[i])
            count1++;
    MPI_Reduce(&count1, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return count;
}
