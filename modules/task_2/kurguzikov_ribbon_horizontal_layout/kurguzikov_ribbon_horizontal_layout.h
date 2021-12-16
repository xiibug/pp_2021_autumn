  // Copyright 2021 Kurguzikov Kirill
#ifndef MODULES_TASK_2_KURGUZIKOV_RIBBON_HORIZONTAL_LAYOUT_KURGUZIKOV_RIBBON_LAYOUT_HORIZONTAL_H_
#define MODULES_TASK_2_KURGUZIKOV_RIBBON_HORIZONTAL_LAYOUT_KURGUZIKOV_RIBBON_LAYOUT_HORIZONTAL_H_

int* initEmptyMatrix(int string, int column);
int* getRandomMatrix(int string, int column);
void SequentialMatrixMultiplication(int* A, int Astring, int Acolumn,
    int* B, int Bstring, int Bcolumn, int* C);
void ParallelMatrixMultiplication(int* A, int Astring, int Acolumn,
    int* B, int Bstring, int Bcolumn, int* C);

#endif  // MODULES_TASK_2_KURGUZIKOV_RIBBON_HORIZONTAL_LAYOUT_KURGUZIKOV_RIBBON_LAYOUT_HORIZONTAL_H_
