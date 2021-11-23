// Copyright 2021 Kim Nikita
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include "./reduce.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Reduce_INT_MAX) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<int> input_vec;
  std::vector<int> res_vec_1;
  std::vector<int> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<int>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<int> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_INT, local_vec.data(), range, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (res_vec_1[i] != res_vec_2[i])
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_INT_MIN) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<int> input_vec;
  std::vector<int> res_vec_1;
  std::vector<int> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<int>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<int> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_INT, local_vec.data(), range, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_INT, MPI_MIN, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_INT, MPI_MIN, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (res_vec_1[i] != res_vec_2[i])
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_INT_SUM) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<int> input_vec;
  std::vector<int> res_vec_1;
  std::vector<int> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<int>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<int> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_INT, local_vec.data(), range, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (res_vec_1[i] != res_vec_2[i])
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_INT_PROD) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<int> input_vec;
  std::vector<int> res_vec_1;
  std::vector<int> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<int>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<int> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_INT, local_vec.data(), range, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_INT, MPI_PROD, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_INT, MPI_PROD, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (res_vec_1[i] != res_vec_2[i])
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_FLOAT_MAX) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<float> input_vec;
  std::vector<float> res_vec_1;
  std::vector<float> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<float>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<float> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_FLOAT, local_vec.data(), range, MPI_FLOAT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_FLOAT, MPI_MAX, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_FLOAT, MPI_MAX, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_FLOAT_MIN) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<float> input_vec;
  std::vector<float> res_vec_1;
  std::vector<float> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<float>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<float> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_FLOAT, local_vec.data(), range, MPI_FLOAT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_FLOAT, MPI_MIN, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_FLOAT, MPI_MIN, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_FLOAT_SUM) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<float> input_vec;
  std::vector<float> res_vec_1;
  std::vector<float> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<float>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<float> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_FLOAT, local_vec.data(), range, MPI_FLOAT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_FLOAT_PROD) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<float> input_vec;
  std::vector<float> res_vec_1;
  std::vector<float> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<float>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<float> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_FLOAT, local_vec.data(), range, MPI_FLOAT, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_FLOAT, MPI_PROD, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_FLOAT, MPI_PROD, root, MPI_COMM_WORLD);

  // res_vec_1[i] && res_vec_2[i] sometimes equal to x.ye+18 - x.ye+30 and more
  // so, i use assert_float_eq instead assert_lt (time is good on other tests => good at this)
  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_FLOAT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_DOUBLE_MAX) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<double> input_vec;
  std::vector<double> res_vec_1;
  std::vector<double> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<double>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<double> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_DOUBLE, local_vec.data(), range, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_DOUBLE_MIN) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<double> input_vec;
  std::vector<double> res_vec_1;
  std::vector<double> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<double>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<double> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_DOUBLE, local_vec.data(), range, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_DOUBLE, MPI_MIN, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_DOUBLE, MPI_MIN, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_DOUBLE_SUM) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<double> input_vec;
  std::vector<double> res_vec_1;
  std::vector<double> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<double>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<double> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_DOUBLE, local_vec.data(), range, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

TEST(Parallel_Operations_MPI, Test_Reduce_DOUBLE_PROD) {
  int rank, proc_num, root;
  double time_1, time_2;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  std::vector<double> input_vec;
  std::vector<double> res_vec_1;
  std::vector<double> res_vec_2;

  if (rank == 0) {
    input_vec = getRandomVector<double>(20);
    std::random_device dev;
    std::mt19937 gen(dev());
    root = gen() % proc_num;
  }
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // range == const for all processes
  // even if 20 % proc_num != 0
  int range = 20 / proc_num;
  std::vector<double> local_vec(range);
  MPI_Scatter(input_vec.data(), range, MPI_DOUBLE, local_vec.data(), range, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == root) {
    res_vec_1.reserve(range);
    res_vec_2.reserve(range);
    time_1 = MPI_Wtime();
  }

  Reduce(local_vec.data(), res_vec_1.data(), range, MPI_DOUBLE, MPI_PROD, root, MPI_COMM_WORLD);

  if (rank == root) {
    time_1 = MPI_Wtime() - time_1;
    time_2 = MPI_Wtime();
  }

  MPI_Reduce(local_vec.data(), res_vec_2.data(), range, MPI_DOUBLE, MPI_PROD, root, MPI_COMM_WORLD);

  // res_vec_1[i] && res_vec_2[i] sometimes equal to x.ye+18 - x.ye+30 and more
  // so, i use assert_double_eq instead assert_lt (time is good on other tests => good at this)
  if (rank == root) {
    time_2 = MPI_Wtime() - time_2;
    for (int i = 0; i < range; i++)
      if (abs(res_vec_1[i] - res_vec_2[i]) > 1e-10)
        ASSERT_DOUBLE_EQ(res_vec_2[i], res_vec_1[i]);
    ASSERT_LT(abs(time_2 - time_1), 1);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners &listeners = ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
