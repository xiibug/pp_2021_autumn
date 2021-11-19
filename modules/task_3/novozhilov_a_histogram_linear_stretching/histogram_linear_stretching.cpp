// Copyright 2021 Novozhilov Alexander
#include <mpi.h>
#include <vector>
#include <random>
#include <algorithm>
#include "../../../modules/task_3/novozhilov_a_histogram_linear_stretching/histogram_linear_stretching.h"

std::vector<int> getRandomVector(int sz) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; i++) { vec[i] = gen() % 255; }
    return vec;
}

std::vector<std::vector<int>> getRandomMatrix(int rows, int cols) {
    std::vector<std::vector<int>> matrix;
    for (int i = 0; i < rows; i++) {
        matrix.push_back(getRandomVector(cols));
    }
    return matrix;
}

std::vector<int> maxValuesInColumnsSequential(const std::vector<std::vector<int>>& matrix) {
    std::vector<int> result;
    for (int i = 0; i < static_cast<int>(matrix[0].size()); i++) {
        int max = matrix[0][i];
        for (int j = 0; j < static_cast<int>(matrix.size()); j++) {
            if (matrix[j][i] > max) {
                max = matrix[j][i];
            }
        }
        result.push_back(max);
    }
    return result;
}

std::vector<int> minValuesInColumnsSequential(const std::vector<std::vector<int>>& matrix) {
    std::vector<int> result;
    for (int i = 0; i < static_cast<int>(matrix[0].size()); i++) {
        int min = matrix[0][i];
        for (int j = 0; j < static_cast<int>(matrix.size()); j++) {
            if (matrix[j][i] < min) {
                min = matrix[j][i];
            }
        }
        result.push_back(min);
    }
    return result;
}


std::vector<std::vector<int>> histogrammStretchingSequential(std::vector<std::vector<int>> image) {
    int y_min = image[0][0];
    int y_max = image[0][0];
    for (int i = 0; i < static_cast<int>(image.size()); i++) {
        for (int j = 0; j < static_cast<int>(image[i].size()); j++) {
            if (image[i][j] > y_max) {
                y_max = image[i][j];
            }
            if (image[i][j] < y_min) {
                y_min = image[i][j];
            }
        }
    }
    for (int i = 0; i < static_cast<int>(image.size()); i++) {
        for (int j = 0; j < static_cast<int>(image[i].size()); j++) {
            image[i][j] = static_cast<int>((image[i][j] - y_min) * (255 / static_cast<double>((y_max - y_min))));
        }
    }
    return image;
}

std::vector<std::vector<int>> histogrammStretchingParallel(const std::vector<std::vector<int>>& image,
                                                                                   int rows, int cols) {
    int size = 0, rank = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rows_per_proc = rows / size;
    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            for (int i = 0; i < rows_per_proc; i++) {
                MPI_Send(image[proc * rows_per_proc + i].data(), cols, MPI_INT, proc, 0, MPI_COMM_WORLD);
            }
        }
    }
    std::vector<int> local_max_vec(cols);
    std::vector<int> local_min_vec(cols);
    std::vector<std::vector<int>> local_matrix;
    std::vector<int> max_vec(cols);
    std::vector<int> min_vec(cols);
    if (rank == 0) {
        for (int i = 0; i < rows_per_proc; i++) {
            local_matrix.push_back(image[i]);
        }
        if (rows % size != 0) {
            for (int i = static_cast<int>(image.size()) - rows % size; i < static_cast<int>(image.size()); i++) {
                local_matrix.push_back(image[i]);
            }
        }
        local_max_vec = maxValuesInColumnsSequential(local_matrix);
        local_min_vec = minValuesInColumnsSequential(local_matrix);
    } else {
        std::vector<int> tmp(cols);
        MPI_Status status;
        for (int i = 0; i < rows_per_proc; i++) {
            MPI_Recv(tmp.data(), cols, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            local_matrix.push_back(tmp);
        }
        local_max_vec = maxValuesInColumnsSequential(local_matrix);
        local_min_vec = minValuesInColumnsSequential(local_matrix);
    }
    MPI_Reduce(local_max_vec.data(), max_vec.data(), cols, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(local_min_vec.data(), min_vec.data(), cols, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    int min;
    int max;
    if (rank == 0) {
        min = minValueInVector(min_vec);
        max = maxValueInVector(max_vec);
    }
    MPI_Bcast(&min, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&max, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < static_cast<int>(local_matrix.size()); i++) {
        for (int j = 0; j < static_cast<int>(local_matrix[0].size()); j++) {
            local_matrix[i][j] = static_cast<int>((local_matrix[i][j] - min) * (255 / static_cast<double>(max - min)));
        }
    }
    std::vector<std::vector<int>> result;
    if (rank == 0) {
        for (int i = 0; i < rows_per_proc; i++) {
            result.push_back(local_matrix[i]);
        }
        std::vector<int> tmp(cols);
        MPI_Status status;
        for (int proc = 1; proc < size; proc++) {
            for (int i = 0; i < rows_per_proc; i++) {
                MPI_Recv(tmp.data(), cols, MPI_INT, proc, 0, MPI_COMM_WORLD, &status);
                result.push_back(tmp);
            }
        }
        if (static_cast<int>(local_matrix.size()) > rows_per_proc) {
            for (int i = 0; i < static_cast<int>(local_matrix.size()) - rows_per_proc; i++) {
                result.push_back(local_matrix[rows_per_proc + i]);
            }
        }
    } else {
        for (int i = 0; i < rows_per_proc; i++) {
            MPI_Send(local_matrix[i].data(), cols, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    return result;
}

int maxValueInVector(const std::vector<int>& vector) {
    int max = vector[0];
    for (int i : vector) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}

int minValueInVector(const std::vector<int>& vector) {
    int min = vector[0];
    for (int i : vector) {
        if (i < min) {
            min = i;
        }
    }
    return min;
}
