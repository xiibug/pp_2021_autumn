// Copyright 2021 Lakhov Kirill

#include <vector>
#include <cstdlib>
#include "../../../modules/task_1/lakhov_k_matrix_col_sum/matrix_col_sum.h"

std::vector<int> getRandomVector(int sz) {
    int min = -100;
    int max = 100;
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    std::vector<int> vec(sz);
    for (int  i = 0; i < sz; i++) { vec[i] = distribution(engine); }
    return vec;
}

std::vector<std::vector<int>> getRandomMatrix(int rows, int cols) {
    std::vector<std::vector<int>> vec(rows);
    for (int  i = 0; i < rows; i++) { vec[i] = getRandomVector(cols); }
    return vec;
}

int sequentialCalc(std::vector<std::vector<int>> vect, int rows, int cols) {
    int sum = 0;
    for (int  i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += vect[i][j];
        }
    }
    return sum;
}


int parallelCalc(std::vector<std::vector<int>> vect, int rows, int cols) {
    int proc_count = 0, proc_rank = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    int proc_amount_of_data = 0;
    for (int i = proc_rank; i < cols; i += proc_count) {
         proc_amount_of_data+= rows;
    }

    if (proc_rank == 0) {
        for (int proc = 1; proc < proc_count; proc++) {
            std::vector<int> flatten_vect;
            int cols_to_proc = 0;
            for (int i = proc; i < cols; i += proc_count) {
                for (int j = 0; j < rows; j++) {
                    flatten_vect.push_back(vect[j][i]);
                }
                cols_to_proc++;
            }

            int amount_of_data_sent = cols_to_proc*rows;
            MPI_Send(flatten_vect.data(), amount_of_data_sent, MPI_INT,
                        proc, 0, MPI_COMM_WORLD);
        }
    }


    std::vector<int> local_vec(proc_amount_of_data);
    if (proc_rank == 0) {
        for (int i = 0; i < cols; i += proc_count) {
            for (int j = 0; j < rows; j++) {
                local_vec.push_back(vect[j][i]);
            }
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_vec.data(), proc_amount_of_data, MPI_INT,
                    0, 0, MPI_COMM_WORLD, &status);
    }

    int partial_sum = 0;
    for (int &i : local_vec) {
        partial_sum  += i;
    }
    int sum;
    MPI_Reduce(&partial_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return sum;
}
