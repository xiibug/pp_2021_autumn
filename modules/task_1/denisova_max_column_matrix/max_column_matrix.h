// Copyright 2021 Denisova Julia
#ifndef MODULES_TASK_1_DENISOVA_MAX_COLUMN_MATRIX_MAX_COLUMN_MATRIX_H_
#define MODULES_TASK_1_DENISOVA_MAX_COLUMN_MATRIX_MAX_COLUMN_MATRIX_H_

void findmax(int* mas, int col, int str, int* tmpmax);
void random_matrix(int str, int col, int* matrix);
void swap_matrix(int str, int col, int* matrix, int* bigmas);
void max_from_columns(int str, int col, int* bigmas, int* resbuf);

#endif  //MODULES_TASK_1_DENISOVA_MAX_COLUMN_MATRIX_MAX_COLUMN_MATRIX_H_