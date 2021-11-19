// Copyright 2021 Novozhilov Alexander
#ifndef MODULES_TASK_3_NOVOZHILOV_A_HISTOGRAM_LINEAR_STRETCHING_HISTOGRAM_LINEAR_STRETCHING_H_
#define MODULES_TASK_3_NOVOZHILOV_A_HISTOGRAM_LINEAR_STRETCHING_HISTOGRAM_LINEAR_STRETCHING_H_

#include <vector>

std::vector<int> getRandomVector(int sz);

std::vector<std::vector<int>> getRandomMatrix(int rows, int cols);

std::vector<int> maxValuesInColumnsSequential(std::vector<std::vector<int>> matrix);

std::vector<int> minValuesInColumnsSequential(std::vector<std::vector<int>> matrix);

std::vector<std::vector<int>> histogrammStretchingSequential(std::vector<std::vector<int>> image);

std::vector<std::vector<int>> histogrammStretchingParallel(const std::vector<std::vector<int>>& image, int rows, int cols);

int maxValueInVector(const std::vector<int>& vector);

int minValueInVector(const std::vector<int>& vector);


#endif  // MODULES_TASK_3_NOVOZHILOV_A_HISTOGRAM_LINEAR_STRETCHING_HISTOGRAM_LINEAR_STRETCHING_H_
