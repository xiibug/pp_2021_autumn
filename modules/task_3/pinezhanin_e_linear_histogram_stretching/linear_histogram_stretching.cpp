// Copyright 2021 Pinezhanin Evgeny
#include <mpi.h>
#include <vector>
#include <random>
#include "../../../modules/task_3/pinezhanin_e_linear_histogram_stretching/linear_histogram_stretching.h"

std::vector<uchar> getRandomMatrix(int height, int width, int a, int b) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<uchar> matrix;
    matrix.resize(height * width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i * width + j] = gen() % (b - a) + a;
        }
    }
    return matrix;
}

std::vector<uchar> LinearHistogramStretchingParallel(std::vector<uchar> image, int width) {
    int size, rank;
    //MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //int* sendCounts = new int[size];
    //int* displs = new int[size];
    //int height, width;
    ////image.data()[0].data = 0;
//
    //height = image.size();
    //width = image[0].size();
    //MPI_Bcast(&height, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Bcast(&width, 1, MPI_INT, 0, MPI_COMM_WORLD);
//
    //for (int i = 0; i < size; i++) {
    //    sendCounts[i] = height / size;
    //}
    //for (int i = 0; i < height % size; i++) {
    //    sendCounts[i] += 1;
    //}
    //displs[0] = 0;
    //for (int i = 1; i < size; i++) {
    //    displs[i] = displs[i - 1] + sendCounts[i - 1];
    //}
//
    //uchar *part_vec = new uchar[sendCounts[rank] * width];

    return image;
}

std::vector<uchar> LinearHistogramStretchingSequential(std::vector<uchar> image) {
    double a, b;
    int imin = 255, imax = 0;
    int size = image.size();
    for (int i = 0; i < size; i++) {
        if (image[i] < imin) imin = image[i];
        if (image[i] > imax) imax = image[i];
    }
    if (imin == imax) {
        a = 0.0; b = 0.0;
    } else {
        if (imin != 0) {
            b = 255.0 / (1.0 - static_cast<double>(imax) / imin);
        } else {
            b = 0.0;
        }
        a = -255.0 / (static_cast<double>(imin) - imax);
    }
    for (int i = 0; i < size; i++) {
        image[i] = round(a * image[i] + b);
    }
    return image;
}
