// Copyright 2021 Chornyi Yurii
#include <mpi.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include "../../../modules/task_2/chornyi_y_smoothing_filter/smoothing_filter.h"

using std::vector;

vector<vector<float>> fillMatrixOfColor(const int matrixWidth, const int matrixHeight) {
    std::vector<vector<float>> colorMatrix(matrixWidth);

    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(0, 1);

    for (int i = 0; i < matrixWidth; ++i) {  // Filling the matrix with random values
        colorMatrix[i] = vector<float>(matrixHeight);
        for (int j = 0; j < matrixHeight; ++j)
            colorMatrix[i][j] = urd(gen);
    }

    return colorMatrix;
}

template <typename T>
T clamp(T value, T min, T max) {
    if (value > max) return max;
    else if (value < min) return min;
    return value;
}

float calculateNewPixelColor(const vector<vector<float>>& colorMatrix, const int radiusCore,
                                                            int coordinateX, int coordinateY) {
    int areaWidth = 2 * radiusCore + 1;
    vector<float> vectorOfValue(areaWidth * areaWidth);

    int index = 0;
    for (int i = -radiusCore; i <= radiusCore; i++)
        for (int j = -radiusCore; j <= radiusCore; j++) {
            float color = colorMatrix[clamp<int>(coordinateX + j, 0, colorMatrix.size() - 1)]
                                     [clamp<int>(coordinateY + i, 0, colorMatrix[0].size() - 1)];
            vectorOfValue[index] = color;

            index += 1;
        }

    std::sort(vectorOfValue.data(), vectorOfValue.data() + areaWidth * areaWidth);
    return clamp<float>(vectorOfValue[(areaWidth * areaWidth) / 2], 0, 1);
}

vector<vector<float>> singleSmoothingImage(const vector<vector<float>>& colorMatrix, const int radiusCore) {
    int matrixWidth = colorMatrix.size(), matrixHeight = colorMatrix[0].size();
    vector<vector<float>> resultMatrix(matrixWidth);

    for (int x = 0; x < matrixWidth; ++x) {
        resultMatrix[x] = vector<float>(matrixHeight);
        for (int y = 0; y < matrixHeight; ++y)
            resultMatrix[x][y] = calculateNewPixelColor(colorMatrix, radiusCore, x, y);
    }

    return resultMatrix;
}
vector<vector<float>> parallelSmoothingImage(const vector<vector<float>>& colorMatrix, const int radiusCore) {
    int matrixWidth = 0, matrixHeight = 0;
    int excessData = 0, dataPackage = 0;
    int radius = 0;
    vector<vector<float>> localColorMatrix, globalColorMatrix;

    int numberOfProcess, currentRank;;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    if (currentRank == 0) {
        matrixWidth = colorMatrix.size(), matrixHeight = colorMatrix[0].size();
        radius = radiusCore;

        globalColorMatrix.resize(matrixWidth);
        for (int i = 0; i < matrixWidth; ++i)
            globalColorMatrix[i] = vector<float>(matrixHeight);

        int areaWidth = 2 * radius + 1;

        int areaExcess = matrixWidth % areaWidth;
        int areaPackage = matrixWidth / areaWidth;

        excessData = (areaPackage % numberOfProcess) * areaWidth + areaExcess;
        dataPackage = (areaPackage / numberOfProcess) * areaWidth;

        for (int i = 1; i < numberOfProcess; ++i) {
            int initialVector = excessData + (dataPackage * i) - radius;
            int lastVector = excessData + (dataPackage * i) + dataPackage + radius;
            if (lastVector > matrixWidth) lastVector = matrixWidth;
            for (int j = initialVector; j < lastVector; ++j)
                MPI_Send(colorMatrix[j].data(), matrixHeight, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Bcast(&matrixHeight, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&dataPackage, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&radius, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Status status;

    if (currentRank != 0) {
        if (currentRank == numberOfProcess - 1) {
            dataPackage += radius;
        } else {
            dataPackage += 2 * radius;
        }

        localColorMatrix.resize(dataPackage);

        for (int i = 0; i < dataPackage; ++i) {
            localColorMatrix[i] = vector<float>(matrixHeight);
            MPI_Recv(localColorMatrix[i].data(), matrixHeight, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }

        localColorMatrix = singleSmoothingImage(localColorMatrix, radius);

        if (currentRank != numberOfProcess - 1) {
            dataPackage -= radius;
        }

        for (int i = radius; i < dataPackage; ++i)
            MPI_Send(localColorMatrix[i].data(), matrixHeight, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    } else {
        if (numberOfProcess != 1) {
            localColorMatrix = vector<vector<float>>(colorMatrix.begin(), colorMatrix.begin()
                                                            + dataPackage + excessData + radius);
        } else {
            localColorMatrix = vector<vector<float>>(colorMatrix.begin(), colorMatrix.begin()
                                                                     + dataPackage + excessData);
        }

        localColorMatrix = singleSmoothingImage(localColorMatrix, radius);

        for (int i = 0; i < excessData + dataPackage; ++i)
            globalColorMatrix[i] = localColorMatrix[i];

        for (int i = 1; i < numberOfProcess; ++i)
            for (int j = (excessData + dataPackage * i); j < ((excessData + dataPackage * i) + dataPackage); ++j)
                MPI_Recv(globalColorMatrix[j].data(), matrixHeight, MPI_FLOAT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }

    return globalColorMatrix;
}
