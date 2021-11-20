// Copyright 2021 Gleb "belgad" Danshin
#include "../../../modules/task_1/danshin_g_matrix_max_by_rows/matrix_max_by_rows.h"

int *GetRandomMatrix(int row_num, int col_num) {
    int *matrix = new int[row_num * col_num];
    std::random_device random_device;
    std::mt19937 random_engine(random_device());

    for (int i = 0; i < row_num * col_num; ++i) {
        matrix[i] = random_engine();
    }

    return matrix;
}

int *GetMatrixRowMaxSequence(int *matrix, int row_num, int col_num) {
    int *answer = new int[row_num];
    for (int i = 0; i < row_num; ++i) {
        answer[i] = matrix[i * col_num];
        for (int j = 1; j < col_num; ++j) {
            if (matrix[i * col_num + j] > answer[i]) {
                answer[i] = matrix[i * col_num + j];
            }
        }
    }
    return answer;
}

int *GetMatrixRowMaxParallel(int *matrix, int row_num, int col_num) {
    int comm_size, comm_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    if (comm_rank == 0) {
        MPI_Bcast(&row_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&col_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(&row_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&col_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (row_num <= 2 * comm_size) {
        if (comm_rank == 0) {
            return GetMatrixRowMaxSequence(matrix, row_num, col_num);
        } else {
            return nullptr;
        }
    }

    int *answer = new int[row_num], *send_elem_count = new int[comm_size],
    *data, *send_elem_displacements = new int[comm_size];

    MPI_Datatype vector_t;
    MPI_Type_contiguous(col_num, MPI_INT, &vector_t);
    MPI_Type_commit(&vector_t);

    if (comm_rank == 0) {
        int send_elem_count_atomic = row_num / comm_size, send_elem_count_overflow = row_num % comm_size;
        for (int i = 0; i < comm_size; ++i) {
            send_elem_count[i] = send_elem_count_atomic + (--send_elem_count_overflow >= 0);
        }
        send_elem_displacements[0] = 0;
        for (int i = 1; i < comm_size; ++i) {
            send_elem_displacements[i] = send_elem_displacements[i - 1] + send_elem_count[i - 1];
        }
    }

    MPI_Bcast(send_elem_count, comm_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(send_elem_displacements, comm_size, MPI_INT, 0, MPI_COMM_WORLD);
    data = new int[col_num * send_elem_count[comm_rank]];
    MPI_Scatterv(matrix, send_elem_count, send_elem_displacements, vector_t,
    data, send_elem_count[comm_rank], vector_t, 0, MPI_COMM_WORLD);

    int *answer_atomic = new int[send_elem_count[comm_rank]];
    int col_now = 0;

    for (int i = 0; i < send_elem_count[comm_rank]; ++i) {
        answer_atomic[i] = data[col_now];
        for (int j = 1; j < col_num; ++j) {
            if (data[col_now + j] > answer_atomic[i]) {
              answer_atomic[i] = data[col_now + j];
            }
        }
        col_now += col_num;
    }

    MPI_Gatherv(answer_atomic, send_elem_count[comm_rank], MPI_INT,
    answer, send_elem_count, send_elem_displacements, MPI_INT, 0, MPI_COMM_WORLD);

    delete [] send_elem_count;
    delete [] send_elem_displacements;
    delete [] data;
    delete [] answer_atomic;

    return answer;
}
