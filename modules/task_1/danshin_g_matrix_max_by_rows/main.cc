// Copyright 2021 Gleb "belgad" Danshin
#include <gtest/gtest.h>
#include <cstring>
#include "../../../modules/task_1/danshin_g_matrix_max_by_rows/matrix_max_by_rows.h"
#include <gtest-mpi-listener.hpp>

TEST(DanshinGMatrixMaxByRow, ConstMatrixSize5x5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 5;
        col_num = 5;
        matrix = new int[row_num * col_num] {
            1, 3, 5, 4, 2,
            1, 13, 45, 67, 89,
            -1, 1, -1, 1, -1,
            0, 0, 0, 0, 0,
            -1, -2, -3, -4, -5
        };
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, ConstMatrixSize10x5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 10;
        col_num = 5;
        matrix = new int[row_num * col_num] {
            1, 3, 5, 4, 2,
            1, 13, 45, 67, 89,
            -1, 1, -1, 1, -1,
            0, 0, 0, 0, 0,
            -1, -2, -3, -4, -5,
            -1, 3, -5, 4, -2,
            99, 78, 57, 36, 15,
            2, 2, 2, 2, 6,
            -100000000, 100000000, 0, 0, 0,
            -1000, 1000, -1000, 1000, -2000
        };
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, ConstMatrixSize5x10) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 5;
        col_num = 10;
        matrix = new int[row_num * col_num] {
            1, 3, 5, 4, 2, -1, 3, -5, 4, -2,
            1, 13, 45, 67, 89, 99, 78, 57, 36, 15,
            -1, 1, -1, 1, -1, 2, 2, 2, 2, 6,
            0, 0, 0, 0, 0, -100000000, 100000000, 0, 0, 0,
            -1, -2, -3, -4, -5, -1000, 1000, -1000, 1000, -2000
        };
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, ConstMatrixSize10x10) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 10;
        col_num = 10;
        matrix = new int[row_num * col_num] {
            1, 3, 5, 4, 2, -1, 3, -5, 4, -2,
            1, 13, 45, 67, 89, 99, 78, 57, 36, 15,
            -1, 1, -1, 1, -1, 2, 2, 2, 2, 6,
            0, 0, 0, 0, 0, -100000000, 100000000, 0, 0, 0,
            -1, -2, -3, -4, -5, -1000, 1000, -1000, 1000, -2000,
            -1, 3, -5, 4, -2, 6, -8, 9, -10, 9,
            99, 78, 57, 36, 15, -6, -27, -48, -69, -90,
            2, 2, 2, 2, 6, 6, 6, 6, 2, 2,
            -100000000, 100000000, 0, 0, 0, -100000000, 100000000, -100000000, 100000000, 1000000000,
            -1000, 1000, -1000, 1000, -2000, -1000, 2000, 1000, -2000, 2000
        };
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, RandMatrixSize100x100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 100;
        col_num = 100;
        matrix = GetRandomMatrix(row_num, col_num);
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, RandMatrixSize250x250) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 250;
        col_num = 250;
        matrix = GetRandomMatrix(row_num, col_num);
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, RandMatrixSize250x500) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 250;
        col_num = 500;
        matrix = GetRandomMatrix(row_num, col_num);
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, RandMatrixSize500x250) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 500;
        col_num = 250;
        matrix = GetRandomMatrix(row_num, col_num);
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
}

TEST(DanshinGMatrixMaxByRow, RandMatrixSize500x500) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *matrix = nullptr, row_num = 0, col_num = 0;
    int *answer_sequence = nullptr, *answer_parallel = nullptr;
    if (rank == 0) {
        row_num = 500;
        col_num = 500;
        matrix = GetRandomMatrix(row_num, col_num);
        answer_sequence = GetMatrixRowMaxSequence(matrix, row_num, col_num);
    }
    answer_parallel = GetMatrixRowMaxParallel(matrix, row_num, col_num);
    if (rank == 0) {
        EXPECT_EQ(0, std::memcmp(answer_sequence, answer_parallel, row_num * sizeof(int)));
        delete [] matrix;
        delete [] answer_sequence;
    }
    delete [] answer_parallel;
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
