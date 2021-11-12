// Copyright 2021 TexHik620953
#include "./lex_ordering.h"
#include <mpi.h>
#include <list>
#include <cstring>
#include <iostream>
const char ALPHABET[26] = "ABCDEFGHIJKLMOPQRSTUVWXYZ";

char* get_random_string(int len) {
	char* arr = new char[len + 1];
	for (int i = 0; i < len; i++) {
		arr[i] = ALPHABET[(rand() * 26 / RAND_MAX)];
	}
	arr[len] = '\0';
	return arr;
}

int basic_compare(const char c1, const char c2) {
	int r = (int)c2 - (int)c1;
	if (r > 0) return 1;
	else if (r < 0) return -1;
	else return 0;
	return 0;
}
int seq_lex_compare(const char* str1, const char* str2, int size) 
{
	int r = 0;
	for (int i = 0; i < size; ++i) {
		r = basic_compare(str1[i], str2[i]);
		if (r != 0)
			break;
	}
	return r;
}

int omp_lex_compare(const char* str1, const char* str2, int len) {


	int root = 0;
	int rank = 0, commSize = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	const int block_size = len / commSize;
	const int shift = len% block_size;

	char* buffer1 = new char[block_size];
	char* buffer2 = new char[block_size];

	int* global_result = new int[block_size + 1];
	for (int i = 0; i <= block_size; i++) {
		global_result[i] = 0;
	}

	//int global_result = 0;
	MPI_Scatter(str1 + shift, block_size, MPI_CHAR, buffer1, block_size, MPI_CHAR, root, MPI_COMM_WORLD);
	MPI_Scatter(str2 + shift, block_size, MPI_CHAR, buffer2, block_size, MPI_CHAR, root, MPI_COMM_WORLD);
	int local_result = 0;
	local_result = seq_lex_compare(buffer1, buffer2, block_size);
	MPI_Reduce(reinterpret_cast<void*>(&local_result), reinterpret_cast<void*>(global_result + rank + 1), 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

	if (rank == root) {
		global_result[0] = seq_lex_compare(str1, str2, shift);
	}
	for (int i = 0; i <= block_size; i++) {
		if (global_result[i] != 0)
			return global_result[i];
	}
	return 0;
}
