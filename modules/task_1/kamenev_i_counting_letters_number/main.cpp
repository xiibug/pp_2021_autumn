// Copyright 2021 Kamenev Ilya

#include <gtest/gtest.h>
#include "../../../modules/task_1/kamenev_i_counting_letters_number/counting_letters_number.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Empty_Random_Str) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string str;
  const int str_size = 0;
  if (rank == 0) {
    str = CreateRandomStr(str_size);
  }
  int par_result = CountingLettersParallel(str);
  if (rank == 0) {
    int expected_result = 0;
    ASSERT_EQ(expected_result, par_result);
  }
}

TEST(Parallel_Operations_MPI, Test_Only_Letters_20) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string str;
  const int str_size = 20;
  if (rank == 0) {
    str = CreateOnlyLettersStr(str_size);
    std::cout << str;
  }
  int par_result = CountingLettersParallel(str);
  if (rank == 0) {
    int expected_result = CountingLettersSequential(str);
    ASSERT_EQ(expected_result, par_result);
  }
}

TEST(Parallel_Operations_MPI, Test_Random_Str_20) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string str;
  const int str_size = 20;
  if (rank == 0) {
    str = CreateRandomStr(str_size);
    std::cout << str;
  }
  int par_result = CountingLettersParallel(str);
  if (rank == 0) {
    int expected_result = CountingLettersSequential(str);
    ASSERT_EQ(expected_result, par_result);
  }
}

TEST(Parallel_Operations_MPI, Test_Empty_Str_Only_Letters) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string str;
  const int str_size = 0;
  if (rank == 0) {
    str = CreateOnlyLettersStr(str_size);
  }
  int par_result = CountingLettersParallel(str);
  if (rank == 0) {
    int seq_result = CountingLettersSequential(str);
    ASSERT_EQ(seq_result, par_result);
  }
}

TEST(Parallel_Operations_MPI, Test_No_Letters_Str) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string str;
  if (rank == 0) {
    str = "$%##4235!8*15%79)-7$}=";
  }
  int result = CountingLettersParallel(str);
  if (rank == 0) {
    int expected_result = 0;
    ASSERT_EQ(expected_result, result);
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
