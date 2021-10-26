#ifndef _VECTOR_ALTERNATIONS_H
#define _VECTOR_ALTERNATIONS_H

#include <mpi.h>
#include <random>
#include <limits>


// standard checking for alterations
int sequentialCount_V1(const int* vec, int len);

// optimized checking for alternations
int sequentialCount_V2(const int* vec, int len);

// parallel checking for alternations
int parallelCount(const int* vec, int len);

// fill vector with random values (value != 0)
void fillVecWithRandValues(int* vec, int len);

#endif
