// Copyright 2021 Samoiluk Anastasiya
#include <gtest/gtest.h>
#include <string>
#include "../../modules/task_1/samoiluk_a_number_of_letters/number_of_letters.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Number_of_letters_sequential_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "Test string to count letters";

    if (rank == 0) {
        int count = numOfLetters_seq(str);
        ASSERT_EQ(count, 24);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_sequential_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "TeSt stRIng WIth uPperCasE aNd lOWeRcasE lETTers";

    if (rank == 0) {
        int count = numOfLetters_seq(str);
        ASSERT_EQ(count, 42);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_sequential_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "Test s3tring6 76 contai87ning numb19ers";

    if (rank == 0) {
        int count = numOfLetters_seq(str);
        ASSERT_EQ(count, 27);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_parallel_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "Test string to count letters";

    int count = numOfLetters_par(str);
    if (rank == 0) {
        ASSERT_EQ(count, 24);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_parallel_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "TeSt stRIng WIth uPperCasE aNd lOWeRcasE lETTers";

    int count = numOfLetters_par(str);
    if (rank == 0) {
        ASSERT_EQ(count, 42);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_parallel_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "Test s3tring6 76 contai87ning numb19ers";

    int count = numOfLetters_par(str);
    if (rank == 0) {
        ASSERT_EQ(count, 27);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_sequential_and_parallel_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "Test string to count letters";
    int count_s, count_p;
    count_p = numOfLetters_par(str);

    if (rank == 0) {
        count_s = numOfLetters_seq(str);
        ASSERT_EQ(count_s, count_p);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_sequential_and_parallel_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "TeSt stRIng WIth uPperCasE aNd lOWeRcasE lETTers";
    int count_s, count_p;
    count_p = numOfLetters_par(str);

    if (rank == 0) {
        count_s = numOfLetters_seq(str);
        ASSERT_EQ(count_s, count_p);
    }
}

TEST(Parallel_Operations_MPI, Number_of_letters_sequential_and_parallel_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string str = "Test s3tring6 76 contai87ning numb19ers";
    int count_s, count_p;
    count_p = numOfLetters_par(str);

    if (rank == 0) {
        count_s = numOfLetters_seq(str);
        ASSERT_EQ(count_s, count_p);
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
