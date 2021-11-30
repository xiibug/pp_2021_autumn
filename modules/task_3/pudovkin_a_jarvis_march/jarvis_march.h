// Copyright 2021 Pudovkin Artem
#ifndef MODULES_TASK_3_PUDOVKIN_A_JARVIS_MARCH_JARVIS_MARCH_H_
#define MODULES_TASK_3_PUDOVKIN_A_JARVIS_MARCH_JARVIS_MARCH_H_

#include <mpi.h>
#include <vector>

using std::vector;

struct Point2d {
	int x;
	int y;

	Point2d() : x(0), y(0) {}
	Point2d(const int _x, const int _y) : x(_x), y(_y) {}
};

vector<Point2d> getRandomVector(const vector<int>::size_type vectorSize);

vector<Point2d> sequentialJarvisMarch(const vector<Point2d>& vectorOfVertex);
vector<Point2d> parallelJarvisMarch(const vector<Point2d>& vectorOfVertex, vector<int>::size_type vectorSize);

#endif  // MODULES_TASK_3_PUDOVKIN_A_JARVIS_MARCH_JARVIS_MARCH_H_
