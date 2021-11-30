// Copyright 2021 Pudovkin Artem
#include <mpi.h>
#include <stddef.h>
#include <random>
#include <algorithm>
#include <numeric>
#include "../../../modules/task_3/pudovkin_a_jarvis_march/jarvis_march.h"

int findRotate(const Point2d& firstVertex, const Point2d& secondVertex, const Point2d& thirdVertex) {
    return (secondVertex.x - firstVertex.x) * (thirdVertex.y - secondVertex.y)
        - (secondVertex.y - firstVertex.y) * (thirdVertex.x - secondVertex.x);
}
void initializeStructPoint2d(MPI_Datatype* structPoint2d) {
    int lenght[3] = { 1, 1, 1 };
    MPI_Aint position[3] = { offsetof(Point2d, x), offsetof(Point2d, y), sizeof(Point2d) };
    MPI_Datatype type[3] = { MPI_INT, MPI_INT, MPI_UB };

    MPI_Type_create_struct(3, lenght, position, type, structPoint2d);
    MPI_Type_commit(structPoint2d);
}

vector<Point2d> getRandomVector(const vector<int>::size_type vectorSize) {
    std::random_device dev;
    std::mt19937 gen(dev());

    vector<Point2d> vectorOfVertex(vectorSize);
    for (vector<int>::size_type i = 0; i < vectorSize; i++) {
        vectorOfVertex[i] = Point2d(gen() % 10000, gen() % 10000);
    }

    return vectorOfVertex;
}

vector<Point2d> sequentialJarvisMarch(const vector<Point2d>& vectorOfVertex) {
    vector<int> vectorOfIndex(vectorOfVertex.size());
    std::iota(vectorOfIndex.begin(), vectorOfIndex.end(), 0);

    for (vector<int>::size_type i = 1; i < vectorOfVertex.size(); ++i) {
        if (vectorOfVertex[vectorOfIndex[i]].x < vectorOfVertex[vectorOfIndex[0]].x) {
            std::swap(vectorOfIndex[i], vectorOfIndex[0]);
        }
    }

    vector<int> curveH = { vectorOfIndex[0] };
    vectorOfIndex.erase(vectorOfIndex.begin());
    vectorOfIndex.push_back(curveH[0]);

    while (true) {
        int right = 0;
        for (vector<int>::size_type i = 1; i < vectorOfIndex.size(); i++) {
            if (findRotate(vectorOfVertex[curveH[curveH.size() - 1]],
                vectorOfVertex[vectorOfIndex[right]],
                vectorOfVertex[vectorOfIndex[i]]) < 0) {
                right = i;
            }
        }
        if (vectorOfIndex[right] == curveH[0]) {
            break;
        } else {
            curveH.push_back(vectorOfIndex[right]);
            vectorOfIndex.erase(vectorOfIndex.begin() + right);
        }
    }

    vector<Point2d> curveVertex(curveH.size());
    for (vector<int>::size_type i = 0; i < curveH.size(); i++) {
        curveVertex[i] = vectorOfVertex[curveH[i]];
    }

    return curveVertex;
}
vector<Point2d> parallelJarvisMarch(const vector<Point2d>& vectorOfVertex, vector<int>::size_type vectorSize) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Datatype structPoint2d;
    initializeStructPoint2d(&structPoint2d);

    int delta = vectorSize / size;

    vector<Point2d> localVectorOfVertex(delta);
    vector<Point2d> localJarvisMarch, globalJarvisMarch;

    MPI_Scatter(vectorOfVertex.data(), delta, structPoint2d, localVectorOfVertex.data(), delta,
        structPoint2d, 0, MPI_COMM_WORLD);
    localJarvisMarch = sequentialJarvisMarch(localVectorOfVertex);

    if (rank != 0) {
        MPI_Send(localJarvisMarch.data(), localJarvisMarch.size(), structPoint2d, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Status status;
            int sendElements = 0;
            MPI_Probe(i, 0, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, structPoint2d, &sendElements);

            vector<int>::size_type oldSize = localJarvisMarch.size();
            localJarvisMarch.resize(oldSize + sendElements);
            MPI_Recv(localJarvisMarch.data() + oldSize, sendElements, structPoint2d, i, 0,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (size != 1) {
            int tail = vectorSize - size * delta;
            if (tail) {
                localVectorOfVertex = vector<Point2d>(vectorOfVertex.begin() +
                    (vectorSize - tail), vectorOfVertex.end());
                globalJarvisMarch = sequentialJarvisMarch(localVectorOfVertex);

                vector<int>::size_type oldSize = localJarvisMarch.size();
                localJarvisMarch.resize(oldSize + globalJarvisMarch.size());
                for (vector<int>::size_type i = oldSize, j = 0; i < localJarvisMarch.size(); i++, j++) {
                    localJarvisMarch[i] = globalJarvisMarch[j];
                }
            }
        }
        globalJarvisMarch = sequentialJarvisMarch(localJarvisMarch);
    }

    return globalJarvisMarch;
}
