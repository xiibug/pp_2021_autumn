// Copyright 2021 Samoiluk Anastasiya
#include <mpi.h>
#include <string>
#include "../../modules/task_1/samoiluk_a_number_of_letters/number_of_letters.h"


int numOfLetters_seq(std::string str) {
    char cap_let[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char sm_let[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    int n = 26;
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        for (int j = 0; j < n; j++) {
            if (str[i] == cap_let[j] || str[i] == sm_let[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

int numOfLetters_par(std::string str) {
    int count = 0; // number of letters
    int size; // number of processes
    int rank; // process number
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int sym_num = 0; // number of symbols to chek for each process
    int rem = 0; // remaining symbols
    int proc_count = 0; // number of letters counted by each process

    if (size > str.length())
        throw - 1;
    else {
        sym_num = str.length() / size;
        rem = str.length() % size;
    }

    if (rank == 0) {
        for (int pr_rank = 1; pr_rank < size; pr_rank++) {
            int s = 0, f = 0;
            s = pr_rank * sym_num + rem;
            f = s + sym_num;
            MPI_Send(&s, 1, MPI_INT, pr_rank, 0, MPI_COMM_WORLD);
            MPI_Send(&f, 1, MPI_INT, pr_rank, 0, MPI_COMM_WORLD);
        }
    }
     
    char cap_let[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char sm_let[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    int n = 26;
    int s, f;
    if (rank != 0) {
        MPI_Status status;
        MPI_Recv(&s, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Recv(&f, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        for (int i = s; i < f; i++) {
            for (int j = 0; j < n; j++) {
                if (str[i] == cap_let[j] || str[i] == sm_let[j]) {
                    proc_count++;
                    break;
                }
            }
        }
    }
    else {
        for (int i = 0; i < (sym_num + rem); i++) {
            for (int j = 0; j < n; j++) {
                if (str[i] == cap_let[j] || str[i] == sm_let[j]) {
                    proc_count++;
                    break;
                }
            }
        }
    }

    MPI_Reduce(&proc_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return count;
}