// Copyright 2021 Pudovkin Artem
#include <gtest/gtest.h>
#include <vector>
#include "./allreduce.h"
#include <gtest-mpi-listener.hpp>

TEST(Check_Allreduce, Allreduce_Max_Int_Vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_vector;
    const vector<int>::size_type size = 100;

    if (rank == 0) {
        global_vector = getRandomVector<int>(size);
    }

    int global_max = parallelMax<int>(global_vector, size);

    if (rank == 0) {
        int reference_max = maxVector<int>(global_vector);
        ASSERT_EQ(global_max, reference_max);
    }
}

TEST(Check_Allreduce, Allreduce_Min_Int_Vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_vector;
    const vector<int>::size_type size = 100;

    if (rank == 0) {
        global_vector = getRandomVector<int>(size);
    }

    int global_min = parallelMin<int>(global_vector, size);

    if (rank == 0) {
        int reference_min = minVector<int>(global_vector);
        ASSERT_EQ(global_min, reference_min);
    }
}

TEST(Check_Allreduce, Allreduce_Sum_Int_Vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> global_vector;
    const vector<int>::size_type size = 100;

    if (rank == 0) {
        global_vector = getRandomVector<int>(size);
    }

    int global_sum = parallelSum<int>(global_vector, size);

    if (rank == 0) {
        int reference_sum = sumVector<int>(global_vector);
        ASSERT_EQ(global_sum, reference_sum);
    }
}

TEST(Check_Allreduce, Allreduce_Max_Float_Vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<float> global_vector;
    const vector<float>::size_type size = 100;

    if (rank == 0) {
        global_vector = getRandomVector<float>(size);
    }

    float global_max = parallelMax<float>(global_vector, size);

    if (rank == 0) {
        float reference_max = maxVector<float>(global_vector);
        ASSERT_EQ(global_max, reference_max);
    }
}

TEST(Check_Allreduce, Allreduce_Min_Double_Vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<double> global_vector;
    const vector<double>::size_type size = 100;

    if (rank == 0) {
        global_vector = getRandomVector<double>(size);
    }

    double global_min = parallelMin<double>(global_vector, size);

    if (rank == 0) {
        double reference_min = minVector<double>(global_vector);
        ASSERT_EQ(global_min, reference_min);
    }
}

TEST(Check_Allreduce, allreduce_ints) {
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 3)
        return;

    vector<int> result = { 3, 6, -7, 12 };
    vector<int> recv{ 0, 0, 0, 0 };
    vector<int> local{ 0, 0, 0, 0 };
    const vector<int>::size_type sizeVec = 4;

    if (rank == 0) {
        local = { 1, 2, 3, 4 };
    }
    if (rank == 1) {
        local = { 0, 2, 0, 4 };
    }
    if (rank == 2) {
        local = { 2, 2, -10, 4 };
    }

    Allreduce(local.data(), recv.data(), sizeVec, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    ASSERT_EQ(result, recv);
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
