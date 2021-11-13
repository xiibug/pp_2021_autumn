// Copyright 2021 Bakalina Darya
#ifndef MODULES_TASK_2_BAKALINA_D_MULTIPLICATION_MTRX_BY_VEC_MULTIPLICATION_MTRX_BY_VEC_H_
#define MODULES_TASK_2_BAKALINA_D_MULTIPLICATION_MTRX_BY_VEC_MULTIPLICATION_MTRX_BY_VEC_H_

int* lin_multiply(int** mtrx, int* v, int size_n, int size_m);
int* multiplication(int* mtrx, int* v, int size_n, int ProcSndNumbr, int SndNumrVctr);
int** create_random_matrix(const int size_n, const int size_m);
int* create_random_vector(const int len);
void print_vector(int* v, const int len);
void print_matrix(int** mtrx, int size_n, int size_m);
int* ñonvert_mtrx_to_vctr(int** mtrx, int size_n, int size_m);
int* paral_multiply(int** mtrx, int* v, int size_n, int size_m);
bool check_equality(int* mas, int* mas1, int lines);

#endif  // MODULES_TASK_2_BAKALINA_D_MULTIPLICATION_MTRX_BY_VEC_MULTIPLICATION_MTRX_BY_VEC_H_