// Copyright 2021 Olynin Alexandr
#include <mpi.h>
#include "../../../modules/task_1/olynin_a_count_words_in_a_line/count_words_in_a_line.h"

int SequentialCountWordsInALine(std::string str) {
    str += " ";
    int l = 0;
    int count = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] != ' ' && str[i] != '-') {
            l++;
        } else if (l > 0) {
            count++;
            l = 0;
        }
    }
    return count;
}

int ParallelCountWordsInALine(std::string str) {
    int ProcNum;
    int ProcRank;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    int send_count;
    if (ProcRank == 0) {
        for (size_t i = 0; i < str.size() % ProcNum; i++) {
            str += " ";
        }
        send_count = str.size() / ProcNum;
    }
    MPI_Bcast(&send_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (send_count == 0) {
        return 0;
    }

    std::string local_str;
    local_str.resize(send_count);
    MPI_Scatter(str.c_str(), send_count, MPI_CHAR,
                const_cast<char*>(local_str.data()), send_count, MPI_CHAR, 0, MPI_COMM_WORLD);

    int count = SequentialCountWordsInALine(local_str);
    int total_count = 0;
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (ProcRank == 0) {
        int inaccuracy = 0;
        for (int i = 1; i < ProcNum; i++) {
            if (str[send_count * i] != ' ' && str[send_count * i - 1] != ' ') {
                inaccuracy++;
            }
        }
        total_count -= inaccuracy;
        return total_count;
    }
    return ProcRank;
}

std::string GetReadyText(int key) {
    if (key == 0) {
        return "Amidst a wild flat meadow - encircled by an Edenic lush forest";
    }
    if (key == 1) {
        return "The Emergency Code for a plane hijacking is 7500: a tense, intense thriller";
    }
    return "error";
}
