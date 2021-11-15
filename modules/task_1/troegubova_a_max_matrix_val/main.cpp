// Copyright 2021 Troegubova Alexandra
#include <gtest/gtest.h>
#include <vector>
#include "./max_matrix_val.h"
#include <gtest-mpi-listener.hpp>

TEST(parallel_max_MPI, correct_finding_of_the_maximum_in_a_matrix_with_dimension_3x2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> matrix;
    const int lines = 3;
	const int columns = 2;

    if (rank == 0) {
        matrix = getRandomMatrix(lines, columns);
    }

    int global_max = getParallelMax(matrix, lines * columns);

    if (rank == 0) {
        int reference_max = getSequentialMax(matrix);
        ASSERT_EQ(reference_max, global_max);
    }
}

TEST(parallel_max_MPI, correct_finding_of_the_maximum_in_a_matrix_with_dimension_100x100) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> matrix;
	const int lines = 100;
	const int columns = 100;

	if (rank == 0) {
		matrix = getRandomMatrix(lines, columns);
	}

	int global_max = getParallelMax(matrix, lines * columns);

	if (rank == 0) {
		int reference_max = getSequentialMax(matrix);
		ASSERT_EQ(reference_max, global_max);
	}
}

TEST(parallel_max_MPI, correct_finding_of_the_maximum_in_a_matrix_with_dimension_1x150) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> matrix;
	const int lines = 1;
	const int columns = 150;

	if (rank == 0) {
		matrix = getRandomMatrix(lines, columns);
	}

	int global_max = getParallelMax(matrix, lines * columns);

	if (rank == 0) {
		int reference_max = getSequentialMax(matrix);
		ASSERT_EQ(reference_max, global_max);
	}
}

TEST(parallel_max_MPI, correct_finding_of_the_maximum_in_a_matrix_with_dimension_150x1) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> matrix;
	const int lines = 150;
	const int columns = 1;

	if (rank == 0) {
		matrix = getRandomMatrix(lines, columns);
	}

	int global_max = getParallelMax(matrix, lines * columns);

	if (rank == 0) {
		int reference_max = getSequentialMax(matrix);
		ASSERT_EQ(reference_max, global_max);
	}
}

TEST(parallel_max_MPI, correct_finding_of_the_maximum_in_a_matrix_with_dimension_3x200_test_1) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> matrix;
	const int lines = 3;
	const int columns = 200;

	if (rank == 0) {
		matrix = getRandomMatrix(lines, columns);
	}

	int global_max = getParallelMax(matrix, lines * columns);

	if (rank == 0) {
		int reference_max = getSequentialMax(matrix);
		ASSERT_EQ(reference_max, global_max);
	}
}

TEST(parallel_max_MPI, correct_finding_of_the_maximum_in_a_matrix_with_dimension_3x200_test_2) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> matrix;
	const int lines = 3;
	const int columns = 200;
	int matrix_size = lines * columns;

	if (rank == 0) {
		for (int i = 0; i < matrix_size; i++)
			matrix.push_back(i % 2);
	}

	int global_max = getParallelMax(matrix, lines * columns);

	if (rank == 0) {
		ASSERT_EQ(1, global_max);
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
