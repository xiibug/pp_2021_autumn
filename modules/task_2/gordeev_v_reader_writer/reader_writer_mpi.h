// Copyright 2021 Gordeev Viktor
#ifndef MODULES_TASK_2_GORDEEV_V_READER_WRITER_READER_WRITER_MPI_H_
#define MODULES_TASK_2_GORDEEV_V_READER_WRITER_READER_WRITER_MPI_H_

#include <string>

void read();
void write();
void reader(int rank);
void writer(int rank);
void library(int rank, int procs);

#define SREQUEST 1
#define SRESPONSE 2
#define SRELEASE 3

#define RCREQUEST 4
#define RCRESPONSE 5
#define RCRELEASE 6

#define ACCESSREQUEST 7
#define ACCESSRESPONSE 8
#define ACCESSRELEASE 9

#define FINISH 10

#define RCSENDING 11

/*#define SWaiting 1
#define SRelease 3
#define RCWaiting 4
#define RCRelease 6
#define ACCESSWaiting 7
#define ACCESSRelease 9*/
#endif  // MODULES_TASK_2_GORDEEV_V_READER_WRITER_READER_WRITER_MPI_H_
