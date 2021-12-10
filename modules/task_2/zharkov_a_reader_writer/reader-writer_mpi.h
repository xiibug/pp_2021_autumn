// Copyright 2021 Zharkov Andrey
#ifndef MODULES_TASK_2_ZHARKOV_A_READER_WRITER_READER_WRITER_MPI_H_
#define MODULES_TASK_2_ZHARKOV_A_READER_WRITER_READER_WRITER_MPI_H_

#include <string>
#define S_Request 1
#define S_Response 2
#define S_Release 3

#define RC_Request 4
#define RC_Response 5
#define RC_Release 6

#define Access_Request 7
#define Access_Response 8
#define Access_Release 9
#define Finish 10

void reader(int rank);
void writer(int rank);
void work(int rank, int proc);
void read_oper();
void write_oper();
void wait(int proc);

#endif  // MODULES_TASK_2_ZHARKOV_A_READER_WRITER_READER_WRITER_MPI_H_
