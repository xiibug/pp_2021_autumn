// "Copyright [2021] <Borisov Maxim>"

#include "../../../modules/task_1/borisov_m_scalar_vector_product/scalar_vector_product.h"
#include <mpi.h>
#include <random>
#include <numeric>
#include <iterator>

int sequential_product(const std::vector<int>& vector_a,
        const std::vector<int>& vector_b) {
    if (vector_a.size() != vector_b.size())
        return -1;
    int result = 0;
    for (std::vector<int>::size_type i = 0; i < vector_a.size(); i++) {
        result += vector_a[i] * vector_b[i];
    }
    return result;
}

int sequential_product(int* vector_a, int* vector_b, int size) {
    int result = 0;
    for (std::vector<int>::size_type i = 0; i < size; i++) {
        result += vector_a[i] * vector_b[i];
    }
    return result;
}

int sequential_product_std(const std::vector<int>& vector_a,
        const std::vector<int>&  vector_b) {
    int result = std::inner_product(vector_a.begin(),
        vector_a.end(), vector_b.begin(), 0);
    return result;
}

std::vector<int> get_random_vector(int size) {
    std::vector<int> vector(size);
    std::random_device r_device;
    std::mt19937 rand_r(r_device());
    for (int i = 0; i < size; i++) {
        vector[i] = rand_r() % 100;
    }
    return vector;
}


int parallel_product(std::vector<int> vector_a, std::vector<int> vector_b) {
    if (vector_a.size() != vector_b.size())
        return -1;
    int size = vector_a.size();
    int proc_count = 0;
    int proc_rank = 0;
    int dummy = 0;
    int result = 0;
    int local_result = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int local_size = size / proc_count; 
    std::vector<int> loc_a(local_size);
    std::vector<int> loc_b(local_size);
  if (proc_rank == 0) {
       std::cout << "SIZE: " << proc_count << std::endl;
       if (size % proc_count != 0) {
           for(int i = size - size % proc_count; i < size; i++) {
               loc_a.push_back(vector_a[i]);
               loc_b.push_back(vector_b[i]);
           }
       }
   }

   MPI_Scatter(vector_a.data(), local_size, MPI_INT, loc_a.data(), local_size, 
           MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Scatter(vector_b.data(), local_size, MPI_INT, loc_b.data(), local_size, 
           MPI_INT, 0, MPI_COMM_WORLD);

    local_result = sequential_product_std(loc_a, loc_b);

    MPI_Reduce(&local_result, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    return result;
}
