// Copyright 2021 Pudovkin Artem
#include <gtest/gtest.h>
#include <vector>
#include "./jarvis_march.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Jarvis_March, Vertex_Equal_100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<Point2d> global_vector;
    const vector<int>::size_type size = 100;

    if (rank == 0) {
        global_vector = getRandomVector(size);
    }

    vector<Point2d> global_curve = parallelJarvisMarch(global_vector, size);

    if (rank == 0) {
        vector<Point2d> reference_curve = sequentialJarvisMarch(global_vector);

        ASSERT_EQ(global_curve.size(), reference_curve.size());
        for (vector<int>::size_type i = 0; i < global_curve.size(); ++i) {
            ASSERT_EQ(global_curve[i].x, reference_curve[i].x);
            ASSERT_EQ(global_curve[i].y, reference_curve[i].y);
        }
    }
}

TEST(Parallel_Jarvis_March, Vertex_Equal_150) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<Point2d> global_vector;
    const vector<int>::size_type size = 150;

    if (rank == 0) {
        global_vector = getRandomVector(size);
    }

    vector<Point2d> global_curve = parallelJarvisMarch(global_vector, size);

    if (rank == 0) {
        vector<Point2d> reference_curve = sequentialJarvisMarch(global_vector);

        ASSERT_EQ(global_curve.size(), reference_curve.size());
        for (vector<int>::size_type i = 0; i < global_curve.size(); ++i) {
            ASSERT_EQ(global_curve[i].x, reference_curve[i].x);
            ASSERT_EQ(global_curve[i].y, reference_curve[i].y);
        }
    }
}

TEST(Parallel_Jarvis_March, Vertex_Equal_200) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<Point2d> global_vector;
    const vector<int>::size_type size = 200;

    if (rank == 0) {
        global_vector = getRandomVector(size);
    }

    vector<Point2d> global_curve = parallelJarvisMarch(global_vector, size);

    if (rank == 0) {
        vector<Point2d> reference_curve = sequentialJarvisMarch(global_vector);

        ASSERT_EQ(global_curve.size(), reference_curve.size());
        for (vector<int>::size_type i = 0; i < global_curve.size(); ++i) {
            ASSERT_EQ(global_curve[i].x, reference_curve[i].x);
            ASSERT_EQ(global_curve[i].y, reference_curve[i].y);
        }
    }
}

TEST(Parallel_Jarvis_March, Vertex_Equal_250) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<Point2d> global_vector;
    const vector<int>::size_type size = 250;

    if (rank == 0) {
        global_vector = getRandomVector(size);
    }

    vector<Point2d> global_curve = parallelJarvisMarch(global_vector, size);

    if (rank == 0) {
        vector<Point2d> reference_curve = sequentialJarvisMarch(global_vector);

        ASSERT_EQ(global_curve.size(), reference_curve.size());
        for (vector<int>::size_type i = 0; i < global_curve.size(); ++i) {
            ASSERT_EQ(global_curve[i].x, reference_curve[i].x);
            ASSERT_EQ(global_curve[i].y, reference_curve[i].y);
        }
    }
}

TEST(Parallel_Jarvis_March, Vertex_Equal_300) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<Point2d> global_vector;
    const vector<int>::size_type size = 300;

    if (rank == 0) {
        global_vector = getRandomVector(size);
    }

    vector<Point2d> global_curve = parallelJarvisMarch(global_vector, size);

    if (rank == 0) {
        vector<Point2d> reference_curve = sequentialJarvisMarch(global_vector);

        ASSERT_EQ(global_curve.size(), reference_curve.size());
        for (vector<int>::size_type i = 0; i < global_curve.size(); ++i) {
            ASSERT_EQ(global_curve[i].x, reference_curve[i].x);
            ASSERT_EQ(global_curve[i].y, reference_curve[i].y);
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
