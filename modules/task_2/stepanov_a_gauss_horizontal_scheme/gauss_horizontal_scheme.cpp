// Copyright 2021 Stepanov Alexander
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../../../modules/task_2/stepanov_a_gauss_horizontal_scheme/gauss_horizontal_scheme.h"


std::vector<double> generateSLE(std::vector<double>* matrix_sle,
    std::vector<double>* vector_result,
    std::vector<double>::size_type number_unknows) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<> urd(-50, 50);
    std::vector<double> expected_solution(number_unknows, 0);

    for (std::vector<double>::size_type i = 0; i < number_unknows; i++) {
        auto random = urd(gen);
        expected_solution[i] = random == 0.0 ? 1.0 : random;
        for (std::vector<double>::size_type j = 0; j < number_unknows; j++) {
            (*matrix_sle)[i * number_unknows + j] = urd(gen);
        }
    }

    for (std::vector<double>::size_type i = 0; i < number_unknows; i++) {
        (*vector_result)[i] = 0;
        for (std::vector<double>::size_type j = 0; j < number_unknows; j++) {
            (*vector_result)[i] += (*matrix_sle)[i * number_unknows + j] * expected_solution[j];
        }
    }

    return expected_solution;
}

std::vector<double> sequentialGaussScheme(const std::vector<double>& matrix_sle,
    const std::vector<double>& vector_result,
    std::vector<double>::size_type number_unknows) {
    std::vector<double> modiffed_sle(matrix_sle);
    std::vector<double> modiffed_vector_res(vector_result);
    std::vector<double> solution(number_unknows, 0);

    for (std::vector<double>::size_type i = 0; i < number_unknows; i++) {
        for (std::vector<double>::size_type j = i + 1; j < number_unknows; j++) {
            double coeff = modiffed_sle[j * number_unknows + i] / modiffed_sle[i * number_unknows + i];
            modiffed_vector_res[j] -= modiffed_vector_res[i] * coeff;
            for (std::vector<double>::size_type k = i; k < number_unknows; k++) {
                modiffed_sle[j * number_unknows + k] -= modiffed_sle[i * number_unknows + k] * coeff;
            }
            modiffed_sle[j * number_unknows + i] = 0;
        }
    }

    for (auto i = number_unknows - 1; i > 0; i--) {
        double coeff = modiffed_vector_res[i];
        for (auto j = number_unknows - 1; j > i; j--) {
            coeff -= modiffed_sle[i * number_unknows + j] * solution[j];
        }
        solution[i] = coeff / modiffed_sle[i * number_unknows + i];
    }

    double coeff = modiffed_vector_res[0];
    for (std::vector<double>::size_type i = 1; i < number_unknows; i++) {
        coeff -= modiffed_sle[i] * solution[i];
    }
    solution[0] = coeff / modiffed_sle[0];

    return solution;
}

std::vector<double> parallelGauss(const std::vector<double>& matrix_sle,
    const std::vector<double>& vector_result,
    std::vector<double>::size_type number_unknows) {
    return std::vector<double>{};
}
