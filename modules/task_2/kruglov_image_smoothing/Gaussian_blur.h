// Copyright 2021 Kruglov Aleksei
#ifndef MODULES_TASK_2_KRUGLOV_IMAGE_SMOOTHING_GAUSSIAN_BLUR_H_
#define MODULES_TASK_2_KRUGLOV_IMAGE_SMOOTHING_GAUSSIAN_BLUR_H_

#include <vector>
#include <string>

typedef std::vector<std::vector<float>> Matrix;
typedef std::vector<std::vector<std::uint8_t>> Image;

Image get_random_image(int height, int width);

Image get_image_from_file(const std::string& path);

void save_image_in_file(const std::string& path, const Image& image);

Matrix create_gaussian_kernel(int radius, float sigma);

Image apply_gaussian_blur(const Image& image, const Matrix& kernel);

Image apply_gaussian_blur_parallel(const Image& image, const Matrix& kernel);

void save_an_accuracy(int* count_sends, int* offset, int width, int radius);

Image get_result_image(const Image& received_image, const Matrix& kernel, int* count_sends,
                       int width, int radius);

// last used process always work with lower bound of image
// there is need to check this process
bool is_last_process(int* count_sends, int index);

std::uint8_t calculate_new_pixel(const Image& image, const Matrix& kernel, int x, int y);

int clamp(int value, int min, int max);

// processes uses different order of calculations
// same values can rounds in different ways
// that's why we need to validate values with some threshold
bool is_equal(const Image& img1, const Image& img2, int threshold);

#endif  // MODULES_TASK_2_KRUGLOV_IMAGE_SMOOTHING_GAUSSIAN_BLUR_H_
