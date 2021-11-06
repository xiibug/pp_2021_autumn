// Copyright 2021 Myasnikova Varvara

#include <gtest/gtest.h>
#include <mpi.h>
#include <string>
#include "./myasnikova_counting_symbols.h"
#include <gtest-mpi-listener.hpp>


TEST(Parallel_Operations_MPI, Serial_test) {
  int procRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  std::string text = "The Nile crocodile is called tanin ha-yeor in Hebrew, "
"timsah al-nil in Arabic, mamba in Swahili, garwe in Shona, ngwenya in Ndebele, "
"ngwena in Venda, and kwena in Sotho and Tswana. It also sometimes referred to "
"as the African crocodile, Ethiopian crocodile, common crocodile, or the black crocodile.";
  char s = 'c';
  if (procRank == 0) {
    int res = sCountingSymbols(s, text);
    ASSERT_EQ(res, 15);
  }
}

TEST(Parallel_Operations_MPI, Parallel_test) {
  int procRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  std::string text = "The Nile crocodile is called tanin ha-yeor in Hebrew, "
"timsah al-nil in Arabic, mamba in Swahili, garwe in Shona, ngwenya in Ndebele, "
"ngwena in Venda, and kwena in Sotho and Tswana. It also sometimes referred to "
"as the African crocodile, Ethiopian crocodile, common crocodile, or the black crocodile.";
  char s = 'c';
  int res = pCountingSymbols(s, text);
  if (procRank == 0) {
    ASSERT_EQ(res, 15);
  }
}

TEST(Parallel_Operations_MPI, Parallel_Serial_test) {
  int procRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  std::string text = "The Nile crocodile is called tanin ha-yeor in Hebrew, "
"timsah al-nil in Arabic, mamba in Swahili, garwe in Shona, ngwenya in Ndebele, "
"ngwena in Venda, and kwena in Sotho and Tswana. It also sometimes referred to "
"as the African crocodile, Ethiopian crocodile, common crocodile, or the black crocodile.";
  char s = 'c';
  int P_res = pCountingSymbols(s, text);
  if (procRank == 0) {
    int S_res = sCountingSymbols(s, text);
    ASSERT_EQ(S_res, P_res);
  }
}

TEST(Parallel_Operations_MPI, Register_test) {
  int procRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  char s = 'c';
  std::string text_1 = "The Nile crocodile is called tanin ha-yeor in Hebrew, "
"timsah al-nil in Arabic, mamba in Swahili, garwe in Shona, ngwenya in Ndebele, "
"ngwena in Venda, and kwena in Sotho and Tswana. It also sometimes referred to "
"as the African crocodile, Ethiopian crocodile, common crocodile, or the black crocodile.";

  int P1_res = pCountingSymbols(s, text_1);

  std::string text_2 = "THE NILE CROCODILE IS CALLED TANIN HA-YEOR IN HEBREW, "
"TIMSAH AL-NIL IN ARABIC, MAMBA IN SWAHILI, GARWE IN SHONA, NGWENYA IN NDEBELE, "
"NGWENA IN VENDA, AND KWENA IN SOTHO AND TSWANA. IT ALSO SOMETIMES REFERRED TO "
"AS THE AFRICAN CROCODILE, ETHIOPIAN CROCODILE, COMMON CROCODILE, OR THE BLACK CROCODILE.";

  int P2_res = pCountingSymbols(s, text_2);
  if (procRank == 0) {
    ASSERT_EQ(P1_res, P2_res);
  }
}

TEST(Parallel_Operations_MPI, Other_text_test) {
  int procRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  char s = 's';
  std::string text = "African lions live in scattered populations across "
"Sub-Saharan Africa. The lion prefers grassy plains and savannahs, scrub bordering "
"rivers and open woodlands with bushes. It is absent from rainforests and rarely enters "
"closed forests. Lions occur in savannah grasslands with scattered "
"acacia trees, which serve as shade. Its habitat is a mixture of dry savannah "
"forest and very dry, deciduous scrub forest.";

  int p_res = pCountingSymbols(s, text);
  if (procRank == 0) {
    int s_res = sCountingSymbols(s, text);
    ASSERT_EQ(p_res, s_res);
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
