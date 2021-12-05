// Copyright 2021 Gleb "belgad" Danshin
#ifndef MODULES_TASK_1_DANSHIN_G_MATRIX_MAX_BY_ROWS_MATRIX_MAX_BY_ROWS_H_
#define MODULES_TASK_1_DANSHIN_G_MATRIX_MAX_BY_ROWS_MATRIX_MAX_BY_ROWS_H_

#include <mpi.h>
#include <random>

int *GetRandomMatrix(int row_num, int col_num);
int *GetMatrixRowMaxSequence(int *matrix, int row_num, int col_num);
int *GetMatrixRowMaxParallel(int *matrix, int row_num, int col_num);

#endif  // MODULES_TASK_1_DANSHIN_G_MATRIX_MAX_BY_ROWS_MATRIX_MAX_BY_ROWS_H_
