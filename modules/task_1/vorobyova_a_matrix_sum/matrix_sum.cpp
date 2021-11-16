// Copyright 2018 Nesterov Alexander
#include <mpi.h>
#include <random>
#include "../../../modules/task_1/vorobyova_a_matrix_sum/matrix_sum.h"


int* getRandomMatrix(int size) { // получить матрицу заполненную случайными числами
    std::random_device dev;
    std::mt19937 gen(dev()); // генератор случайных чисел Нестерова
    int* matrix = new int[size]; // создать массив
    for (int  i = 0; i < size; i++) {
        matrix[i] = gen() % 100; // заполнить массив числами не больше 100
    }
    return matrix;
}

int getSequentialSum(int* matrix, int size) { // последовательный алгоритм
    int sum = 0; // переменная для суммы
    for (int i = 0; i < size; i++) {
        sum += matrix[i]; // складываем все элементы
    }
    return sum;
}

int getParallelSum(int* matrix, int msize) { // параллельный алгоритм
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size); // получить количество процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // получить ранг данного процесса
    const int delta  = msize / size; // размер куска
    const int remainder = msize % size; // размер остатка

    if (rank == 0) { // отправить матрицу по кускам
        for (int proc = 1; proc < size; proc++) { // в цикле начинаем с 1 процесса, 0 не трогаем
            MPI_Send(matrix + proc * delta + remainder, delta, // первый элемент + размер куска * номер процесса
                        MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }

    int* local_matrix = nullptr; // создаем локальную матрицу и записываем нее пустой указатель 

    if (rank == 0) {
        local_matrix = new int[delta + remainder]; // инициализируем матрицу для хранения бОльшего куска чтобы вместить остаток
    } else {
        local_matrix = new int[delta]; // размер куска для остальных процессов
    }

    if (rank == 0) {
        for (int i = 0; i < delta + remainder; i++) {
            local_matrix[i] = matrix[i]; // в цикле копируем в локульную матрицу процесса 0 данные из matrix размера delta + remainder
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_matrix, delta, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); // во всех остальных процессах делаем Recv в локальную матрицу
    }

    int global_sum = 0; // создаем переменную для глобальной суммы
    int local_sum = 0; // создаем переменную для локальной суммы

    if (rank == 0) {
        local_sum = getSequentialSum(local_matrix, delta + remainder); // считаем сумму в локальной матрице процесса 0
    } else {
        local_sum = getSequentialSum(local_matrix, delta); // считаем сумму в локальных матрицах остальных процессов
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // взять все локальные суммы и сложить в глобальную сумму
    return global_sum;
}
