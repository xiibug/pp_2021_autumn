// Copyright 2021 Kitaev Pavel

#include <gtest/gtest.h>
#include <mpi.h>
#include <string>
#include "./kitaev_counting_sentences.h"
#include <gtest-mpi-listener.hpp>


TEST(Parallel_Operations_MPI, Test_Sequentiall) {
  int ProcRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  std::string Text = getText();

  if (ProcRank == 0) {
    int SequentiallRes = sequentialCountingSentences(Text);
    ASSERT_EQ(SequentiallRes, 50);
  }
}

TEST(Parallel_Operations_MPI, Test_Parallel) {
  int ProcRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  std::string Text = getText();

  int ParallelRes = parallelCountingSentences(Text);

  if (ProcRank == 0) {
    ASSERT_EQ(ParallelRes, 50);
  }
}

TEST(Parallel_Operations_MPI, Test_Standard_Text) {
  int ProcRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  std::string Text = getText();

  int ParallelRes = parallelCountingSentences(Text);

  if (ProcRank == 0) {
    int SequentiallRes = sequentialCountingSentences(Text);
    ASSERT_EQ(SequentiallRes, ParallelRes);
  }
}

TEST(Parallel_Operations_MPI, Test_Additional_Characters_In_Text) {
  int ProcRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  std::string Text = getText();
  std::string NewText = Text + " Question mark? Exclamation mark! Ellipsis...";

  int ParallelRes = parallelCountingSentences(NewText);

  if (ProcRank == 0) {
    int SequentiallRes = sequentialCountingSentences(NewText);
    ASSERT_EQ(SequentiallRes, ParallelRes);
  }
}

TEST(Parallel_Operations_MPI, Test_Large_Text) {
  int ProcRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  std::string Text = getText();
  std::string NewText = Text + " " + Text + " " + Text;

  int ParallelRes = parallelCountingSentences(NewText);
  if (ProcRank == 0) {
    int SequentiallRes = sequentialCountingSentences(NewText);
    ASSERT_EQ(ParallelRes, SequentiallRes);
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
