// Copyright 2021 Olenin Sergey
#include <gtest/gtest.h>
#include <string>
#include <gtest-mpi-listener.hpp>


#include "./number_of_sentences.h"

TEST(Parallel_NumOfSentences_MPI, Text_1) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string global_string;

  if (rank == 0) {
    global_string = "Pariatur ipsum magna consectetur excepteur.";
  }

  int pnum = getParallelNumOfSentences(global_string);

  if (rank == 0) {
    int snum = getSequentialNumOfSentences(global_string);
    ASSERT_EQ(snum, pnum);
  }
}

TEST(Parallel_NumOfSentences_MPI, Text_2) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string global_string;

  if (rank == 0) {
    global_string =
        "Quis et aliqua minim id labore ullamco veniam excepteur ut do ipsum "
        "esse? Cillum aute mollit anim laborum. Ea velit commodo veniam et id! "
        "Fugiat ex incididunt cupidatat nulla anim ex ullamco amet id est "
        "proident do. Excepteur reprehenderit id esse in!";
  }

  int pnum = getParallelNumOfSentences(global_string);

  if (rank == 0) {
    int snum = getSequentialNumOfSentences(global_string);
    ASSERT_EQ(snum, pnum);
  }
}

TEST(Parallel_NumOfSentences_MPI, Text_3) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string global_string;

  if (rank == 0) {
    global_string =
        "Non qui id ea ipsum qui! Aliquip culpa dolore dolor amet cupidatat "
        "aliquip enim adipisicing consequat in velit. Consectetur esse aliquip "
        "nostrud irure nisi excepteur enim velit adipisicing. Labore nostrud "
        "pariatur non do. Nisi elit commodo nostrud qui aliquip duis veniam "
        "eiusmod laboris laborum anim? Fugiat proident veniam culpa laborum "
        "enim aliqua dolor laboris quis. Quis est est ad ex consequat sint "
        "laborum laboris dolor aliquip ut exercitation. Ex sit veniam nulla et "
        "est sit commodo ipsum nisi mollit enim. Non nulla pariatur sit aliqua "
        "qui occaecat. Commodo minim ad est deserunt aliqua qui minim aliquip "
        "reprehenderit!";
  }

  int pnum = getParallelNumOfSentences(global_string);

  if (rank == 0) {
    int snum = getSequentialNumOfSentences(global_string);
    ASSERT_EQ(snum, pnum);
  }
}

TEST(Parallel_NumOfSentences_MPI, Text_4) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string global_string;

  if (rank == 0) {
    global_string =
        "Sunt deserunt excepteur eiusmod reprehenderit duis magna fugiat anim "
        "officia incididunt id minim enim pariatur. Eu id ipsum labore ullamco "
        "laboris non reprehenderit nulla ullamco eiusmod. Incididunt anim ut "
        "fugiat ex. Laboris ullamco nulla nisi mollit. Commodo ipsum aute ad "
        "reprehenderit ipsum sit. Lorem elit irure do ad deserunt enim. Veniam "
        "Lorem ipsum occaecat ut duis consequat officia cillum laboris enim "
        "culpa. Duis Lorem consequat non Lorem magna. Voluptate laboris "
        "cupidatat aliqua tempor anim ullamco cupidatat ullamco duis. Ut esse "
        "aliqua aute incididunt nisi do est duis ex. Deserunt dolor cupidatat "
        "nulla labore nisi in consectetur commodo adipisicing. Velit amet "
        "Lorem amet labore nostrud tempor sunt commodo. Amet commodo esse ex "
        "nulla amet. Qui excepteur aliqua culpa et occaecat est ad id "
        "exercitation proident tempor eiusmod ex cupidatat. Cupidatat id amet "
        "amet aliquip minim proident qui labore fugiat excepteur nostrud amet "
        "veniam minim.";
  }

  int pnum = getParallelNumOfSentences(global_string);

  if (rank == 0) {
    int snum = getSequentialNumOfSentences(global_string);
    ASSERT_EQ(snum, pnum);
  }
}

TEST(Parallel_NumOfSentences_MPI, Text_5) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::string global_string;

  if (rank == 0) {
    global_string =
        "Eu quis minim reprehenderit nulla amet nisi in in pariatur tempor "
        "veniam. Elit Lorem consequat cupidatat Lorem esse elit culpa sint ea "
        "non enim culpa. Irure magna commodo deserunt quis sint cupidatat. "
        "Consectetur labore reprehenderit nulla enim minim mollit nostrud amet "
        "nulla. Fugiat Lorem quis duis fugiat. Commodo nisi adipisicing velit "
        "nostrud minim do deserunt ullamco cupidatat amet ut labore. Excepteur "
        "magna sit eu adipisicing irure nostrud nulla amet est. Veniam laborum "
        "magna commodo ut proident quis amet officia ad qui consectetur. "
        "Cupidatat ipsum sint proident aute minim cupidatat labore in "
        "proident. Laboris amet culpa incididunt laborum aute laboris amet "
        "duis nisi adipisicing occaecat deserunt reprehenderit. Labore ipsum "
        "irure esse velit culpa ea veniam elit tempor. Ullamco minim ut labore "
        "commodo eiusmod consequat magna dolor consequat. Aute irure mollit "
        "officia anim esse exercitation. Officia in mollit do incididunt "
        "irure. Sit fugiat enim dolore eiusmod eu tempor amet consectetur "
        "ullamco incididunt cupidatat enim amet. Elit amet dolor tempor non "
        "occaecat ut quis ullamco nulla nisi sint aliquip pariatur. Excepteur "
        "Lorem minim ullamco ad ex dolor pariatur aliqua voluptate quis "
        "deserunt anim nisi. Est dolore irure magna veniam voluptate Lorem "
        "eiusmod ipsum deserunt duis consequat veniam velit nostrud. Nisi "
        "tempor exercitation consectetur adipisicing dolor anim quis ullamco. "
        "Adipisicing ex cupidatat ullamco aliquip duis culpa laborum elit.";
  }

  int pnum = getParallelNumOfSentences(global_string);

  if (rank == 0) {
    int snum = getSequentialNumOfSentences(global_string);
    ASSERT_EQ(snum, pnum);
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
