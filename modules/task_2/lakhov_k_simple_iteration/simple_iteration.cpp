// Copyright 2021 Lakhov Kirill

#include <vector>
#include <cstdlib>
#include "../../../modules/task_2/lakhov_k_simple_iteration/simple_iteration.h"

std::vector<double> getRandomVector(int sz, int min, int max) {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> distribution(min, max);
    std::vector<double> vec(sz);
    for (int  i = 0; i < sz; i++) { vec[i] = distribution(engine); }
    return vec;
}

std::vector<std::vector<double>> getRandomMatrix(int size) {
    std::vector<std::vector<double>> vec(size);
    std::vector<double> prevailing = getRandomVector(size,
        10*size+1, 10*size+20);
    for (int  i = 0; i < size; i++) {
        vec[i] = getRandomVector(size, -10, 10);
        vec[i][i] = prevailing[i];
    }
    return vec;
}

/*
    Ax=b
    [a(1,1), a(1,2)] x [x(1)] = [b(1)]
    [a(2,1), a(2,2)]   [x(2)]   [b(2)]

    Ax=b -> x = Cx + d

    *(-1) if a(i, i) < 0
    : -a(i, i)

    [x(1)] = [0, -a(1,2)/a(1,1)] x  [x(1)] + [b(1)/a(1,1)]
    [x(2)]   [-a(2,1)/a(2,2), 0]    [x(2)]   [b(2)/a(2,2)]


    [x(k+1)] = [0, -a(1,2)/a(1,1)] x  [x(k)] + [b(1)/a(1,1)]
    [x(k+1)]   [-a(2,1)/a(2,2), 0]    [x(k)]   [b(2)/a(2,2)]

    convergence condition:
    max[i](sum[j=1 to n](|C[i][j])|) < 1

    is met by:
    a(i,i) > sum[j=1 to n, j!=i](a(i, j))

    more info
    https://en.wikipedia.org/wiki/Iterative_method (need to enable RU)
*/

std::vector<double> sequentialCalc(
                                std::vector<std::vector<double>> coefficients,
                                std::vector<double> free_members, int size) {
    for (int i = 0; i < size; i++) {
        double coeff = coefficients[i][i];
        bool coeff_is_negative = coeff < 0;
        free_members[i] /= coeff_is_negative ? -coeff : coeff;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                coefficients[i][j] /= coeff_is_negative ? coeff : -coeff;
            } else {
                coefficients[i][j] = 0;
            }
        }
    }

    std::vector<double> x(size);
    std::vector<double> next_x = free_members;
    double epsilon = 0.0001;
    bool stop = false;
    while (!stop) {
        for (int i = 0; i < size; i++) {
            x[i] = next_x[i];
            next_x[i] = 0;
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                next_x[i] += coefficients[i][j]*x[j];
            }
            next_x[i] += free_members[i];
        }

        stop = true;
        for (int i = 0; i < size - 1; i++) {
            if (std::abs(x[i] - next_x[i]) > epsilon) {
                stop = false;
            }
        }
    }
    return next_x;
}


std::vector<double> parallelCalc(std::vector<std::vector<double>> matrix,
        std::vector<double> free_members, int size) {
    int proc_count = 0, proc_rank = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    int rows_per_proc = size / proc_count;
    int excess_rows = size % proc_count;

    int amount_of_elems_per_proc = rows_per_proc*size+rows_per_proc;
    int current_amount_of_elems = amount_of_elems_per_proc;
    if (proc_rank < excess_rows) {
        current_amount_of_elems += size + 1;
    }

    std::vector<double> raw_data;
    std::vector<int> send_counts(proc_count, amount_of_elems_per_proc);
    std::vector<int> send_offsets(proc_count, 0);
    std::vector<double> proc_data(current_amount_of_elems);

    if (proc_rank == 0) {
        // flatten vector and add free members for each row
        std::size_t total_size = size*size + size;
        raw_data.reserve(total_size);
        for (int i = 0; i < size; i++) {
            matrix[i].push_back(free_members[i]);
            raw_data.insert(raw_data.end(),
                            matrix[i].begin(), matrix[i].end());
        }

        for (int i = 0; i < excess_rows; i++)
            send_counts[i] += size + 1;
        for (int i = 1; i < proc_count; i++)
            send_offsets[i] = send_offsets[i - 1] + send_counts[i - 1];
    }
    MPI_Scatterv(raw_data.data(), send_counts.data(), send_offsets.data(),
                 MPI_DOUBLE, proc_data.data(),
                 current_amount_of_elems, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    int start_x_index = rows_per_proc*proc_rank +
                        std::min(proc_rank, excess_rows);
    int x_index = start_x_index;
    int row_size = size + 1;
    for (int i = 0; i < current_amount_of_elems; i += row_size) {
        double coeff = proc_data[x_index + i];
        bool coeff_is_negative = coeff < 0;
        int free_member_index = i + row_size - 1;
        proc_data[free_member_index] /= coeff_is_negative ? -coeff : coeff;
        // handle everything except last number that is not a coefficient
        for (int j = i; j < i + row_size - 1; j++) {
            if (j != x_index + i) {
                proc_data[j] /= coeff_is_negative ? coeff : -coeff;
            } else {
                proc_data[j] = 0;
            }
        }
        x_index++;
    }
    std::vector<double> x(size);
    std::vector<double> old_x(size);
    std::vector<double> this_x;

    for (int i = 0; i < current_amount_of_elems; i += row_size) {
        int free_member_index = i + row_size - 1;
        this_x.push_back(proc_data[free_member_index]);
    }

    send_counts.assign(proc_count, rows_per_proc);
    for (int i = 0; i < excess_rows; i++)
        send_counts[i]++;
    send_offsets.assign(proc_count, 0);
    for (int i = 1; i < proc_count; i++)
        send_offsets[i] = send_offsets[i - 1] + send_counts[i - 1];


    MPI_Allgatherv(this_x.data(), this_x.size(), MPI_DOUBLE,
                   x.data(), send_counts.data(), send_offsets.data(),
                   MPI_DOUBLE, MPI_COMM_WORLD);

    old_x = x;
    double epsilon = 0.0001;
    bool global_stop = false;
    int step = 0;
    while (!global_stop) {
        if (step > 0) {
            MPI_Allgatherv(this_x.data(), this_x.size(), MPI_DOUBLE,
                           x.data(), send_counts.data(), send_offsets.data(),
                           MPI_DOUBLE, MPI_COMM_WORLD);
            global_stop = true;
            for (int i = 0; i < size - 1; i++) {
                if (std::abs(old_x[i] - x[i]) > epsilon) {
                    global_stop = false;
                }
            }
            old_x = x;
        }

        if (!global_stop) {
            this_x.assign(send_counts[proc_rank], 0);
            for (int i = 0; i < send_counts[proc_rank]; i++) {
                for (int j = i*row_size, x_index=0;
                        j < i*row_size+row_size-1; j++, x_index++) {
                    this_x[i] += proc_data[j]*x[x_index];
                }
                this_x[i] += proc_data[i*row_size+row_size - 1];
            }
        }
        step++;
    }
    return x;
}
