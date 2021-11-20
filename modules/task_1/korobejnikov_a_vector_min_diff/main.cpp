#include <gtest/gtest.h>
#include "vector_min_diff.h"
#include <vector>
#include <gtest-mpi-listener.hpp>


TEST (Parallel_Operations_MPI, Test_Min1) {
    int rank;
 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 120;
    if (rank == 0) {
	    global_vec = getRandomVector(count_size_vector);
    }
    std::pair<int, int> globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
	    std::pair<int, int> reference_min = sequentialCount(global_vec, count_size_vector);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_Min2) {
    int rank;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 120;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    std::pair<int, int> globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        std::pair<int, int> reference_min = sequentialCount(global_vec, count_size_vector);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_Min3) {
    int rank;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int count_size_vector = 120;
    if (rank == 0) {
        global_vec = getRandomVector(count_size_vector);
    }
    std::pair<int, int> globalMin = parallelCount(global_vec, count_size_vector);
    if (rank == 0) {
        std::pair<int, int> reference_min = sequentialCount(global_vec, count_size_vector);
        ASSERT_EQ(globalMin, reference_min);
    }
}

TEST(Parallel_Operations_MPI, Test_Min4) {
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> global_vec;
	const int count_size_vector = 120;
	if (rank == 0) {
		global_vec = getRandomVector(count_size_vector);
	}
	std::pair<int, int> globalMin = parallelCount(global_vec, count_size_vector);
	if (rank == 0) {
		std::pair<int, int> reference_min = sequentialCount(global_vec, count_size_vector);
		ASSERT_EQ(globalMin, reference_min);
	}
}

TEST(Parallel_Operations_MPI, Test_Min5) {
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> global_vec;
	const int count_size_vector = 120;
	if (rank == 0) {
		global_vec = getRandomVector(count_size_vector);
	}
	std::pair<int, int> globalMin = parallelCount(global_vec, count_size_vector);
	if (rank == 0) {
		std::pair<int, int> reference_min = sequentialCount(global_vec, count_size_vector);
		ASSERT_EQ(globalMin, reference_min);
	}
}

TEST(Parallel_Operations_MPI, Test_Min6) {
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> global_vec;
	const int count_size_vector = 120;
	if (rank == 0) {
		global_vec = getRandomVector(count_size_vector);
	}
	std::pair<int, int> globalMin = parallelCount(global_vec, count_size_vector);
	if (rank == 0) {
		std::pair<int, int> reference_min = sequentialCount(global_vec, count_size_vector);
		ASSERT_EQ(globalMin, reference_min);
	}
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv); 
    
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    
    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}

