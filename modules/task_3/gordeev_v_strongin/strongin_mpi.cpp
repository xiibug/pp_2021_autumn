// Copyright 2021 Gordeev Viktor
#include "./strongin_mpi.h"
#include <random>
#include <algorithm>

double R(const double& _m_small, const double& _z_curr,
    const double& _z_prev, const double& _x_curr, const double& _x_prev) {
    return _m_small * (_x_curr - _x_prev) + (pow(_z_curr - _z_prev, 2)
        / (_m_small * (_x_curr - _x_prev))) - (2 * (_z_curr + _z_prev));
}

double M(const double& _z_curr, const double& _z_prev,
    const double& _x_curr, const double& _x_prev) {
    return abs((_z_curr - _z_prev) / (_x_curr - _x_prev));
}

double StronginParallel(const double _left, const double _right,
    const int _N_max, const double _Eps, int procs, int rank) {
    std::vector<std::list<double>> parallel_z;
    std::vector<std::list<double>> parallel_x;
    parallel_x.resize(procs);
    parallel_z.resize(procs);
    segment opt_value;
    double out;

    opt_value.yi = StronginSeq(_left + (_right - _left) * (rank) / procs,
        _left + (_right - _left) * (rank+1) / procs, _N_max, _Eps);
    opt_value.yj = func(opt_value.yi);
    MPI_Allreduce(&opt_value.yi, &out, 1, MPI_DOUBLE,
        MPI_MIN, MPI_COMM_WORLD);
    return out;
}

double StronginSeq(const double _left, const double _right,
    const int _N_max, const double _Eps) {
    double curr_left = _left;
    double curr_right = _right;
    double r = 2.;

    double z_begin = func(curr_left);
    double z_end = func(curr_right);
    double temp = 0.;
    int k = 1;
    int new_size;
    double M_big, m_small = 1.;
    int R_max_index = 0;
    double new_point;
    double R_max_mpi;
    double M_max_mpi;

    std::list<double> z;
    std::list<double> x;
    std::list<double> M_vector;
    std::list<double> R_vector;

    segment val_z;
    segment arg_x;

    std::list<double>::iterator place_M, place_R;
    std::list<double>::iterator iter_x, iter_z, iter_R, iter_M;

    M_big = M(z_end, z_begin, curr_right, curr_left);
    MPI_Allreduce(&M_big, &M_max_mpi, 1, MPI_DOUBLE,
        MPI_MIN, MPI_COMM_WORLD);
    m_small = (M_big == 0) ? 1 : r * M_big;

    new_point = (curr_right + curr_left)
        / 2 - (z_end - z_begin) / (2 * m_small);

    x.push_back(curr_left);
    x.push_back(new_point);
    x.push_back(curr_right);

    iter_x = x.begin();
    for (int i = 0; i < 3; i++) {
    z.push_back(func(*iter_x++));
    }

    iter_z = z.begin();
    iter_x = x.begin();

    {
    for (int i = 1; i < 3; i++) {
        val_z.yi = *iter_z++;
        val_z.yj = *iter_z;
        arg_x.yi = *iter_x++;
        arg_x.yj = *iter_x;
        M_vector.push_back(M(val_z.yj, val_z.yi, arg_x.yj, arg_x.yi));
    }

    if (M_max_mpi < M_vector.back()) M_max_mpi = M_vector.back();
    M_big = M_max_mpi;

    m_small = (M_big == 0) ? 1 : r * M_big;

    R_max_index = 1;

    iter_z = z.begin();
    iter_x = x.begin();
    for (int i = 1; i < 3; i++) {
    val_z.yi = *iter_z++;
    val_z.yj = *iter_z;
    arg_x.yi = *iter_x++;
    arg_x.yj = *iter_x;

    temp = R(m_small, val_z.yj, val_z.yi, arg_x.yj, arg_x.yi);
    MPI_Allreduce(&temp, &R_max_mpi, 1, MPI_DOUBLE,
        MPI_MIN, MPI_COMM_WORLD);
    R_vector.push_back(temp);
    if (i == 1) M_max_mpi = temp;

    if (M_max_mpi < temp) {
        M_max_mpi = temp;
        R_max_index = i;
    }
    }

    iter_z = z.begin();
    iter_x = x.begin();

    for (int i = 0; i < R_max_index; i++) {
    iter_z++;
    iter_x++;
    }

    curr_right = *iter_x;
    curr_left = *--iter_x;
    }

    while (k < _N_max && (abs(curr_left - curr_right) > _Eps)) {
    new_size = 2 + k;

    iter_z = z.begin();
    iter_x = x.begin();

    for (register int i = 0; i < R_max_index; i++) {
    iter_z++;
    iter_x++;
    }

    val_z.yj = *iter_z--;
    val_z.yi = *iter_z++;


    new_point = (curr_right + curr_left)
        / 2 - (val_z.yj - val_z.yi) / (2 * m_small);

    z.insert(iter_z, func(new_point));
    x.insert(iter_x, new_point);

    iter_z = z.begin();
    iter_x = x.begin();
    place_M = M_vector.begin();
    place_R = R_vector.begin();

    for (int i = 0; i < R_max_index - 1; i++) {
    iter_z++;
    iter_x++;
    if (i == R_max_index - 1) break;
    place_M++;
    place_R++;
    }

    for (int i = 0; i < 2; i++) {
    val_z.yi = *iter_z++;
    val_z.yj = *iter_z;
    arg_x.yi = *iter_x++;
    arg_x.yj = *iter_x;
    if (i == 0) M_vector.insert(place_M, M(val_z.yj,
        val_z.yi, arg_x.yj, arg_x.yi));
    else
        *place_M = M(val_z.yj, val_z.yi, arg_x.yj, arg_x.yi);
    }

    iter_M = M_vector.begin();

    double max = *iter_M;
    temp = M_vector.back();

    for (int i = 0; i < new_size - 1; i++) {
    if (max < temp) max = temp;
    temp = *++iter_M;
    }
    M_big = max;

    m_small = (M_big == 0) ? 1 : r * M_big;

    iter_z = z.begin(); iter_x = x.begin();

    R_max_index = 1;
    place_R = R_vector.begin();

    for (int i = 0; i < new_size; i++) {
    val_z.yi = *iter_z++;
    val_z.yj = *iter_z;
    arg_x.yi = *iter_x++;
    arg_x.yj = *iter_x;
    if (i == 0)
        R_vector.insert(place_R, R(m_small,
            val_z.yj, val_z.yi, arg_x.yj, arg_x.yi));
    else
        *place_R++ = R(m_small, val_z.yj, val_z.yi, arg_x.yj, arg_x.yi);
    }

    iter_R = R_vector.begin();
    max = *iter_R;
    for (register int i = 1; i < new_size; i++) {
    temp = *++iter_R;
    if (max < temp) {
    max = temp;
    R_max_index = i + 1;
    }
    }

    iter_x = x.begin();
    iter_z = z.begin();

    for (register int i = 0; i < R_max_index; i++) {
    iter_z++;
    iter_x++;
    }

    curr_right = *iter_x;
    curr_left = *--iter_x;
    ++k;
    }

    return curr_right;
}

double func(const double& _x) {
    return 2 * sin(3 * _x) + 3 * cos(5 * _x);
}
