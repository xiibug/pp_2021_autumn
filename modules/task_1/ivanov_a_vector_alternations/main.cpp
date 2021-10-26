#include "./vector_alternations.h"
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>


TEST(seq_and_par_check_equivalence, two_elems_at_the_borders_vec_size_200)
{
	int procRank = 0;
	const int vecLen = 200;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		std::fill_n(vec, vecLen, 1); vec[0] = vec[vecLen - 1] = -1;
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(seq_and_par_check_equivalence, one_elem_in_the_middle_vec_size_200)
{
	int procRank = 0;
	const int vecLen = 200;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		std::fill_n(vec, vecLen, 1); vec[100] = -1;
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(seq_and_par_check_equivalence, negative_vec_size_200)
{
	int procRank = 0;
	const int vecLen = 200;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		std::fill_n(vec, vecLen, -1);
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(seq_and_par_check_equivalence, positive_vec_size_200)
{
	int procRank = 0;
	const int vecLen = 200;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		std::fill_n(vec, vecLen, 1);
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(seq_and_par_check_equivalence, rng_vec_size_100000)
{
	int procRank = 0;
	const int vecLen = 100000;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		fillVecWithRandValues(vec, vecLen);
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(seq_and_par_check_equivalence, rng_vec_size_110)
{
	int procRank = 0;
	const int vecLen = 110;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		fillVecWithRandValues(vec, vecLen);
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(seq_and_par_check_equivalence, rng_vec_size_11)
{
	int procRank = 0;
	const int vecLen = 11;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		fillVecWithRandValues(vec, vecLen);
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(seq_and_par_check_equivalence, rng_vec_size_8)
{
	int procRank = 0;
	const int vecLen = 8;
	int* vec = nullptr;

	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		vec = new int[vecLen];
		fillVecWithRandValues(vec, vecLen);
	}
	int globalAlternations = parallelCount(vec, vecLen);
	if (procRank == 0)
	{
		int referenceAlternations = sequentialCount_V1(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(referenceAlternations, globalAlternations);
	}
}

TEST(equivalense_of_sequential_count, two_elems_at_the_borders)
{
	int procRank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		const int vecLen = 1000;
		int* vec = new int[vecLen];
		bool ok = true;
		std::fill_n(vec, vecLen, 1);
		vec[0] = vec[vecLen - 1] = -1;
		int sc_v1 = sequentialCount_V1(vec, vecLen);
		int sc_v2 = sequentialCount_V2(vec, vecLen);
		if (sc_v1 != sc_v2 || sc_v1 != 2)
			ok = false;
		delete[] vec;
		ASSERT_TRUE(ok);
	}
}

TEST(equivalense_of_sequential_count, one_elem_in_the_middle)
{
	int procRank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		const int vecLen = 1000;
		int* vec = new int[vecLen];
		bool ok = true;
		std::fill_n(vec, vecLen, 1);
		vec[400] = -1;
		int sc_v1 = sequentialCount_V1(vec, vecLen);
		int sc_v2 = sequentialCount_V2(vec, vecLen);
		if (sc_v1 != sc_v2 || sc_v1 != 2)
			ok = false;
		delete[] vec;
		ASSERT_TRUE(ok);
	}
}

TEST(equivalense_of_sequential_count, on_negative_vect)
{
	int procRank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		const int vecLen = 1000;
		int* vec = new int[vecLen];
		std::fill_n(vec, vecLen, -1);
		int sc_v1 = sequentialCount_V1(vec, vecLen);
		int sc_v2 = sequentialCount_V2(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(sc_v1, sc_v2);
	}
}

TEST(equivalense_of_sequential_count, on_positive_vect)
{
	int procRank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		const int vecLen = 1000;
		int* vec = new int[vecLen];
		std::fill_n(vec, vecLen, 1);
		int sc_v1 = sequentialCount_V1(vec, vecLen);
		int sc_v2 = sequentialCount_V2(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(sc_v1, sc_v2);
	}
}

TEST(equivalense_of_sequential_count, on_rand_vect)
{
	int procRank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		const int vecLen = 1000; 
		int *vec = new int[vecLen];
		fillVecWithRandValues(vec, vecLen);
		int sc_v1 = sequentialCount_V1(vec, vecLen);
		int sc_v2 = sequentialCount_V2(vec, vecLen);
		delete[] vec;
		ASSERT_EQ(sc_v1, sc_v2);
	}
}

TEST(RNG_function_check, does_not_contain_0)
{
	int procRank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		const int vecLen = 1000;
		const int numOfIterations = 10;
		bool ok = true;
		int* vec = new int[vecLen];

		for (int i = 0; i < numOfIterations; i++)
		{
			fillVecWithRandValues(vec, vecLen);
			for (int j = 0; j < vecLen; j++)
			{
				if (vec[j] == 0)
				{
					ok = false;
					break;
				}
			}
			if (!ok) break;
		}
		delete[] vec;
		ASSERT_TRUE(ok);
	}
}

TEST(RNG_function_check, generate_positive_and_negative_numbers)
{
	int procRank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	if (procRank == 0)
	{
		const int vecLen = 30;
		const int numOfIterations = 30;
		bool hasPositive, hasNegative;
		bool ok = true;
		int* vec = new int[vecLen];

		for (int i = 0; i < numOfIterations; i++)
		{
			hasPositive = hasNegative = false;
			fillVecWithRandValues(vec, vecLen);
			for (int j = 0; j < vecLen; j++)
			{
				if (vec[j] > 0) hasPositive = true;
				if (vec[j] < 0) hasNegative = true;
				if (hasPositive && hasNegative)
					break;
			}
			if (!hasPositive || !hasNegative)
				ok = false;
			if (!ok)
				break;
		}
		delete[] vec;
		ASSERT_TRUE(ok);
	}
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	MPI_Init(&argc, &argv); // check for MPI_SUCCESS?

	::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
	::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
	
	listeners.Release(listeners.default_result_printer());
	listeners.Release(listeners.default_xml_generator());

	listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
	return RUN_ALL_TESTS();
}
