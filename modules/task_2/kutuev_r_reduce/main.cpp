// Copyright 2021 Kutuev Roman

#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "../../../modules/task_2/kutuev_r_reduce/reduce.h"

TEST(ReduceTest, MPI_SUM_INT) {
  int ProcNum, ProcRank;
  int Reduce, my_result = 0;
  double t1, t2, t3, t4;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  int value = ProcNum * (ProcNum + 100) - ProcRank;
  t1 = MPI_Wtime();
  MPI_Reduce(&value, &Reduce, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
  }
  t3 = MPI_Wtime();
  my_reduce(&value, &my_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t4 = MPI_Wtime();
    printf("Reduce: %lf\n", t2 - t1);
    fflush(stdout);
    printf("my reduce: %lf\n", t4 - t3);
    fflush(stdout);
    ASSERT_EQ(Reduce, my_result);
  }
}

TEST(ReduceTest, MPI_MAX_INT) {
  int ProcNum, ProcRank;
  int Reduce, reduce = -2147483647;
  double t1, t2, t3, t4;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  int value = ProcNum * (ProcNum + 100) - ProcRank;
  t1 = MPI_Wtime();
  MPI_Reduce(&value, &Reduce, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
  }
  t3 = MPI_Wtime();
  my_reduce(&value, &reduce, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t4 = MPI_Wtime();
    printf("Reduce: %lf\n", t2 - t1);
    fflush(stdout);
    printf("my reduce: %lf\n", t4 - t3);
    fflush(stdout);
    ASSERT_EQ(reduce, Reduce);
  }
}

TEST(ReduceTest, MPI_MIN_INT) {
  int ProcNum, ProcRank;
  int Reduce, reduce = 2147483647;
  double t1, t2, t3, t4;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  int value = ProcNum * (ProcNum + 100) - ProcRank;
  t1 = MPI_Wtime();
  MPI_Reduce(&value, &Reduce, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
  }
  t3 = MPI_Wtime();
  my_reduce(&value, &reduce, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t4 = MPI_Wtime();
    printf("Reduce: %lf\n", t2 - t1);
    fflush(stdout);
    printf("my reduce: %lf\n", t4 - t3);
    fflush(stdout);
    ASSERT_EQ(reduce, Reduce);
  }
}

TEST(ReduceTest, MPI_PROD_INT) {
  int ProcNum, ProcRank;
  int Reduce, reduce = 1;
  double t1, t2, t3, t4;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  int value = ProcNum * (ProcNum + 100) - ProcRank;
  t1 = MPI_Wtime();
  MPI_Reduce(&value, &Reduce, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
  }
  t3 = MPI_Wtime();
  my_reduce(&value, &reduce, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t4 = MPI_Wtime();
    printf("Reduce: %lf\n", t2 - t1);
    fflush(stdout);
    printf("my reduce: %lf\n", t4 - t3);
    fflush(stdout);
    ASSERT_EQ(reduce, Reduce);
  }
}

TEST(ReduceTest, MPI_SUM_INT_VEC) {
  int ProcNum, ProcRank;
  int count = 17;
  int* Reduce = new int[count];
  int* reduce = new int[count];
  int* value = new int[count];
  double t1, t2, t3, t4;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  for (int i = 0; i < count; i++) {
    reduce[i] = 0;
  }
  for (int i = 0; i < count; i++) {
    value[i] = i * (ProcNum + 100) - ProcRank;
  }
  t1 = MPI_Wtime();
  MPI_Reduce(value, Reduce, count, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
  }
  t3 = MPI_Wtime();
  my_reduce(value, reduce, count, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if (ProcRank == 0) {
    t4 = MPI_Wtime();
    printf("Reduce: %lf\n", t2 - t1);
    fflush(stdout);
    printf("my reduce: %lf\n", t4 - t3);
    fflush(stdout);
    for (int i = 0; i < count; i++) {
      ASSERT_EQ(Reduce[i], reduce[i]);
    }
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
