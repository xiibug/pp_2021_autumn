// Copyright 2021 Shelepin Nikita
#ifndef MODULES_TASK_2_KULEMIN_P_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_
#define MODULES_TASK_2_KULEMIN_P_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_

void barber(int myrank, int chairs_count, int ccount);
void customer(int myrank);
void line(int chairs_count, int runs);
#define CHAIR_REQUEST  1
#define CHAIR_RESPONSE  2
#define HAIR_CUT_REQUEST 3
#define HAIR_CUT 4
#endif  // MODULES_TASK_2_KULEMIN_P_SLEEPING_HAIRDRESSER_SLEEPING_HAIRDRESSER_H_
