// Copyright 2021 Nazarov Nikita
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "../../../modules/task_3/nazarov_n_fox_algorithm/fox_algorithm.h"

// 1 4 9 16 25 36 49 ... n^2

TEST(FoxAlgorithm, Test_on_Matrix_size_1X1) {
  int data = 1;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(0);
  }
}

TEST(FoxAlgorithm, Test_on_BlockMatrix_size_5X5) {
  int data = 5;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(false);
  }
}

TEST(FoxAlgorithm, Test_on_BlockMatrix_size_10X10) {
  int data = 10;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(false);
  }
}

TEST(FoxAlgorithm, Test_on_BlockMatrix_size_25X25) {
  int data = 25;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(false);
  }
}

TEST(FoxAlgorithm, Test_on_BlockMatrix_size_50X50) {
  int data = 50;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(false);
  }
}

TEST(FoxAlgorithm, Test_on_BlockMatrix_size_100X100) {
  int data = 100;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(false);
  }
}

TEST(FoxAlgorithm, Test_on_BlockMatrix_size_150X150) {
  int data = 150;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(false);
  }
}

TEST(FoxAlgorithm, Test_on_BlockMatrix_size_200X200) {
  int data = 200;
  std::vector<double> A, B, C, CFox;
  int ProcRank, ProcNum;
  double MULT, MULT_, FOX, FOX_;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int blocks = sqrt(ProcNum);
  if (blocks * blocks == ProcNum) {
    int add = data % blocks;
    data += (blocks - add) % blocks;
    if (ProcRank == 0) {
      A = GetRandomMatrix(data);
      B = GetRandomMatrix(data);
      C.resize(data * data, 0);
      MULT = MPI_Wtime();
      Multiplication(A, B, C, data);
      MULT_ = MPI_Wtime();
    }
    CFox.resize(data * data, 0);
    FOX = MPI_Wtime();
    FoxAlgorithm(A, B, CFox, data);
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0) {
      FOX_ = MPI_Wtime();
      printf("Multipl: \t %lf \n", MULT_ - MULT);
      printf("FoxAlgorithm: \t %lf \n", FOX_ - FOX);
      printf("speed-up: \t %lf \n", (MULT_ - MULT) / (FOX_ - FOX));
      for (int i = 0; i < data * data; i++) {
        ASSERT_NEAR(CFox[i], C[i], 0.0001);
      }
    }
  } else {
    ASSERT_FALSE(false);
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
