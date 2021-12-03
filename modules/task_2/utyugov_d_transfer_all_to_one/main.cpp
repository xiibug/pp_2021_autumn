// Copyright 2021 Utyugov Denis
#include <gtest/gtest.h>
#include <vector>
#include "./transfer_all_to_one.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Int_Sum) {
  std::vector<int> global_vec;
  int count_size_vector = 120;
  int size, rank;
  int sum = 0;
  int global_sum = 0;
  int test_value = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int count_zeros = 0;
  if (count_size_vector % size) {
    count_zeros = size - count_size_vector % size;
    for (int i = 0; i < count_zeros; i++) {
      global_vec.push_back(0);
      count_size_vector++;
    }
  }
  const int delta = count_size_vector / size;

  std::vector<int> proc_el(delta);

  MPI_Scatter(global_vec.data(), delta, MPI_INT, proc_el.data(), delta, MPI_INT,
              0, MPI_COMM_WORLD);

  for (int i = 0; i < delta; i++) {
    sum += proc_el[i];
  }

  MY_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < count_size_vector; i++) {
      test_value += global_vec[i];
    }

    ASSERT_EQ(test_value, global_sum);
  }
}

TEST(Parallel_Operations_MPI, Test_Int_Prod) {
  std::vector<int> global_vec;
  int count_size_vector = 40;
  int size, rank;
  int sum = 1;
  int global_sum = 0;
  int test_value = 1;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int count_zeros = 0;
  if (count_size_vector % size) {
    count_zeros = size - count_size_vector % size;
    for (int i = 0; i < count_zeros; i++) {
      global_vec.push_back(1);
      count_size_vector++;
    }
  }
  const int delta = count_size_vector / size;

  std::vector<int> proc_el(delta);

  MPI_Scatter(global_vec.data(), delta, MPI_INT, proc_el.data(), delta, MPI_INT,
              0, MPI_COMM_WORLD);

  for (int i = 0; i < delta; i++) {
    sum *= proc_el[i];
  }

  MY_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < count_size_vector; i++) {
      test_value *= global_vec[i];
    }

    ASSERT_EQ(test_value, global_sum);
  }
}

TEST(Parallel_Operations_MPI, Test_Float_Sum) {
  std::vector<float> global_vec;
  int count_size_vector = 12;
  int size, rank;
  float sum = 0;
  float global_sum = 0;
  float test_value = 0;
  int test_round = 0;
  int g_round = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    for (int i = 10; i < count_size_vector + 10; i++) {
      global_vec.push_back((static_cast<float>(i)) / 10.0);
    }
  }

  int count_zeros = 0;
  if (count_size_vector % size) {
    count_zeros = size - count_size_vector % size;
    for (int i = 0; i < count_zeros; i++) {
      global_vec.push_back(0.0);
      count_size_vector++;
    }
  }
  const int delta = count_size_vector / size;

  std::vector<float> proc_el(delta);

  MPI_Scatter(global_vec.data(), delta, MPI_FLOAT, proc_el.data(), delta,
              MPI_FLOAT, 0, MPI_COMM_WORLD);

  for (int i = 0; i < delta; i++) {
    sum += proc_el[i];
  }

  MY_Reduce(&sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < count_size_vector; i++) {
      test_value += global_vec[i];
    }
    test_round = test_value;
    g_round = global_sum;

    ASSERT_EQ(test_round, g_round);
  }
}

TEST(Parallel_Operations_MPI, Test_Int_Max) {
  std::vector<int> global_vec;
  int count_size_vector = 40;
  int size, rank;
  int max = 0;
  int global_max = 0;
  int test_value = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int count_zeros = 0;
  if (count_size_vector % size) {
    count_zeros = size - count_size_vector % size;
    for (int i = 0; i < count_zeros; i++) {
      global_vec.push_back(0);
      count_size_vector++;
    }
  }
  const int delta = count_size_vector / size;

  std::vector<int> proc_el(delta);

  MPI_Scatter(global_vec.data(), delta, MPI_INT, proc_el.data(), delta, MPI_INT,
              0, MPI_COMM_WORLD);

  for (int i = 0; i < delta; i++) {
    if (max < proc_el[i]) max = proc_el[i];
  }

  MY_Reduce(&max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < count_size_vector; i++) {
      if (test_value < global_vec[i]) test_value = global_vec[i];
    }

    ASSERT_EQ(test_value, global_max);
  }
}

TEST(Parallel_Operations_MPI, Test_Int_Min) {
  std::vector<int> global_vec;
  int count_size_vector = 10;
  int size, rank;
  int min = 900;
  int global_min = 0;
  int test_value = 900;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    global_vec = getRandomVector(count_size_vector);
  }

  int count_zeros = 0;
  if (count_size_vector % size) {
    count_zeros = size - count_size_vector % size;
    for (int i = 0; i < count_zeros; i++) {
      global_vec.push_back(900);
      count_size_vector++;
    }
  }
  const int delta = count_size_vector / size;

  std::vector<int> proc_el(delta);

  MPI_Scatter(global_vec.data(), delta, MPI_INT, proc_el.data(), delta, MPI_INT,
              0, MPI_COMM_WORLD);

  for (int i = 0; i < delta; i++) {
    if (min > proc_el[i]) min = proc_el[i];
  }

  MY_Reduce(&min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < count_size_vector; i++) {
      if (test_value > global_vec[i]) test_value = global_vec[i];
    }

    ASSERT_EQ(test_value, global_min);
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
