// Copyright 2021 Chornyi Yurii
#ifndef MODULES_TASK_2_CHORNYI_Y_SMOOTHING_FILTER_SMOOTHING_FILTER_H_
#define MODULES_TASK_2_CHORNYI_Y_SMOOTHING_FILTER_SMOOTHING_FILTER_H_

#include <vector>

using std::vector;

// Fill matrix of color
vector<vector<float>> fillMatrixOfColor(const int matrixWidth, const int matrixHeight);

template <typename T>
T clamp(T value, T min, T max);
float calculateNewPixelColor(const vector<vector<float>>& colorMatrix, const int radiusCore,
                                                            int coordinateX, int coordinateY);

vector<vector<float>> singleSmoothingImage(const vector<vector<float>>& colorMatrix, const int radiusCore);
vector<vector<float>> parallelSmoothingImage(const vector<vector<float>>& colorMatrix, const int radiusCore);

#endif  // MODULES_TASK_2_CHORNYI_Y_SMOOTHING_FILTER_SMOOTHING_FILTER_H_
