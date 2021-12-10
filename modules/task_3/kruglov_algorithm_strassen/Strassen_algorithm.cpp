// Copyright 2021 Kruglov Aleksei
#include <mpi.h>
#include <algorithm>
#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include "../../../modules/task_3/kruglov_algorithm_strassen/Strassen_algorithm.h"

Matrix get_random_matrix(int height, int width, double max_number) {
    std::random_device device;
    std::mt19937 gen(device());
    Matrix matrix(height, std::vector<double>(width));
    std::uniform_real_distribution<> dis(-max_number, max_number);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = (dis(gen));
        }
    }
    return matrix;
}


Matrix reference_multiply(const Matrix& a, const Matrix& b) {
    Matrix res(a.size(), std::vector<double>(b[0].size()));
    for (std::size_t i = 0; i < a.size(); i++) {
        for (std::size_t j = 0; j < b[0].size(); j++) {
            for (std::size_t k = 0; k < a[0].size(); k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

Matrix parallel_multiply(const Matrix& a, const Matrix& b) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    int n = static_cast<int>(a.size());
    MPI_Bcast(reinterpret_cast<void*>(&n), 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n <= 2 && proc_rank == 0) {
        return reference_multiply(a, b);
    }
    // exit for other processes
    if (n <= 2) {
        return Matrix();
    }
    Matrix a11, a12, a21, a22;
    Matrix b11, b12, b21, b22;
    if (proc_rank == 0) {
        n = n / 2;
        a11 = Matrix(n, std::vector<double>(n));
        a12 = Matrix(n, std::vector<double>(n));
        a21 = Matrix(n, std::vector<double>(n));
        a22 = Matrix(n, std::vector<double>(n));

        b11 = Matrix(n, std::vector<double>(n));
        b12 = Matrix(n, std::vector<double>(n));
        b21 = Matrix(n, std::vector<double>(n));
        b22 = Matrix(n, std::vector<double>(n));
    }

    if (proc_rank == 0) {
        std::vector<Matrix> all;
        all = split(a);
        a11 = std::move(all[0]), a12 = std::move(all[1]), a21 = std::move(all[2]), a22 = std::move(all[3]);

        all = split(b);
        b11 = std::move(all[0]), b12 = std::move(all[1]), b21 = std::move(all[2]), b22 = std::move(all[3]);
    }
    Matrix p1, p2, p3, p4, p5, p6, p7;
    p1 = parallel_multiply(matrix_sum(a11, a22), matrix_sum(b11, b22));
    p2 = parallel_multiply(matrix_sum(a21, a22), b11);
    p3 = parallel_multiply(a11, matrix_sub(b12, b22));
    p4 = parallel_multiply(a22, matrix_sub(b21, b11));
    p5 = parallel_multiply(matrix_sum(a11, a12), b22);
    p6 = parallel_multiply(matrix_sub(a21, a11), matrix_sum(b11, b12));
    p7 = parallel_multiply(matrix_sub(a12, a22), matrix_sum(b21, b22));

    auto c11 = matrix_sum(matrix_sum(p1, p4), matrix_sub(p7, p5));
    auto c12 = matrix_sum(p3, p5);
    auto c21 = matrix_sum(p2, p4);
    auto c22 = matrix_sum(matrix_sub(p1, p2), matrix_sum(p3, p6));

    return merge(c11, c12, c21, c22);
}

std::vector<Matrix> split(const Matrix& a) {
    int n = static_cast<int>(a.size() / 2);
    std::vector<Matrix> result(4, Matrix(n));
    for (int i = 0; i < n; i++) {
        result[0][i] = { a[i].begin(), a[i].begin() + n };
        result[1][i] = { a[i].begin() + n, a[i].begin() + 2 * n };
        result[2][i] = { a[i + n].begin(), a[i + n].begin() + n };
        result[3][i] = { a[i + n].begin() + n, a[i + n].begin() + 2 * n };
    }
    return result;
}

Matrix merge(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d) {
    int n = static_cast<int>(a.size());
    Matrix result(n * 2, std::vector<double>(n * 2));
    for (int i = 0; i < n; i++) {
        result[i] = a[i];
        result[i].insert(result[i].end(), b[i].begin(), b[i].end());
        result[i + n] = c[i];
        result[i + n].insert(result[i + n].end(), d[i].begin(), d[i].end());
    }
    return result;
}

Matrix matrix_sum(const Matrix& a, const Matrix& b) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    int n = 0;
    if (proc_rank == 0) {
        n = static_cast<int>(a.size());
    }
    MPI_Bcast(reinterpret_cast<void*>(&n), 1, MPI_INT, 0, MPI_COMM_WORLD);
    Matrix cur_a, cur_b, res;
    if (proc_rank == 0) {
        int lines_per_proc = static_cast<int>(a.size() / proc_num);
        int above_average = static_cast<int>(a.size() % proc_num);
        int cur_lines_per_proc = lines_per_proc;
        if (proc_rank < above_average)
            cur_lines_per_proc++;
        // reserving for zero process
        int j = cur_lines_per_proc;
        for (int i = 1; i < proc_num; i++) {
            int cur_lines_per_proc = lines_per_proc;
            if (i < above_average)
                cur_lines_per_proc++;
            MPI_Send(reinterpret_cast<void*>(&cur_lines_per_proc), 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            for (int c = 0; c < cur_lines_per_proc; c++, j++) {
                MPI_Send(reinterpret_cast<const void*>(a[j].data()), n, MPI_DOUBLE,
                         i, c + 1, MPI_COMM_WORLD);
                MPI_Send(reinterpret_cast<const void*>(b[j].data()), n, MPI_DOUBLE,
                         i, c + 1, MPI_COMM_WORLD);
            }
        }
        res.assign(cur_lines_per_proc, std::vector<double>(n));
        for (int i = 0; i < cur_lines_per_proc; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = a[i][j] + b[i][j];
            }
        }
    } else {
        int h;
        MPI_Status* status = new MPI_Status();
        MPI_Recv(reinterpret_cast<void*>(&h), 1, MPI_INT, 0, 0, MPI_COMM_WORLD, status);
        cur_a.assign(h, std::vector<double>(n));
        cur_b.assign(h, std::vector<double>(n));
        for (int i = 0; i < h; i++) {
            MPI_Recv(reinterpret_cast<void*>(cur_a[i].data()), n,
                MPI_DOUBLE, 0, i + 1, MPI_COMM_WORLD, status);
            MPI_Recv(reinterpret_cast<void*>(cur_b[i].data()), n,
                MPI_DOUBLE, 0, i + 1, MPI_COMM_WORLD, status);
        }
        res.assign(h, std::vector<double>(n));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = cur_a[i][j] + cur_b[i][j];
            }
        }
        MPI_Send(reinterpret_cast<void*>(&h), 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        for (int i = 0; i < h; i++) {
            MPI_Send(reinterpret_cast<void*>(res[i].data()), n, MPI_DOUBLE, 0, i + 1, MPI_COMM_WORLD);
        }
    }
    Matrix all_res;
    if (proc_rank == 0) {
        all_res.assign(n, std::vector<double>(n));
        int j = 0;
        for (std::size_t i = 0; i < res.size(); i++, j++) {
            all_res[j] = std::move(res[i]);
        }
        for (int i = 1; i < proc_num; i++) {
            int h;
            MPI_Status* status = new MPI_Status();
            MPI_Recv(reinterpret_cast<void*>(&h), 1, MPI_INT, i, 0, MPI_COMM_WORLD, status);
            for (int c = 0; c < h; c++, j++) {
                MPI_Recv(reinterpret_cast<void*>(all_res[j].data()), n, MPI_DOUBLE, i,
                         c + 1, MPI_COMM_WORLD, status);
            }
        }
    }

    return all_res;
}

Matrix matrix_sub(const Matrix& a, const Matrix& b) {
    int proc_num, proc_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    int n = 0;
    if (proc_rank == 0) {
        n = static_cast<int>(a.size());
    }
    MPI_Bcast(reinterpret_cast<void*>(&n), 1, MPI_INT, 0, MPI_COMM_WORLD);
    Matrix cur_a, cur_b, res;
    if (proc_rank == 0) {
        int lines_per_proc = static_cast<int>(a.size() / proc_num);
        int above_average = static_cast<int>(a.size() % proc_num);
        int cur_lines_per_proc = lines_per_proc;
        if (proc_rank < above_average)
            cur_lines_per_proc++;
        // reserving for zero process
        int j = cur_lines_per_proc;
        for (int i = 1; i < proc_num; i++) {
            int cur_lines_per_proc = lines_per_proc;
            if (i < above_average)
                cur_lines_per_proc++;
            MPI_Send(reinterpret_cast<void*>(&cur_lines_per_proc), 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            for (int c = 0; c < cur_lines_per_proc; c++, j++) {
                MPI_Send(reinterpret_cast<const void*>(a[j].data()), n, MPI_DOUBLE,
                    i, c + 1, MPI_COMM_WORLD);
                MPI_Send(reinterpret_cast<const void*>(b[j].data()), n, MPI_DOUBLE,
                    i, c + 1, MPI_COMM_WORLD);
            }
        }
        res.assign(cur_lines_per_proc, std::vector<double>(n));
        for (int i = 0; i < cur_lines_per_proc; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = a[i][j] - b[i][j];
            }
        }
    } else {
        int h;
        MPI_Status* status = new MPI_Status();
        MPI_Recv(reinterpret_cast<void*>(&h), 1, MPI_INT, 0, 0, MPI_COMM_WORLD, status);
        cur_a.assign(h, std::vector<double>(n));
        cur_b.assign(h, std::vector<double>(n));
        for (int i = 0; i < h; i++) {
            MPI_Recv(reinterpret_cast<void*>(cur_a[i].data()), n,
                MPI_DOUBLE, 0, i + 1, MPI_COMM_WORLD, status);
            MPI_Recv(reinterpret_cast<void*>(cur_b[i].data()), n,
                MPI_DOUBLE, 0, i + 1, MPI_COMM_WORLD, status);
        }
        res.assign(h, std::vector<double>(n));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = cur_a[i][j] - cur_b[i][j];
            }
        }
        MPI_Send(reinterpret_cast<void*>(&h), 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        for (int i = 0; i < h; i++) {
            MPI_Send(reinterpret_cast<void*>(res[i].data()), n, MPI_DOUBLE, 0, i + 1, MPI_COMM_WORLD);
        }
    }
    Matrix all_res;
    if (proc_rank == 0) {
        all_res.assign(n, std::vector<double>(n));
        int j = 0;
        for (std::size_t i = 0; i < res.size(); i++, j++) {
            all_res[j] = std::move(res[i]);
        }
        for (int i = 1; i < proc_num; i++) {
            int h = 0;
            MPI_Status* status = new MPI_Status();
            MPI_Recv(reinterpret_cast<void*>(&h), 1, MPI_INT, i, 0, MPI_COMM_WORLD, status);
            for (int c = 0; c < h; c++, j++) {
                MPI_Recv(reinterpret_cast<void*>(all_res[j].data()), n, MPI_DOUBLE, i,
                    c + 1, MPI_COMM_WORLD, status);
            }
        }
    }

    return all_res;
}

bool is_equal(const Matrix& m1, const Matrix& m2, double threshold) {
    if (m1.size() != m2.size()) {
        return false;
    }
    for (std::size_t h = 0; h < m1.size(); h++) {
        if (m1[h].size() != m2[h].size()) {
            return false;
        }
        for (std::size_t w = 0; w < m1[h].size(); w++) {
            if (std::abs(m1[h][w] - m2[h][w]) > threshold) {
                return false;
            }
        }
    }
    return true;
}
