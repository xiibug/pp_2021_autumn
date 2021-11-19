// Copyright 2021 Ermakov Pavel

#include "./letters_count.h"

TEST(Parallel_Operations_MPI, str_lenght_eq_zero) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::string s;
	const int size_of_s = 0;

	if (rank == 0)
		s = random_str_gen(size_of_s);

	int num_of_letters_in_s = letters_count_par(s);
	if (rank == 0) {
		int res = 0;
		ASSERT_EQ(res, num_of_letters_in_s);
	}
}

TEST(Parallel_Operations_MPI, str_with_33_letters) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::string s;
	s = "The qUick bR34own fox ju26mps over a la!|1337|zy doG.";
	int num_of_letters_in_s = letters_count_par(s);
	int res = 33;

	if (rank == 0) {
		ASSERT_EQ(res, num_of_letters_in_s);
	}

}
TEST(Parallel_Operations_MPI, rand_str_64_char) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::string s;
	const int size_of_s = 64;
	if (rank == 0)
		s = random_str_gen(size_of_s);

	int num_of_letters_in_s_par = letters_count_par(s);
	if (rank == 0) {
		int num_of_letters_in_s_seq = letters_count_seq(s);
		ASSERT_EQ(num_of_letters_in_s_seq, num_of_letters_in_s_par);
	}
}

TEST(Parallel_Operations_MPI, every1_letter_is_S_64_char) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int size_of_s = 64;
	std::string s(size_of_s, '\n');
	for (int i = 0; i < size_of_s; i++)
		s[i] = 'S';
	int num_of_letters_in_s_par = letters_count_par(s);
	if (rank == 0) {

		int num_of_letters_in_s_seq = letters_count_seq(s);
		ASSERT_EQ(num_of_letters_in_s_seq, num_of_letters_in_s_par);
	}
}

TEST(Parallel_Operations_MPI, no_letters_at_all) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::string s;
	if (rank == 0)
		s = "123!@)=|%^&*";

	int num_of_letters_in_s = letters_count_par(s);
	if (rank == 0) {
		int res = 0;
		ASSERT_EQ(res, num_of_letters_in_s);
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