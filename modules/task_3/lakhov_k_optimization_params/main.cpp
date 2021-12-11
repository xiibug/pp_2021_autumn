// Copyright 2021 Lakhov Kirill
#define _USE_MATH_DEFINES

#include <gtest/gtest.h>
#include <iostream>
#include "./optimization_params.h"
#include <gtest-mpi-listener.hpp>

TEST(Global_Optimization_MPI, Test_1) {

}
TEST(Global_Optimization_MPI, Test_2) {

}
TEST(Global_Optimization_MPI, Test_3) {

}
TEST(Global_Optimization_MPI, Test_4) {

}
TEST(Global_Optimization_MPI, Test_5) {

}

int main(int argc, char** argv) {
    // ::testing::InitGoogleTest(&argc, argv);
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    // ::testing::TestEventListeners& listeners =
    //     ::testing::UnitTest::GetInstance()->listeners();
    // listeners.Release(listeners.default_result_printer());
    // listeners.Release(listeners.default_xml_generator());
    // listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    // return RUN_ALL_TESTS();
    std::vector<int> send_counts(size, 0);
    std::vector<int> send_offsets(size, 0);
    std::vector<double> proc_data;
    std::vector<double> raw_data;
    std::vector<double> proc_characteristics;
    std::set<pointSender> proc_set;

    double left_x = -1;
    double right_x = 1;
    double left_y = -2;
    double right_y = 2;
    double(*func)(double, double) = f1;
    // int n_max_value = 1000;
    // double eps_in_func = 0.01;
    // double r = 2;

    if(rank == 0){

        double eps = 0.01;
        double n_max_value = 1000;
        double r = 2;
        int flag = 0;

        point result;
        point last_result;
        std::set<doubleDimensionChar> set;

        result = singleDimensionMinParallel(left_x, right_x, left_y, func, size);
        last_result = result;
        std::cout<<" ("<<result.x<<" "<<result.y<<" "<<result.z<<")"<<std::endl;
        set.insert(doubleDimensionChar(result.x, result.y, result.z));


        result = singleDimensionMinParallel(left_x, right_x, right_y, func, size);
        std::cout<<" ("<<result.x<<" "<<result.y<<" "<<result.z<<")"<<std::endl;
        set.insert(doubleDimensionChar(result.x, result.y, result.z));
        if (result.z < last_result.z) { last_result = result;}

        int k = 2;
        bool stop = false;
        double mu, mu_current;
        double M;
        while(!stop && k < n_max_value){
           // calc mu and M
            mu = -1;
            auto set_iter = set.begin();
            set_iter++;
            auto set_iter_previos = set.begin();
            while (set_iter != set.end()) {
                mu_current = std::abs(static_cast<double>((set_iter->functionValue - set_iter_previos->functionValue) /
                (set_iter->y - set_iter_previos->y)));
                if (mu_current > mu) {mu = mu_current;}
                set_iter++; set_iter_previos++;
            }
            if (mu > 0) {
                M = r * mu;
            } else {
                M = 1;
            }

            if((int)(set.size()) > size){
                MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Bcast(&M, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
                set_iter = set.begin();
                raw_data.clear();
                while (set_iter != set.end()) {
                    raw_data.push_back(set_iter->y);
                    raw_data.push_back(set_iter->functionValue);
                    set_iter++;
                }


                int intervals_count = set.size() - 1;
                int excess_intervals =  intervals_count % size;
                send_counts.clear();
                send_offsets.clear();
                send_counts.assign(size, intervals_count*2);
                send_offsets.assign(size, 0);
                for (int i = 0; i < excess_intervals; i++)
                    send_counts[i] += 2;
                for (int i = 1; i < size; i++)
                    send_offsets[i] = send_offsets[i - 1] - 2 + send_counts[i - 1];

                for (int i = 1; i < size; i++){
                    int send_size = send_counts[i];
                    MPI_Send(&send_size, 1, MPI_INT, i,0, MPI_COMM_WORLD);
                }

                proc_data.clear();
                proc_data.assign(send_counts[0], 0);
                MPI_Scatterv(raw_data.data(), send_counts.data(), send_offsets.data(),
                    MPI_DOUBLE, proc_data.data(),
                    send_counts[0], MPI_DOUBLE, 0, MPI_COMM_WORLD);

                proc_set.clear();
                for(int i=0; i<(int)(proc_data.size()); i+=2){
                    proc_set.insert(pointSender(proc_data[i], proc_data[i+1]));
                }

                auto proc_set_iter = proc_set.begin();
                proc_set_iter++;
                auto proc_set_iter_previous = proc_set.begin();
                double R, current_r;
                auto local_r_iter = proc_set.begin();
                R = std::numeric_limits<double>::lowest();
                while (proc_set_iter != proc_set.end()) {
                    double delta_x = (proc_set_iter->variable - proc_set_iter_previous->variable);
                    double a = M * delta_x;
                    double b = pow((proc_set_iter->functionValue - proc_set_iter_previous->functionValue), 2) / a;
                    double c = 2 * (proc_set_iter->functionValue - proc_set_iter_previous->functionValue);
                    current_r = a + b - c;
                    if (current_r > R) {
                        R = current_r;
                        local_r_iter = proc_set_iter;
                    }
                    proc_set_iter++; proc_set_iter_previous++;
                }

                std::vector<double> send_v;
                send_v.push_back(R);
                send_v.push_back(local_r_iter->variable);
                send_v.push_back(local_r_iter->functionValue);
                proc_characteristics.assign(3*size, 0);
                MPI_Gather(send_v.data(), 3, MPI_DOUBLE, proc_characteristics.data(), 3, MPI_DOUBLE, 0,
                        MPI_COMM_WORLD);

                std::set<singleDimensionR> total_r_set;
                for(int i=0; i<(int)(proc_characteristics.size()); i+=3){
                    total_r_set.insert(singleDimensionR(proc_characteristics[i], proc_characteristics[i+1], proc_characteristics[i+2]));
                }

                auto maxRiter = total_r_set.begin();
                maxRiter++;
                auto r_i_value_previous_max = maxRiter;
                k++;

                double new_y = 0.5 * (maxRiter->variable + r_i_value_previous_max->variable) -
                ((maxRiter->functionValue - r_i_value_previous_max->functionValue) / (2 * M));

                result = singleDimensionMinParallel(left_x, right_x, new_y, func, size);
                set.insert(doubleDimensionChar(result.x, result.y, result.z));
                std::cout<<k<<" ("<<result.x<<" "<<result.y<<" "<<result.z<<")"<<std::endl;
                if (result.z < last_result.z) {
                    last_result = result;
                }
                if (maxRiter->variable - r_i_value_previous_max->variable <= eps) {
                    stop = true;
                    flag = 111;
                    MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
                }

            }else{
                set_iter = set.begin();
                set_iter++;
                set_iter_previos = set.begin();
                double R, current_r;
                auto maxRiter = set_iter;
                auto r_i_value_previous_max = set_iter_previos;
                R = std::numeric_limits<double>::lowest();
                while (set_iter != set.end()) {
                    double delta_x = (set_iter->x - set_iter_previos->x);
                    double a = M * delta_x;
                    double b = pow((set_iter->functionValue - set_iter_previos->functionValue), 2) / a;
                    double c = 2 * (set_iter->functionValue - set_iter_previos->functionValue);
                    current_r = a + b - c;
                    if (current_r > R) {
                        R = current_r;
                        maxRiter = set_iter;
                        r_i_value_previous_max = set_iter_previos;
                    }
                    set_iter++; set_iter_previos++;
                }
                k++;
                double new_y = 0.5 * (maxRiter->y + r_i_value_previous_max->y) -
                ((maxRiter->functionValue - r_i_value_previous_max->functionValue) / (2 * M));

                result = singleDimensionMinParallel(left_x, right_x, new_y, func, size);
                set.insert(doubleDimensionChar(result.x, result.y, result.z));
                if (result.z < last_result.z) {
                    last_result = result;
                }
                if (maxRiter->y - r_i_value_previous_max->y <= eps) {
                    stop = true;
                    flag = 111;
                    MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
                }
            }
        }
        std::cout<<" :("<<last_result.x<<" "<<last_result.y<<" "<<last_result.z<<")";
    }else{
        int flag;
        while(true){
            MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
            if(flag == 111){
                break;
            }
            double M;
            MPI_Bcast(&M, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            int recived_size;
            MPI_Recv(&recived_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            proc_data.clear();
            proc_data.assign(recived_size, 0);
            MPI_Scatterv(raw_data.data(), send_counts.data(), send_offsets.data(),
                    MPI_DOUBLE, proc_data.data(),
                    recived_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            proc_set.clear();
            for(int i=0; i<(int)(proc_data.size()); i+=2){
                proc_set.insert(pointSender(proc_data[i], proc_data[i+1]));
            }

            auto i_value = proc_set.begin();
            i_value++;
            auto i_previous_value = proc_set.begin();
            double R, current_r;
            R = std::numeric_limits<double>::lowest();
            auto local_r_iter = proc_set.begin();
            while (i_value != proc_set.end()) {
                double delta_x = (i_value->variable - i_previous_value->variable);
                double a = M * delta_x;
                double b = pow((i_value->functionValue - i_previous_value->functionValue), 2) / a;
                double c = 2 * (i_value->functionValue - i_previous_value->functionValue);
                current_r = a + b - c;
                if (current_r > R) {
                    R = current_r;
                    local_r_iter = i_value;
                }
                i_value++;
                i_previous_value++;
            }
            std::vector<double> send;
            send.push_back(R);
            send.push_back(local_r_iter->variable);
            send.push_back(local_r_iter->functionValue);

            MPI_Gather(send.data(), 3, MPI_DOUBLE, proc_characteristics.data(), 3, MPI_DOUBLE, 0,
                        MPI_COMM_WORLD);
            }
    }

    MPI_Finalize();
}