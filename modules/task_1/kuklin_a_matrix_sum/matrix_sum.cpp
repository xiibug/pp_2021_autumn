//  Copyright 2021 Kuklin Andrey
#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_1/kuklin_a_matrix_sum/matrix_sum.h"

using std::vector;

vector<vector<int>> getRandMatrix(int sizei, int sizej) {
    vector<vector<int>> matrix(sizei);

    std::random_device device;
    std::mt19937 gen(device());
    for (int i = 0; i < sizei; i++) {
        matrix[i] = vector<int>(sizej);
        for (int j = 0; j < sizej; j++) {
            matrix[i][j] = gen() % 100;
        }
    }

    return matrix;
}

int matrixSumSequential(vector<int> vec) {
    int size = vec.size();
    int vec_sum = 0;
    for (int i = 0; i < size; i++) vec_sum += vec[i];

    return vec_sum;
}

int matrixSumParal(vector<vector<int>> mat, int sizei, int sizej) {
    int procNum, procRank;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    int delta = sizei / procNum;
    int size_of_tmp_vec = delta * sizej;
    vector<int> tmp_vec(size_of_tmp_vec);

    if (procRank == 0) {
        int k = 0;
        for (int proc = 1; proc < procNum; proc++) {
            for (int i = proc - 1; i < proc - 1 + delta; i++) {
                for (int j = 0; j < sizej; j++) {
                    tmp_vec[j + sizej * k] = mat[i][j];
                }
                k++;
            }
            k = 0;
            MPI_Send(tmp_vec.data(), size_of_tmp_vec, MPI_INT, proc, 0,
                    MPI_COMM_WORLD);
        }
    }

    vector<int> local_vec;
    if (procRank == 0) {
        local_vec.resize(size_of_tmp_vec + sizei % procNum * sizej);
        int k = 0;
        for (int i = delta * (procNum - 1); i < sizei; i++) {
            for (int j = 0; j < sizej; j++) {
                local_vec[j + sizej * k] = mat[i][j];
            }
            k++;
        }
    } else {
      local_vec.resize(size_of_tmp_vec);
      MPI_Status stat;
      MPI_Recv(local_vec.data(), size_of_tmp_vec, MPI_INT, 0, 0, MPI_COMM_WORLD,
               &stat);
    }

    int matrix_sum = 0;
    int local_matrix_sum = matrixSumSequential(local_vec);
    MPI_Reduce(&local_matrix_sum, &matrix_sum, 1, MPI_INT, MPI_SUM, 0,
             MPI_COMM_WORLD);

    return matrix_sum;
}
