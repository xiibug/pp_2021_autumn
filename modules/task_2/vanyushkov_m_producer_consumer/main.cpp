// Copyright 2021 Vanyushkov Maxim
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "producer_consumer.h"

TEST(producer_consumer_mpi, producer_consumer) {
	int procRank, procCount;

    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);

    if (procRank == 0) {
        int prod = procCount / 2;
        int cons = (procCount - 1) / 2;
        Manager manager(3, procCount, prod, cons);
        manager.Run();
    }
    else {
        if (procRank % 2) {
            // std::cout << "The process with the procRank of " << procRank << " is Producer" << std::endl;
            Producer producer(procRank);
            producer.Run();
        }
        else {
            // std::cout << "The process with the procRank of " << procRank << " is Consumer" << std::endl;
            Consumer consumer(procRank);
            consumer.Run();
        }
    }

    ASSERT_NO_THROW();
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
