// Copyright 2021 Lakhov Kirill
#include <mpi.h>
#include <vector>
#include <random>
using namespace std;

vector<int> getRandomVector(int sz);

vector<vector<int>> getRandomMatrix(int rows, int cols);

int sequentialCalc(vector<vector<int>> vect, int rows, int cols);

int parallelCalc(vector<vector<int>> vect, int rows, int cols);