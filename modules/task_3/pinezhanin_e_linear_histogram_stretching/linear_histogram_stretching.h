// Copyright 2021 Pinezhanin Evgeny
#ifndef MODULES_TASK_3_PINEZHANIN_E_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_
#define MODULES_TASK_3_PINEZHANIN_E_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_

#include <vector>

typedef unsigned char uchar;

std::vector<std::vector<uchar>> getRandomMatrix(int height, int width, uchar a, uchar b);
std::vector<std::vector<uchar>> LinearHistogramStretchingParallel(std::vector<std::vector<uchar>> image);
std::vector<std::vector<uchar>> LinearHistogramStretchingSequential(std::vector<std::vector<uchar>> image);

#endif  // MODULES_TASK_3_PINEZHANIN_E_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_
