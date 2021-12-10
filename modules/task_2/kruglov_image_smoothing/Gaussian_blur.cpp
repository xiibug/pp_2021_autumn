// Copyright 2021 Kruglov Aleksei
#include <mpi.h>
#include <algorithm>
#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include "../../../modules/task_2/kruglov_image_smoothing/Gaussian_blur.h"

Image get_random_image(int height, int width) {
    std::random_device device;
    std::mt19937 gen(device());
    Image image(height, std::vector<std::uint8_t>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = static_cast<std::uint8_t>(gen() % 256);
        }
    }
    return image;
}

Image get_image_from_file(const std::string& path) {
    std::ifstream in(path);
    Image image;
    if (in.is_open()) {
        int i = 0;
        while (!in.eof()) {
            std::string line;
            std::getline(in, line);
            if (line.empty())
                continue;
            std::stringstream in_stream(line);
            image.push_back(std::vector<std::uint8_t>());
            while (!in_stream.eof()) {
                int x;
                in_stream >> x;
                image[i].push_back(static_cast<std::uint8_t>(x));
            }
            i++;
        }
        in.close();
    } else {
        std::string error = path + " file not founded";
        throw std::invalid_argument(error);
    }
    return image;
}

void save_image_in_file(const std::string& path, const Image& image) {
    std::ofstream out(path);
    int height = static_cast<int>(image.size());
    int width = static_cast<int>(image[0].size());
    if (out.is_open()) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                out << static_cast<int>(image[i][j]);
                if (j != width - 1) {
                    out << " ";
                }
            }
            out << std::endl;
        }
    }
    out.close();
}

Matrix create_gaussian_kernel(int radius, float sigma) {
    int size = 2 * radius + 1;
    Matrix kernel(size, std::vector<float>(size));
    float norm = 0;
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            // e^(-(x^2 + y^2) / (2 * sigma^2 ))
            kernel[i + radius][j + radius] = std::exp(-(i * i + j * j) / (2 * sigma * sigma));
            norm += kernel[i + radius][j + radius];
        }
    }
    // Each pixel's new value is set to a weighted average of that pixel's neighborhood
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            kernel[i][j] /= norm;
        }
    }
    return kernel;
}

Image apply_gaussian_blur(const Image& image, const Matrix& kernel) {
    int height = static_cast<int>(image.size());
    int width = static_cast<int>(image[0].size());
    Image result(height, std::vector<std::uint8_t>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            result[i][j] = calculate_new_pixel(image, kernel, i, j);
        }
    }
    return result;
}

Image apply_gaussian_blur_parallel(const Image& image, const Matrix& kernel) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    std::vector<int> sizes(3);
    std::vector<int> count_sends(proc_num), offset;  // both in pixels
    std::vector<std::uint8_t> send_data, receive_data;
    if (proc_rank == 0) {
        if (image.size() == 0 || image[0].size() == 0) {
            throw std::invalid_argument("image size is 0");
        }
        int height = static_cast<int>(image.size());
        int width = static_cast<int>(image[0].size());
        int radius = static_cast<int>(kernel.size() / 2);
        send_data.reserve(height * width);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                send_data.push_back(image[i][j]);
            }
        }
        sizes[0] = height;
        sizes[1] = width;
        sizes[2] = radius;
        int rows_per_proc = height / proc_num;
        int above_average = height % proc_num;
        count_sends.assign(proc_num, rows_per_proc * width);
        for (int i = 0; i < above_average; i++) {
            // adding to processes the remaining rows
            count_sends[i] += width;
        }
        offset.resize(proc_num);
        for (int i = 1; i < proc_num && count_sends[i] > 0; i++)
            offset[i] = offset[i - 1] + count_sends[i - 1];
        // also, to save accuracy we have to send the adding rows
        // above and below the sending part of image
        // for first and last part we have to receive the rows above/below
        // the sending part
        // count of adding rows is equal to kernel's radius
        if (proc_num != 1) {
            save_an_accuracy(count_sends.data(), offset.data(), width, radius);
        }
    }
    MPI_Bcast(reinterpret_cast<void*>(sizes.data()), static_cast<int>(sizes.size()),
              MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(reinterpret_cast<void*>(count_sends.data()), static_cast<int>(count_sends.size()),
              MPI_INT, 0, MPI_COMM_WORLD);

    int height = sizes[0];
    int width = sizes[1];
    int radius = sizes[2];
    receive_data.resize(count_sends[proc_rank]);
    MPI_Scatterv(reinterpret_cast<const void*>(send_data.data()), count_sends.data(), offset.data(),
                 MPI_INT8_T, reinterpret_cast<void*>(receive_data.data()), count_sends[proc_rank],
                 MPI_INT8_T, 0, MPI_COMM_WORLD);

    Image received_image(count_sends[proc_rank] / width, std::vector<std::uint8_t>(width));
    std::size_t cnt = 0;
    for (std::size_t i = 0; i < received_image.size(); i++) {
        for (std::size_t j = 0; j < received_image[i].size(); j++) {
            received_image[i][j] = receive_data[cnt++];
        }
    }
    auto result = get_result_image(received_image, kernel, count_sends.data(), width, radius);
    MPI_Barrier(MPI_COMM_WORLD);
    Image all_result;
    if (proc_rank != 0) {
        int h = static_cast<int>(result.size());
        MPI_Send(reinterpret_cast<void*>(&h), 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        for (int i = 0; i < h; i++) {
            MPI_Send(reinterpret_cast<void*>(result[i].data()), width, MPI_INT8_T, 0, i + 1, MPI_COMM_WORLD);
        }
    } else {
        all_result.assign(height, std::vector<std::uint8_t>(width));
        std::size_t j = 0;
        for (size_t i = 0; i < result.size(); i++, j++) {
            all_result[i] = std::move(result[j]);
        }
        for (int i = 1; i < proc_num; i++) {
            int h;
            MPI_Status* status = new MPI_Status();
            MPI_Recv(&h, 1, MPI_INT, i, 0, MPI_COMM_WORLD, status);
            for (int c = 0; c < h; c++, j++) {
                MPI_Recv(reinterpret_cast<void*>(all_result[j].data()), width,
                         MPI_INT, i, c + 1, MPI_COMM_WORLD, status);
            }
        }
    }

    return all_result;
}

void save_an_accuracy(int* count_sends, int* offset, int width, int radius) {
    int proc_num;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    for (int i = 0; i < proc_num; i++) {
        // situations, when proc_num > height, then we will not use all processes
        if (count_sends[i] == 0) {
            break;
        }
        if (i == 0) {
            count_sends[i] += width * radius;
            continue;
        }
        if (is_last_process(count_sends, i)) {
            count_sends[i] += width * radius;
            offset[i] -= width * radius;
            continue;
        }
        count_sends[i] += width * radius * 2;
        offset[i] -= width * radius;
    }
}

Image get_result_image(const Image& received_image, const Matrix& kernel, int* count_sends,
                       int width, int radius) {
    // when num_proc > image height, then some proccess doesn't get any data
    if (received_image.size() == 0)
        return Image();
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Image result;
    int rows_offset = radius;
    // for zero process is never needed an rows offset to calculate result
    if (proc_rank == 0) {
        rows_offset = 0;
    }
    int res_height;
    if (proc_rank == 0) {
        res_height = count_sends[proc_rank] / width;
        if (proc_num != 1) {
            res_height -= radius;
        }
    } else {
        res_height = count_sends[proc_rank] / width - 2 * radius;
        if (is_last_process(count_sends, proc_rank))
            res_height += radius;
    }
    result.assign(res_height, std::vector<std::uint8_t>(width));
    for (int i = 0; i < res_height; i++) {
        for (int j = 0; j < width; j++) {
            result[i][j] = calculate_new_pixel(received_image, kernel, i + rows_offset, j);
        }
    }
    return result;
}

std::uint8_t calculate_new_pixel(const Image& image, const Matrix& kernel, int x, int y) {
    int height = static_cast<int>(image.size());
    int width = static_cast<int>(image[0].size());
    int radH = static_cast<int>(kernel.size() / 2);
    int radW = static_cast<int>(kernel[0].size() / 2);
    float res = 0;
    for (int i = -radH; i <= radH; i++) {
        for (int j = -radW; j <= radW; j++) {
            int i_clamb = clamp(x + i, 0, height - 1);
            int j_clamb = clamp(y + j, 0, width - 1);
            res += static_cast<float>(image[i_clamb][j_clamb]) * kernel[i + radH][j + radW];
        }
    }
    return static_cast<std::uint8_t>(clamp(static_cast<int>(res), 0, 255));
}

bool is_last_process(int* count_sends, int i) {
    int proc_num;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    if (i == proc_num - 1 || (i + 1 < proc_num && count_sends[i + 1] == 0)) {
        return true;
    }
    return false;
}

int clamp(int value, int min, int max) {
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

bool is_equal(const Image& img1, const Image& img2, int threshold) {
    if (img1.size() != img2.size()) {
        return false;
    }
    for (std::size_t h = 0; h < img1.size(); h++) {
        if (img1[h].size() != img2[h].size()) {
            return false;
        }
        for (std::size_t w = 0; w < img1[h].size(); w++) {
            int val1 = static_cast<int>(img1[h][w]);
            int val2 = static_cast<int>(img2[h][w]);
            if (abs(val1 - val2) > threshold) {
                return false;
            }
        }
    }
    return true;
}
