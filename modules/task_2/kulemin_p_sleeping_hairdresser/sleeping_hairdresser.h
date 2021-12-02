// Copyright 2021 Shelepin Nikita
#ifndef MODULES_TASK_2_KULEMIN_P_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_
#define MODULES_TASK_2_KULEMIN_P_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_

void barber(int myrank, int chairs_count, int total_runs);
void customer(int myrank, int total_runs);

#define CHAIR_REQUEST  1
#define CHAIR_RESPONSE  2
#define HAIR_CUT_REQUEST 3

#endif  // MODULES_TASK_2_KULEMIN_P_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_
