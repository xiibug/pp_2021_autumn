#include "../../../modules/task_3/lakhov_k_optimization_params/optimization_params.h"

double f1(double x, double y){
    return pow(y - 1, 2) + pow(x, 2);
}

point sequentialCalc(double left_x, double right_x, double left_y, double right_y,
                     double(*func)(double x, double y)){
    double eps = 0.01;
    double n_max_value = 1000;
    double(*ptr)(double, double) = func;
    double r = 2;

    point result;
    point last_result = {0, 0, 0};
    std::set<doubleDimensionChar> set;

    result = singleDimensionMin(left_x, right_x, left_y, ptr);
    set.insert(doubleDimensionChar(result.x, result.y, result.z));
    last_result = result;

    result = singleDimensionMin(left_x, right_x, right_y, ptr);
    set.insert(doubleDimensionChar(result.x, result.y, result.z));

    if (result.z < last_result.z) { last_result = result;}

    int k = 2;
    bool stop = false;
    double mu, mu_current;
    double M;
    while(!stop && k < n_max_value){
        // calc mu and M
        mu = -1;
        auto i_value = set.begin();
        i_value++;
        auto i_previous_value = set.begin();
        while (i_value != set.end()) {
            mu_current = std::abs(static_cast<double>((i_value->functionValue - i_previous_value->functionValue) /
            (i_value->y - i_previous_value->y)));
            if (mu_current > mu) {mu = mu_current;}
            i_value++; i_previous_value++;
        }
        if (mu > 0) {
            M = r * mu;
        } else {
            M = 1;
        }

        // calc R(i)
        // R(i) = m(x(i) - x(i-1)) + (z(i) - z(i-1))^2/ m(x(i)-x(i-1)) - 2(z(i)-z(i-1))
        i_value = set.begin();
        i_value++;
        i_previous_value = set.begin();
        double R, current_r;
        R = std::numeric_limits<double>::lowest();

        auto maxRiter = set.begin();
        auto r_i_value_previous_max = set.begin();
        while (i_value != set.end()) {
            double delta_y = (i_value->y - i_previous_value->y);
            double a = M * delta_y;
            double b = pow((i_value->functionValue - i_previous_value->functionValue), 2) / a;
            double c = 2 * (i_value->functionValue - i_previous_value->functionValue);
            current_r = a + b - c;
            if (current_r > R) {
                R = current_r;
                maxRiter = i_value;
                r_i_value_previous_max = i_previous_value;
            }
            i_value++; i_previous_value++;
        }
        k++;
        // std::cout<<maxRiter->y<<" "<<r_i_value_previous_max->y<<std::endl;
        double new_y = 0.5 * (maxRiter->y + r_i_value_previous_max->y) -
        ((maxRiter->functionValue - r_i_value_previous_max->functionValue) / (2 * M));
        result = singleDimensionMin(left_x, right_x, new_y, ptr);
        set.insert(doubleDimensionChar(result.x, result.y, result.z));
        // std::cout<<new_y<<std::endl;
        if (result.z < last_result.z) {
            last_result = result;
        }
        if (maxRiter->y - r_i_value_previous_max->y <= eps) {
            stop = true;
        }
        // std::cout<<k<<" :("<<result.x<<" "<<result.y<<" "<<result.z<<")";
    }
    // std::cout<<" :("<<last_result.x<<" "<<last_result.y<<" "<<last_result.z<<")";
    return last_result;
}

point singleDimensionMin(double left_x, double right_x, double const_y, double(*func)(double x, double y)){
    int n_max_value = 1000;
    double eps_in_func = 0.01;
    double r = 2;

    point result;
    std::set<singleDimensionChar> set;


    double left_func_value = func(left_x, const_y);
    set.insert(singleDimensionChar(left_x, left_func_value));

    result.x = left_x;
    result.y = const_y;
    result.z = left_func_value;

    double right_func_value = func(right_x, const_y);
    set.insert(singleDimensionChar(right_x, right_func_value));

    if (result.z > right_func_value) {
        result.x = right_x;
        result.z = right_func_value;
    }

    int k = 2;
    auto maxRiter = set.begin();
    auto r_i_value_previous_max = set.begin();
    double mu, mu_current;
    double M;
    bool st_flag = false;
    while (!st_flag && k < n_max_value) {
        // calc mu and M
        mu = -1;
        auto i_value = set.begin();
        i_value++;
        auto i_previous_value = set.begin();
        while (i_value != set.end()) {
            mu_current = std::abs(static_cast<double>((i_value->functionValue - i_previous_value->functionValue) /
            (i_value->x - i_previous_value->x)));
            if (mu_current > mu) {mu = mu_current;}
            i_value++; i_previous_value++;
        }
        if (mu > 0) {
            M = r * mu;
        } else {
            M = 1;
        }
        // std::cout<<k<<" rank 0 total points  ";
        // for(auto &i : set){
        //         std::cout<<" "<<i.x;
        // }
        // std::cout<<std::endl;
        // calc R(i)
        // R(i) = m(x(i) - x(i-1)) + (z(i) - z(i-1))^2/ m(x(i)-x(i-1)) - 2(z(i)-z(i-1))
        i_value = set.begin();
        i_value++;
        i_previous_value = set.begin();
        double R, current_r;
        R = std::numeric_limits<double>::lowest();
        while (i_value != set.end()) {
            double delta_x = (i_value->x - i_previous_value->x);
            double a = M * delta_x;
            double b = pow((i_value->functionValue - i_previous_value->functionValue), 2) / a;
            double c = 2 * (i_value->functionValue - i_previous_value->functionValue);
            current_r = a + b - c;
            if (current_r > R) {
                R = current_r;
                maxRiter = i_value;
                r_i_value_previous_max = i_previous_value;
            }
            i_value++; i_previous_value++;
        }
        k++;
        double new_x = 0.5 * (maxRiter->x + r_i_value_previous_max->x) -
        ((maxRiter->functionValue - r_i_value_previous_max->functionValue) / (2 * M));
        // std::cout<<"rank 0 sent biggest R "<<R<<" on interval ["<<r_i_value_previous_max->x<<" "<<maxRiter->x<<"]"<<" with x="<<new_x<<std::endl;
        double new_func_value = func(new_x, const_y);
        set.insert(singleDimensionChar(new_x, new_func_value));
        if (result.z > new_func_value) {
            result.x = new_x;
            result.z = new_func_value;
        }
        if (maxRiter->x - r_i_value_previous_max->x <= eps_in_func) {
            st_flag = true;
        }

    }
    // std::cout<<" :("<<result.x<<" "<<result.y<<" "<<result.z<<")";
    return result;
}

point singleDimensionMinParallel(double left_x, double right_x, double const_y, double(*func)(double x, double y), int proc_count){
    int n_max_value = 1000;
    double eps_in_func = 0.01;
    double r = 2;

    std::vector<int> send_counts(proc_count, 0);
    std::vector<int> send_offsets(proc_count, 0);
    std::vector<double> proc_data;
    std::vector<double> raw_data;
    std::vector<double> proc_characteristics;
    std::set<pointSender> proc_set;

    point result;
    std::set<singleDimensionChar> set;


    double left_func_value = func(left_x, const_y);
    set.insert(singleDimensionChar(left_x, left_func_value));

    result.x = left_x;
    result.y = const_y;
    result.z = left_func_value;

    double right_func_value = func(right_x, const_y);
    set.insert(singleDimensionChar(right_x, right_func_value));

    if (result.z > right_func_value) {
        result.x = right_x;
        result.z = right_func_value;
    }

    int k = 2;
    double mu, mu_current;
    double M;
    bool st_flag = false;
    while (!st_flag && k < n_max_value) {
        // calc mu and M
        mu = -1;
        auto set_iter = set.begin();
        set_iter++;
        auto set_iter_previos = set.begin();
        while (set_iter != set.end()) {
            mu_current = std::abs(static_cast<double>((set_iter->functionValue - set_iter_previos->functionValue) /
            (set_iter->x - set_iter_previos->x)));
            if (mu_current > mu) {mu = mu_current;}
            set_iter++; set_iter_previos++;
        }
        if (mu > 0) {
            M = r * mu;
        } else {
            M = 1;
        }

        if((int)(set.size()) > proc_count){
            int flag = 0;
            MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(&M, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            set_iter = set.begin();
            raw_data.clear();
            while (set_iter != set.end()) {
                raw_data.push_back(set_iter->x);
                raw_data.push_back(set_iter->functionValue);
                set_iter++;
            }

            // std::cout<<k<<" rank 0 total points  to send";
            // for(auto &i : set){
            //     std::cout<<" "<<i.x;
            // }
            // std::cout<<std::endl;
            int intervals_count = set.size() - 1;
            int excess_intervals =  intervals_count % proc_count;
            int intervals_per_proc = intervals_count / proc_count;
            send_counts.clear();
            send_offsets.clear();
            send_counts.assign(proc_count, intervals_per_proc*2 + 2);
            send_offsets.assign(proc_count, 0);
            for (int i = 0; i < excess_intervals; i++)
                send_counts[i] += 2;
            for (int i = 1; i < proc_count; i++)
                send_offsets[i] = send_offsets[i - 1] - 2 + send_counts[i - 1];
            // std::cout<<k<<" rank 0 send counts  ";
            // for(auto &i : send_counts){
            //     std::cout<<" "<<i;
            // }
            // std::cout<<std::endl;
            // std::cout<<k<<" rank 0 send offsets  ";
            // for(auto &i : send_offsets){
            //     std::cout<<" "<<i;
            // }
            // std::cout<<std::endl;
            for (int i = 1; i < proc_count; i++){
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
            // std::cout<<k<<" rank 0 got points  ";
            // for(auto &i : proc_set){
            //     std::cout<<" "<<i.variable;
            // }
            // std::cout<<std::endl;
            auto proc_set_iter = proc_set.begin();
            proc_set_iter++;
            auto proc_set_iter_previous = proc_set.begin();
            double R, current_r;
            auto local_r_iter = proc_set.begin();
            auto local_r_prev_iter = proc_set.begin();
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
                    local_r_prev_iter = proc_set_iter_previous;
                }
                proc_set_iter++; proc_set_iter_previous++;
            }
            // std::cout<<"rank 0 sent biggest R "<<R<<" on interval ["<<local_r_prev_iter->variable<<" "<<local_r_iter->variable<<"]"<<std::endl;
            std::vector<double> send_v;
            send_v.push_back(R);
            send_v.push_back(local_r_prev_iter->variable);
            send_v.push_back(local_r_prev_iter->functionValue);
            send_v.push_back(local_r_iter->variable);
            send_v.push_back(local_r_iter->functionValue);
            send_v.push_back(0);
            // std::cout<<R<<" "<<local_r_prev_iter->variable<<" "<<local_r_prev_iter->functionValue<<" "<<local_r_iter->variable<<" "<<local_r_iter->functionValue<<" "<<0<<std::endl;
            proc_characteristics.assign(6*proc_count, 0);
            MPI_Gather(send_v.data(), 6, MPI_DOUBLE, proc_characteristics.data(), 6, MPI_DOUBLE, 0,
                     MPI_COMM_WORLD);
            // std::cout<<"in 0 from 0"<<proc_characteristics[0]<<" "<<proc_characteristics[1]<<" "<<proc_characteristics[2]<<" "<<proc_characteristics[3]<<" "<<proc_characteristics[4]<<std::endl;
            // std::cout<<"in 0 from 1"<<proc_characteristics[6]<<" "<<proc_characteristics[7]<<" "<<proc_characteristics[8]<<" "<<proc_characteristics[9]<<" "<<proc_characteristics[10]<<std::endl;
            std::set<singleDimensionR> total_r_set;
            for(int i=0; i<(int)(proc_characteristics.size()); i+=6){
                total_r_set.insert(singleDimensionR(proc_characteristics[i], proc_characteristics[i+1], proc_characteristics[i+2],
                    proc_characteristics[i+3], proc_characteristics[i+4], proc_characteristics[i+5]));
            }

            auto maxRiter = total_r_set.begin();
            k++;
            double new_x = 0.5 * (maxRiter->variableFirst + maxRiter->variableSecond) -
            ((maxRiter->functionValueSecond - maxRiter->functionValueFirst) / (2 * M));
            // std::cout<<"total biggest R "<<R<<" on interval ["<<maxRiter->variableFirst<<" "<<maxRiter->variableSecond<<"]"<<" with x="<<new_x<<" proc="<<maxRiter->rank<<std::endl;

            double new_func_value = func(new_x, const_y);
            set.insert(singleDimensionChar(new_x, new_func_value));

            if (result.z > new_func_value) {
                result.x = new_x;
                result.z = new_func_value;
            }
            // std::cout<<k<<" ("<<result.x<<" "<<result.y<<" "<<result.z<<")"<<" on variables "<<maxRiter->variable <<" "<<r_i_value_previous_max->variable<<std::endl;
            if (maxRiter->variableSecond - maxRiter->variableFirst <= eps_in_func) {
                st_flag = true;
                // int flag = 111;
                // MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
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
            double new_x = 0.5 * (maxRiter->x + r_i_value_previous_max->x) -
            ((maxRiter->functionValue - r_i_value_previous_max->functionValue) / (2 * M));
            double new_func_value = func(new_x, const_y);
            set.insert(singleDimensionChar(new_x, new_func_value));
            if (result.z > new_func_value) {
                result.x = new_x;
                result.z = new_func_value;
            }
            if (maxRiter->x - r_i_value_previous_max->x <= eps_in_func) {
                st_flag = true;
                }
            }
        }
    return result;
}