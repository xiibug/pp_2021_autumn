// Copyright 2021 Burdukov Mikhail
#include <gtest/gtest.h>
#include <numeric>
#include "./scalar_multiplication.hpp"
#include <gtest-mpi-listener.hpp>


TEST(scalar_muliplication  ,  simple_test)  {
  int prank = 0;
  const int size = 8;
  std::vector<int> first  ,  second;
  MPI_Comm_rank(MPI_COMM_WORLD   ,  &prank);
  if (prank == 0) {
    first = std::vector<int>(size  , 1);
    second = std::vector<int>(size  , 1);
  }
  int answer = scalar_muliply(first  , second  , size);
  if (prank == 0) {
    int right_ans = 8;
    ASSERT_EQ(right_ans  , answer);
  }
}




TEST(scalar_muliplication  , simple_random_vectors) {
  int prank = 0;
  const int size = 100;
  std::vector<int> first  , second;
  MPI_Comm_rank(MPI_COMM_WORLD  ,  &prank);
  if (prank == 0) {
    first = generate_random_vector(size);
    second = generate_random_vector(size);
  }
  int answer = scalar_muliply(first  , second  , size);
  if (prank == 0) {
    int right_ans = non_parallel_scalar_muliply(first  , second  , size);
    ASSERT_EQ(right_ans  , answer);
  }
}


TEST(scalar_muliplication , simple_with_zero) {
  int prank = 0 , pcount;
  int size = 12;
  std::vector<int> first , second;
  MPI_Comm_rank(MPI_COMM_WORLD ,  &prank);
  MPI_Comm_size(MPI_COMM_WORLD ,  &pcount);
  if (prank == 0) {
    first = std::vector<int>(size , 0);
    second = std::vector<int>(size , 1);
  }
  int answer = scalar_muliply(first , second , size);
  if (prank == 0) {
    int right_ans = non_parallel_scalar_muliply(first , second , size);
    ASSERT_EQ(right_ans , answer);
  }
}

TEST(scalar_muliplication , prime_size) {
  int prank = 0;
  const int size = 4483;
  std::vector<int> first , second;
  MPI_Comm_rank(MPI_COMM_WORLD ,  &prank);
  if (prank == 0) {
    first = generate_random_vector(size);
    second = generate_random_vector(size);
  }
  int answer = scalar_muliply(first , second , size);
  if (prank == 0) {
      int right_ans = non_parallel_scalar_muliply(first , second , size);
      ASSERT_EQ(right_ans , answer);
  }
}

TEST(scalar_muliplication , stress_test) {
  std::random_device dev;
  std::mt19937 gen(dev());
  int pcount = 0;
  MPI_Comm_size(MPI_COMM_WORLD ,  &pcount);
  for (int it = pcount+1 ; it < 1000 ; it++) {
        int prank = 0;
    const int size = it;
    std::vector<int> first , second;
    MPI_Comm_rank(MPI_COMM_WORLD ,  &prank);
    if (prank == 0) {
      first = generate_random_vector(size);
      second = generate_random_vector(size);
    }
    int answer = scalar_muliply(first , second , size);
    if (prank == 0) {
        int right_ans = non_parallel_scalar_muliply(first , second , size);
        if (right_ans != answer) {
          ASSERT_FALSE(1);
        }
    }
  }
}



int main(int argc ,  char** argv) {
  ::testing::InitGoogleTest(&argc ,  argv);
  if (MPI_SUCCESS !=MPI_Init(&argc ,  &argv)) {
    std::cout << "init error" << std::endl;
    exit(0);
  }
  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
           ::testing::UnitTest::GetInstance()->listeners();
  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());
  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
