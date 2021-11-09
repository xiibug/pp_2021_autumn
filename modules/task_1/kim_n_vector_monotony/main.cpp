// Copyright 2021 Kim Nikita
#include <gtest/gtest.h>
#include <vector>
#include "./vector_monotony.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Vec_Even_Size_Increase)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> input_vec;

  if (rank == 0)
    input_vec = getRandomVector(20);

  int res = getNumNonMonotonyElemsParall(input_vec, 20, 1);

  if (rank == 0)
  {
    int exp_res = getNumNonMonotonyElems(input_vec, 20, 1);
    ASSERT_EQ(exp_res, res);
  }
}

TEST(Parallel_Operations_MPI, Test_Vec_Even_Size_Decrease)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> input_vec;

  if (rank == 0)
    input_vec = getRandomVector(20);

  int res = getNumNonMonotonyElemsParall(input_vec, 20, -1);

  if (rank == 0)
  {
    int exp_res = getNumNonMonotonyElems(input_vec, 20, -1);
    ASSERT_EQ(exp_res, res);
  }
}

TEST(Parallel_Operations_MPI, Test_Vec_Odd_Size_Increase)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> input_vec;

  if (rank == 0)
    input_vec = getRandomVector(19);

  int res = getNumNonMonotonyElemsParall(input_vec, 19, 1);

  if (rank == 0)
  {
    int exp_res = getNumNonMonotonyElems(input_vec, 19, 1);
    ASSERT_EQ(exp_res, res);
  }
}

TEST(Parallel_Operations_MPI, Test_Vec_Odd_Size_Decrease)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> input_vec;

  if (rank == 0)
    input_vec = getRandomVector(19);

  int res = getNumNonMonotonyElemsParall(input_vec, 19, -1);

  if (rank == 0)
  {
    int exp_res = getNumNonMonotonyElems(input_vec, 19, -1);
    ASSERT_EQ(exp_res, res);
  }
}

TEST(Parallel_Operations_MPI, Test_Vec_Zero_Size)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> input_vec;

  if (rank == 0)
    input_vec = getRandomVector(0);

  int res = getNumNonMonotonyElemsParall(input_vec, 0, 1);

  if (rank == 0)
  {
    int exp_res = 0;
    ASSERT_EQ(exp_res, res);
  }
}

TEST(Parallel_Operations_MPI, Test_Vec_Size_1)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> input_vec;

  if (rank == 0)
    input_vec = getRandomVector(1);

  int res = getNumNonMonotonyElemsParall(input_vec, 1, 1);

  if (rank == 0)
  {
    int exp_res = 0;
    ASSERT_EQ(exp_res, res);
  }
}

TEST(Parallel_Operations_MPI, Test_Vec_Size_2)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> input_vec;

  if (rank == 0)
    input_vec = getRandomVector(2);

  int res = getNumNonMonotonyElemsParall(input_vec, 2, 1);

  if (rank == 0)
  {
    int exp_res = getNumNonMonotonyElems(input_vec, 2, 1);;
    ASSERT_EQ(exp_res, res);
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
