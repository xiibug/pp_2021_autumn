// Copyright 2021 Shurygina Anna
#ifndef MODULES_TASK_2_SHURYGINA_A_LINEAR_TOPOLOGY_LINEAR_TOPOLOGY_H_
#define MODULES_TASK_2_SHURYGINA_A_LINEAR_TOPOLOGY_LINEAR_TOPOLOGY_H_

// Get random int sequence for testing
int* getRandomSequence(int size);

// Get graph of processes
MPI_Comm createGraphComm(MPI_Comm comm);

// buf - memmory buffer
// count - send data size
// type - data type
// dest - process we send data
// comm - communicator
// source - process which send data
// procRank - calling process
int* sendData(int* buf, int count, MPI_Datatype type,
	int dest, int tag, MPI_Comm comm, int source, int procRank);

#endif  // MODULES_TASK_2_SHURYGINA_A_LINEAR_TOPOLOGY_LINEAR_TOPOLOGY_H_
