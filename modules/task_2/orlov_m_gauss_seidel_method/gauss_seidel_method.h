//  Copyright 2021 Maksim Orlov

#include <mpi.h>
#include <vector>

std::vector<double> sequentialGaussSeidel(std::vector<std::vector<double>> coeffMatrix, std::vector<double> rightSide, double eps);
std::vector<double> gaussSeidel(std::vector<std::vector<double>> coeffMatrix, std::vector<double> rightSide, double eps);