// Copyright 2021 Zaitseva Ksenia
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "DiningPhilosophers.h"

TEST(DiningPhilosophers, one_run) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int runs = 1;

  DiningPholisophers(rank, size, runs);

  MPI_Barrier(MPI_COMM_WORLD);

  ASSERT_NO_THROW();
}

TEST(DiningPhilosophers, two_run) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int runs = 2;

  DiningPholisophers(rank, size, runs);

  MPI_Barrier(MPI_COMM_WORLD);

  ASSERT_NO_THROW();
}

TEST(DiningPhilosophers, five_run) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int runs = 5;

  DiningPholisophers(rank, size, runs);

  MPI_Barrier(MPI_COMM_WORLD);

  ASSERT_NO_THROW();
}

TEST(DiningPhilosophers, ten_run) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int runs = 10;

  DiningPholisophers(rank, size, runs);

  MPI_Barrier(MPI_COMM_WORLD);

  ASSERT_NO_THROW();
}

TEST(DiningPhilosophers, ten_fifty) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int runs = 25;

  DiningPholisophers(rank, size, runs);

  MPI_Barrier(MPI_COMM_WORLD);

  ASSERT_NO_THROW();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  std::srand(std::time(nullptr));

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
