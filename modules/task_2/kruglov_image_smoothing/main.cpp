// Copyright 2021 Kruglov Aleksei
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_2/kruglov_image_smoothing/Gaussian_blur.h"

//  TEST(GaussianBlur, Dataset_1) {
//      int proc_rank;
//      MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
//      bool precalculate = false;
//      std::string path_in = "../../modules/task_2/kruglov_image_smoothing/dataset/1arr_input.txt";
//      std::string path_out = "../../modules/task_2/kruglov_image_smoothing/dataset/1arr_output.txt";
//      auto image = get_image_from_file(path_in);
//      auto kernel = create_gaussian_kernel(1, 2.0f);
//      if (proc_rank == 0 && precalculate) {
//          auto img_precalc = apply_gaussian_blur(image, kernel);
//          save_image_in_file(path_out, img_precalc);
//      }
//      auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
//      if (proc_rank == 0) {
//          int threshold = 1;
//          auto img_reference = get_image_from_file(path_out);
//          ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
//      }
//  }
//
//  TEST(GaussianBlur, Dataset_2) {
//      int proc_rank;
//      MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
//      bool precalculate = false;
//      std::string path_in = "../../modules/task_2/kruglov_image_smoothing/dataset/2arr_input.txt";
//      std::string path_out = "../../modules/task_2/kruglov_image_smoothing/dataset/2arr_output.txt";
//      auto image = get_image_from_file(path_in);
//      auto kernel = create_gaussian_kernel(1, 2.0f);
//      if (proc_rank == 0 && precalculate) {
//          auto img_precalc = apply_gaussian_blur(image, kernel);
//          save_image_in_file(path_out, img_precalc);
//      }
//      auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
//      if (proc_rank == 0) {
//          int threshold = 1;
//          auto img_reference = get_image_from_file(path_out);
//          ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
//      }
//  }
//
//  TEST(GaussianBlur, Dataset_3) {
//      int proc_rank;
//      MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
//      bool precalculate = false;
//      std::string path_in = "../../modules/task_2/kruglov_image_smoothing/dataset/3arr_input.txt";
//      std::string path_out = "../../modules/task_2/kruglov_image_smoothing/dataset/3arr_output.txt";
//      auto image = get_image_from_file(path_in);
//      auto kernel = create_gaussian_kernel(1, 2.0f);
//      if (proc_rank == 0 && precalculate) {
//          auto img_precalc = apply_gaussian_blur(image, kernel);
//          save_image_in_file(path_out, img_precalc);
//      }
//      auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
//      if (proc_rank == 0) {
//          int threshold = 1;
//          auto img_reference = get_image_from_file(path_out);
//          ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
//      }
//  }
//
//  TEST(GaussianBlur, Dataset_4) {
//      int proc_rank;
//      MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
//      bool precalculate = false;
//      std::string path_in = "../../modules/task_2/kruglov_image_smoothing/dataset/4arr_input.txt";
//      std::string path_out = "../../modules/task_2/kruglov_image_smoothing/dataset/4arr_output.txt";
//      auto image = get_image_from_file(path_in);
//      auto kernel = create_gaussian_kernel(1, 2.0f);
//      if (proc_rank == 0 && precalculate) {
//          auto img_precalc = apply_gaussian_blur(image, kernel);
//          save_image_in_file(path_out, img_precalc);
//      }
//      auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
//      if (proc_rank == 0) {
//          int threshold = 1;
//          auto img_reference = get_image_from_file(path_out);
//          ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
//      }
//  }

TEST(GaussianBlur, with_small_size) {
    int height = 5, width = 5;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Image image;
    Matrix kernel;
    kernel = create_gaussian_kernel(1, 1.0f);
    if (proc_rank == 0) {
        image = get_random_image(height, width);
    }
    auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
    if (proc_rank == 0) {
        int threshold = 1;
        auto img_reference = apply_gaussian_blur(image, kernel);
        ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
    }
}

TEST(GaussianBlur, with_big_size) {
    int height = 1024, width = 1024;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Image image;
    Matrix kernel;
    kernel = create_gaussian_kernel(1, 1.0f);
    if (proc_rank == 0) {
        image = get_random_image(height, width);
    }
    auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
    if (proc_rank == 0) {
        int threshold = 1;
        auto img_reference = apply_gaussian_blur(image, kernel);
        ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
    }
}

TEST(GaussianBlur, rectangle_shape_0) {
    int height = 120, width = 100;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Image image;
    Matrix kernel;
    kernel = create_gaussian_kernel(1, 1.0f);
    if (proc_rank == 0) {
        image = get_random_image(height, width);
    }
    auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
    if (proc_rank == 0) {
        int threshold = 1;
        auto img_reference = apply_gaussian_blur(image, kernel);
        ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
    }
}

TEST(GaussianBlur, rectangle_shape_1) {
    int height = 100, width = 120;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Image image;
    Matrix kernel;
    kernel = create_gaussian_kernel(1, 1.0f);
    if (proc_rank == 0) {
        image = get_random_image(height, width);
    }
    auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
    if (proc_rank == 0) {
        int threshold = 1;
        auto img_reference = apply_gaussian_blur(image, kernel);
        ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
    }
}

TEST(GaussianBlur, sigma_1) {
    int height = 24, width = 24;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Image image;
    Matrix kernel;
    kernel = create_gaussian_kernel(1, 1.0f);
    if (proc_rank == 0) {
        image = get_random_image(height, width);
    }
    auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
    if (proc_rank == 0) {
        int threshold = 1;
        auto img_reference = apply_gaussian_blur(image, kernel);
        ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
    }
}

TEST(GaussianBlur, sigma_2) {
    int height = 24, width = 24;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    Image image;
    Matrix kernel;
    kernel = create_gaussian_kernel(1, 2.0f);
    if (proc_rank == 0) {
        image = get_random_image(height, width);
    }
    auto image_optimized = apply_gaussian_blur_parallel(image, kernel);
    if (proc_rank == 0) {
        int threshold = 1;
        auto img_reference = apply_gaussian_blur(image, kernel);
        ASSERT_TRUE(is_equal(img_reference, image_optimized, threshold));
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
