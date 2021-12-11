// Copyright 2021 Zharkov Andrey
#include "../../../modules/task_3/zharkov_a_lin_hist/lin_hist.h"

#include <mpi.h>
#include <ctime>
#include <random>
#include <iostream>

int* getRandomArr(int width, int height) {
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(0.3, 0.7);
    int* img = new int[width * height];
    for (int i = 0; i < width * height; i++) {
        img[i] = rand() % 255;
    }
    return img;
}
int get_local_min(int* local_img, int width, int height) {
    int min = local_img[0];
    for (int i = 0; i < width * height; i++) {
        if (local_img[i] < min) {
            min = local_img[i];
        }
    }
    return min;
}
int get_local_max(int* local_img, int width, int height) {
    int max = local_img[0];
    for (int i = 0; i < width * height; i++) {
        if (local_img[i] > max) {
            max = local_img[i];
        }
    }
    return max;
}
int get_global_min(int* arr, int size) {
    int min = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
int get_global_max(int* arr, int size) {
    int max = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
int truncate(int value) {
    if (value < 0) return 0;
    if (value > 255.0) return 255;

    return value;
}
int* get_Sequential_lin_hist(int* img, int width, int height, int min, int max) {
    int* new_img = new int[width * height];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            new_img[j + i * width] =
            truncate((img[j + i * width] - min) * (255/(max - min)));
        }
    }
    return new_img;
}
int* get_Parallel_lin_hist(int* image, int width, int height) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int delta = height / size;
    int rem = height % size;

    int local_min;
    int local_max;
    rem;
    if (delta) {
        if (rank == 0) {
            for (int proc = 1; proc < size; proc++) {
                MPI_Send(image + proc * delta * width + rem * width, delta * width,
                    MPI_INT, proc, 0, MPI_COMM_WORLD);
            }
        }
        int* local_img = nullptr;
        int* local_min_arr = new int[size];
        int* local_max_arr = new int[size];
        if (rank == 0) {
            local_img = new int[(delta + rem) * width];
            for (int i = 0; i < (delta + rem) * width; i++) local_img[i] = image[i];

            local_min = get_local_min(local_img, width, delta + rem);
            local_max = get_local_max(local_img, width, delta + rem);
            local_min_arr[rank] = local_min;
            local_max_arr[rank] = local_max;
        } else {
            local_img = new int[delta * width];
            MPI_Status status;
            MPI_Recv(local_img, delta * width, MPI_INT, 0, 0, MPI_COMM_WORLD,
                &status);
            local_min = get_local_min(local_img, width, delta);
            local_max = get_local_max(local_img, width, delta);
            local_min_arr[rank] = local_min;
            local_max_arr[rank] = local_max;
        }
        
        int min;
        int max;
        if (rank == 0) {
            min = get_global_min(local_min_arr, size);
            max = get_global_max(local_max_arr, size);
        }
              
        int* global_img = nullptr;
        int temp = 0;
        if (rank == 0) {
            temp = rem;
        }
        /*for (int i = 0; i < width * height; i++) {
            std::cout << local_img[i] << " ";
        }
        std::cout << std::endl;*/
        local_img = get_Sequential_lin_hist(local_img, width, delta + temp, min, max);
        /*for (int i = 0; i < width * height; i++) {
            std::cout << local_img[i] << " ";
        }
        std::cout << std::endl;*/

        int* counts = new int[size], * displs = new int[size];
        if (rank == 0) {
            global_img = new int[width * height];
            for (int i = 0; i < size; i++) {
                if (i == 0) {
                    counts[i] = (delta + rem) * width;
                    displs[i] = 0;
                } else {
                    counts[i] = delta * width;
                    displs[i] = (delta * i + rem) * width;
                }
            }
        }
        /*for (int i = 0; i < width * height; i++) {
            std::cout << global_img[i] << " ";
        }
        std::cout << std::endl;*/
        MPI_Gatherv(local_img, (delta + temp) * width, MPI_INT, global_img,
            counts, displs, MPI_INT, 0, MPI_COMM_WORLD);
        /*for (int i = 0; i < width * height; i++) {
            std::cout << global_img[i] << " ";
        }
        std::cout << std::endl;*/
        return global_img;
    } else {
        if (rank == 0) {
            int min = get_local_min(image, width, height);
            int max = get_local_max(image, width, height);
            return get_Sequential_lin_hist(image, width, height, min, max);
        } else {
            return nullptr;
        }
    }
}
