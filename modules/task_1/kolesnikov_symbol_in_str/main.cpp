#include <gtest/gtest.h>
#include <mpi.h>
#include <string>
#include "./kolesnikov_symbol_in_str.h"
#include <gtest-mpi-listener.hpp>

TEST(find_symbol, single) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char s = 'f';

    std::string str = "Here is a vivid example of modern trends -"
        "a deep level of immersion requires an analysis of the directions"
        "of progressive development. By the way, the conclusions made on the"
        "basis of Internet analytics, overcoming the current difficult economic"
        "situation, have been verified in a timely manner. In our quest to"
        "improve the user experience, we miss that the conclusions drawn on the"
        "basis of Internet analytics will be limited solely by the way of thinking.";
    if (rank == 0) {
        int res = single_find_symbol(s, str);
        ASSERT_EQ(res, 10);
    }
}

TEST(find_symbol, parallel) {
    int rank = 0, size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char s = 'f';

    std::string str = "Here is a vivid example of modern trends -"
        "a deep level of immersion requires an analysis of the directions"
        "of progressive development. By the way, the conclusions made on the"
        "basis of Internet analytics, overcoming the current difficult economic"
        "situation, have been verified in a timely manner. In our quest to"
        "improve the user experience, we miss that the conclusions drawn on the"
        "basis of Internet analytics will be limited solely by the way of thinking.";
    int res = parallel_find_symbol(s, str);

    if (rank == size - 1) {
        ASSERT_EQ(res, 10);
    }
}

TEST(find_symbol, single_parallel) {
    int rank = 0, size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char s = 'f';

    std::string str = "Here is a vivid example of modern trends -"
        "a deep level of immersion requires an analysis of the directions"
        "of progressive development. By the way, the conclusions made on the"
        "basis of Internet analytics, overcoming the current difficult economic"
        "situation, have been verified in a timely manner. In our quest to"
        "improve the user experience, we miss that the conclusions drawn on the"
        "basis of Internet analytics will be limited solely by the way of thinking.";
    int fst = parallel_find_symbol(s, str);
    if (rank == size - 1) {
        int snd = single_find_symbol(s, str);
        ASSERT_EQ(fst, snd);
    }
}

TEST(find_symbol, reverse) {
    int rank = 0, size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char s = 'f';

    std::string str = ".gnikniht fo yaw eht yb ylelos detimil eb lliw scitylana tenretnI fo sisab"
        "eht no nward snoisulcnoc eht taht ssim ew ,ecneirepxe resu eht evorpmi"
        "ot tseuq ruo nI .rennam ylemit a ni deifirev neeb evah ,noitautis"
        "cimonoce tluciffid tnerruc eht gnimocrevo ,scitylana tenretnI fo sisab"
        "eht no edam snoisulcnoc eht ,yaw eht yB .tnempoleved evissergorp fo"
        "snoitcerid eht fo sisylana na seriuqer noisremmi fo level peed a"
        "- sdnert nredom fo elpmaxe diviv a si ereH";

    int res = parallel_find_symbol(s, str);

    if (rank == size - 1) {
        ASSERT_EQ(res, 10);
    }
}

TEST(find_symbol, uppercase) {
    int rank = 0, size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char s = 'f';

    std::string str1 = "Here is a vivid example of modern trends -"
        "a deep level of immersion requires an analysis of the directions"
        "of progressive development. By the way, the conclusions made on the"
        "basis of Internet analytics, overcoming the current difficult economic"
        "situation, have been verified in a timely manner. In our quest to"
        "improve the user experience, we miss that the conclusions drawn on the"
        "basis of Internet analytics will be limited solely by the way of thinking.";

    int fst = parallel_find_symbol(s, str1);

    std::string str2 = "HERE IS A VIVID EXAMPLE OF MODERN TRENDS -"
        "A DEEP LEVEL OF IMMERSION REQUIRES AN ANALYSIS OF THE DIRECTIONS"
        "OF PROGRESSIVE DEVELOPMENT. BY THE WAY, THE CONCLUSIONS MADE ON THE"
        "BASIS OF INTERNET ANALYTICS, OVERCOMING THE CURRENT DIFFICULT ECONOMIC"
        "SITUATION, HAVE BEEN VERIFIED IN A TIMELY MANNER. IN OUR QUEST TO"
        "IMPROVE THE USER EXPERIENCE, WE MISS THAT THE CONCLUSIONS DRAWN ON THE"
        "BASIS OF INTERNET ANALYTICS WILL BE LIMITED SOLELY BY THE WAY OF THINKING.";

    int snd = parallel_find_symbol(s, str2);

    if (rank == size - 1) {
        ASSERT_EQ(fst, snd);
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
