// Copyright 2021 TexHik620953
#include <iostream>
#ifndef MODULES_TASK_1_RODIONOV_N_CHECKING_LEXICOGRAPHIC_ORDERING_LEX_ORDERING_H_
#define MODULES_TASK_1_RODIONOV_N_CHECKING_LEXICOGRAPHIC_ORDERING_LEX_ORDERING_H_


int randint(int min, int max);
char* get_random_string(int len);
int basic_compare(const char c1, const char c2);
int seq_lex_compare(const char* str1, const char* str2, int size);
int omp_lex_compare(const char* str1, const char* str2, int len);


#endif  // MODULES_TASK_1_RODIONOV_N_CHECKING_LEXICOGRAPHIC_ORDERING_LEX_ORDERING_H_
