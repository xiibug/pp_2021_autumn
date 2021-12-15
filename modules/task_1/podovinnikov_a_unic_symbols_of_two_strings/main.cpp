// Copyright 2021 Podovinnikov Artyom
#include <gtest/gtest.h>
#include <mpi.h>

#include <gtest-mpi-listener.hpp>



#include "../../../modules/task_1/podovinnikov_a_unic_symbols_of_two_strings/unic_symbols_of_two_strings.h"

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

int len = 5;

TEST(MPIunicSymbols, identical) {
  int procRank = 0;
  char* string1 = "qwerty";
  char* string2 = "qwerty";

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  int result = Mpi_compare(string1, string2, 6);
  if (procRank == 0) {
    EXPECT_EQ(result, 0);
  }
}

TEST(MPIunicSymbols, space) {
  int procRank = 0;
  char* string1 = " ";
  char* string2 = " ";

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  int result = Mpi_compare(string1, string2, 1);
  if (procRank == 0) {
    EXPECT_EQ(result, 0);
  }
}

TEST(MPIunicSymbols, FirstLonger) {
  int procRank = 0;
  char* string1 = "qwe";
  char* string2 = "qwerty";

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  int result = Mpi_compare(string1, string2, 9);
  if (procRank == 0) {
    EXPECT_EQ(result, 3);
  }
}

TEST(MPIunicSymbols, SecondLonger) {
  int procRank = 0;
  char* string1 = "qwerty";
  char* string2 = "qwe";

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  int result = Mpi_compare(string1, string2, 6);
  if (procRank == 0) {
    EXPECT_EQ(result, 3);
  }
}

TEST(MPIunicSymbols, NotIdentical) {
  int procRank = 0;
  char* string1 = "bzxcb";
  char* string2 = "rwerq";

  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  int result = Mpi_compare(string1, string2, 5);
  if (procRank == 0) {
    EXPECT_EQ(result, 5);
  }
}
