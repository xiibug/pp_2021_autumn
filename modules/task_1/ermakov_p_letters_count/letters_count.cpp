// Copyright 2021 Ermakov Pavel
#include "../../../modules/task_1/ermakov_p_letters_count/letters_count.h"
const int albet_size = 26;

std::string
random_str_gen(int size)
{
    std::string s;
    static const char alphanum[] = "01234 56789"
                                   "ABCDEFGHIJKLM NOPQRSTUVWXYZ"
                                   "abcdefghijklm nopqrstuvwxyz";

    for (int i = 0; i < size; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return s;
}

int letters_count_seq(std::string str)
{
    int letters_count = 0;
    int str_size = str.length();
    char albet_lo_reg[albet_size] {}, albet_up_reg[albet_size] {};
    std::iota(std::begin(albet_lo_reg), std::end(albet_lo_reg), 'a');
    std::iota(std::begin(albet_up_reg), std::end(albet_up_reg), 'A');

    for (int i = 0; i < str_size; i++) {
        for (int j = 0; j < albet_size; j++) {
            if (str[i] == albet_lo_reg[j] || str[i] == albet_up_reg[j]) {
                letters_count++;
                break;
            }
        }
    }
    if (str_size == 0)
        return 0;
    return letters_count;
}

int letters_count_par(std::string str)
{
    int total_amount = 0, num_of_proc, proc_num, num_of_chars = 0, rest = 0,
        count_of_s = 0, str_size = str.length(), start_of_s, end_of_s;

    char albet_lo_reg[albet_size] {}, albet_up_reg[albet_size] {};

    std::iota(std::begin(albet_lo_reg), std::end(albet_lo_reg), 'a');
    std::iota(std::begin(albet_up_reg), std::end(albet_up_reg), 'A');

    MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);
    if (str_size == 0)
        return 0;
    if (num_of_proc > str_size) {
        throw "Error. Number of processes is bigger then lenght of string!";
    } else {
        num_of_chars = str_size / num_of_proc;
        rest = str_size % num_of_proc;
    }

    if (proc_num == 0) {
        for (int i = 1; i < num_of_proc; i++) {
            int start_of_s = 0, end_of_s = 0;
            start_of_s = i * num_of_chars + rest;
            end_of_s = start_of_s + num_of_chars;
            MPI_Send(&start_of_s, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&end_of_s, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    if (proc_num != 0) {
        MPI_Status status;
        MPI_Recv(&start_of_s, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Recv(&end_of_s, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        for (int i = start_of_s; i < end_of_s; i++) {
            for (int j = 0; j < albet_size; j++) {
                if (str[i] == albet_lo_reg[j] || str[i] == albet_up_reg[j]) {
                    count_of_s++;
                    break;
                }
            }
        }
    } else {
        int from_zero_to_start = num_of_chars + rest;
        for (int i = 0; i < from_zero_to_start; i++) {
            for (int j = 0; j < albet_size; j++) {
                if (str[i] == albet_up_reg[j] || str[i] == albet_lo_reg[j]) {
                    count_of_s++;
                    break;
                }
            }
        }
    }

    MPI_Reduce(
        &count_of_s, &total_amount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return total_amount;
}