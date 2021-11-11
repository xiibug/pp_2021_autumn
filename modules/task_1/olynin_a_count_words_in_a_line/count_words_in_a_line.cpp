// Copyright 2021 Olynin Alexandr
# include <string.h>
#include <mpi.h>
#include "../../../modules/task_1/olynin_a_count_words_in_a_line/count_words_in_a_line.h"

char tokens[8] = {'\n', '-', ',', '.', '!', ':', '?', ';'};

int SequentialCountWordsInALine(const char* tmp) {
    char* str = new char[strlen(tmp) + 1];
    memcpy(str, tmp, strlen(tmp) + 1);
    str[strlen(tmp)] = ' ';
    str[strlen(tmp) + 1] = '\0';
    int l = 0;
    int count = 0;
    char* is_token = nullptr;
    int len = strlen(str) + 1;
    for (int i = 0; i < len; i++) {
        is_token = strchr(tokens, (int)(str[i]));
        if (is_token == nullptr) {
            if (str[i] != ' ') {
                l++;
            } else if (l > 0) {
                count++;
                l = 0;
            }
        }
    }
    return count;
}

int ParallelCountWordsInALine(const char* tmp) {
    char* str = nullptr;
    char* local_str = nullptr;
    int inaccuracy = 0;

    int* send_counts = nullptr;
    int* offset = nullptr;
    int ProcNum;
    int ProcRank;

    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    send_counts = new int[ProcNum];
    offset = new int[ProcNum];

    if (ProcRank == 0) {
        str = new char[strlen(tmp) + 1];
        memcpy(str, tmp, strlen(tmp) + 1);
        int sum = 0;
        int ost = strlen(str) % ProcNum;
        for (int i = 0; i < ProcNum; i++) {
            send_counts[i] = (strlen(str) / ProcNum);
            if (ost > 0) {
                send_counts[i]++;
                ost--;
            }
            offset[i] = sum;
            sum += send_counts[i];
        }
        sum = 0;
        for (int i = 1; i < ProcNum; i++) {
            sum += send_counts[i - 1];
            char* is_token_char_one = strchr(tokens, static_cast<int>(str[sum - 1]));
            char* is_token_char_two = strchr(tokens, static_cast<int>(str[sum]));
            if (is_token_char_one == nullptr && is_token_char_two == nullptr
                && str[sum] != ' ' && str[sum - 1] != ' ')
                inaccuracy++;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(send_counts, ProcNum, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(offset, ProcNum, MPI_INT, 0, MPI_COMM_WORLD);

    local_str = new char[send_counts[ProcRank] + 2];

    MPI_Scatterv(str, send_counts, offset, MPI_CHAR, local_str, send_counts[ProcRank], MPI_CHAR, 0, MPI_COMM_WORLD);
    local_str[send_counts[ProcRank]] = ' ';
    local_str[send_counts[ProcRank] + 1] = '\0';
    int l = 0;
    int count = 0;
    char* is_token = nullptr;
    for (int i = 0; i < send_counts[ProcRank] + 1; i++) {
        is_token = strchr(tokens, static_cast<int>(local_str[i]));
        if (is_token == nullptr) {
            if (local_str[i] != ' ')
                l++;
            else if (l > 0) {
                count++;
                l = 0;
            }
        }
    }
    int total_count;
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (ProcRank == 0) {
        total_count -= inaccuracy;
        delete[] str;
        return total_count;
    }
    delete[] local_str;
    return ProcRank;
}

const char* GetReadyText(int key) {
    if (key == 0) {
        return "Amidst a wild flat meadow encircled by an Edenic lush forest";
    }
    if (key == 1) {
        return "The Emergency Code for a plane hijacking is 7500: a tense, intense thriller";
    }
    return "error";
}
