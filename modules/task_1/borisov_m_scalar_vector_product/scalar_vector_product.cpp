#include "scalar_vector_product.h"
#include "mpi.h"
#include <random>
#include <numeric>

int sequential_product(const std::vector<int>& vector_a, const std::vector<int>& vector_b) {
	int result = 0;
	for (auto i = 0; i < vector_a.size(); i++) {
		result += vector_a[i] * vector_b[i];
	}
	return result;
}

int sequential_product_std(const std::vector<int>& vector_a, const std::vector<int>&  vector_b) {
	int result = std::inner_product(vector_a.begin(), vector_a.end(),vector_b.begin(), 0);
	return result;
}

std::vector<int> get_random_vector(int size) {
	std::vector<int> vector(size);
	std::random_device r_device;
	std::mt19937 rand(r_device());
	for(int i = 0; i < size; i++) {
		vector[i] = rand() % 100;
	}
	return vector;

}

int parallel_product(const std::vector<int>& vector_a, const std::vector<int>&  vector_b) {
	int proc_count = 0;
	int proc_rank = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
}
