// Copyright 2021 Kim Nikita
#include <gtest/gtest.h>
#include <vector>
#include "./sobel.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Sobel_X) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<int>> image;

  if (rank == 0) {
    image = getRandomImage(3);
  }

  std::vector<std::vector<int>> res = getSobelImageParall(image, 3, 'x');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image, 3, 'x');
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (res[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], res[i][j]);
        }
    ASSERT_EQ(0, 0);
  }
}

TEST(Parallel_Operations_MPI, Test_Sobel_Y) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<int>> image;

  if (rank == 0) {
    image = getRandomImage(3);
  }

  std::vector<std::vector<int>> res = getSobelImageParall(image, 3, 'y');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image, 3, 'y');
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (res[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], res[i][j]);
        }
    ASSERT_EQ(0, 0);
  }
}

TEST(Parallel_Operations_MPI, Test_Sobel_XY) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<int>> image1;

  if (rank == 0) {
    image1 = getRandomImage(3);
  }

  std::vector<std::vector<int>> image2 = getSobelImageParall(image1, 3, 'x');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image1, 3, 'x');
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (image2[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], image2[i][j]);
        }
  }

  std::vector<std::vector<int>> res = getSobelImageParall(image2, 3, 'y');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image2, 3, 'y');
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (res[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], res[i][j]);
        }
    ASSERT_EQ(0, 0);
  }
}

TEST(Parallel_Operations_MPI, Test_Sobel_X_Large) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<int>> image;

  if (rank == 0) {
    image = getRandomImage(4);
  }

  std::vector<std::vector<int>> res = getSobelImageParall(image, 4, 'x');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image, 4, 'x');
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (res[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], res[i][j]);
        }
    ASSERT_EQ(0, 0);
  }
}

TEST(Parallel_Operations_MPI, Test_Sobel_Y_Large) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<int>> image;

  if (rank == 0) {
    image = getRandomImage(4);
  }

  std::vector<std::vector<int>> res = getSobelImageParall(image, 4, 'y');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image, 4, 'y');
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (res[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], res[i][j]);
        }
    ASSERT_EQ(0, 0);
  }
}

TEST(Parallel_Operations_MPI, Test_Sobel_XY_Large) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<std::vector<int>> image1;

  if (rank == 0) {
    image1 = getRandomImage(4);
  }

  std::vector<std::vector<int>> image2 = getSobelImageParall(image1, 4, 'x');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image1, 4, 'x');
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (image2[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], image2[i][j]);
        }
  }

  std::vector<std::vector<int>> res = getSobelImageParall(image2, 4, 'y');

  if (rank == 0) {
    std::vector<std::vector<int>> exp_res = getSobelImage(image2, 4, 'y');
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (res[i][j] != exp_res[i][j]) {
          ASSERT_EQ(exp_res[i][j], res[i][j]);
        }
    ASSERT_EQ(0, 0);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
