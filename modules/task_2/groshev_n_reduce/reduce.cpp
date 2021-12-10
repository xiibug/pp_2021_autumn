// Copyright 2021 Groshev Nikolay
#include "../../../modules/task_2/groshev_n_reduce/reduce.h"

void my_reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) {
	// 1 аргумент - буфер отправки данных от процесса, которых вызвал функцию
	// 2 аргумент - буфер хранения данных на процессе, который указан в качестве корневого (6 аргумент)
	// 3 аргумент - количество данных
	// 4 аргумент - тип данных
	// 5 аргумент - тип операции
	// 6 аргумент - корневой процесс
	// 7 аргумент - коммуникатор процессов
	int ProcNum;
	int ProcRank;
	MPI_Comm_size(comm, &ProcNum); // количество процессов внутри коммуникатора
	MPI_Comm_rank(comm, &ProcRank); // ранг текущего процесса

	if (op == MPI_SUM) { // если редьюс был вызван на операции суммирования элементов, вызываем функцию суммы, с остальными случаями аналогично
		sum(sendbuf, recvbuf, count, datatype, op, root, comm, ProcRank);
	}
	else if (op == MPI_PROD) {
		prod(sendbuf, recvbuf, count, datatype, op, root, comm, ProcRank);
	}
	else if (op == MPI_MAX) {
		max(sendbuf, recvbuf, count, datatype, op, root, comm, ProcRank);
	}
	else if (op == MPI_MIN) {
		min(sendbuf, recvbuf, count, datatype, op, root, comm, ProcRank);
	}
}

// функция суммирования
void sum(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int my_rank) {
	int ProcNum;
	int* buffer = new int[count]; // локальный буфер, будет логично заполнить его нулями
	for (int i = 0; i < count; i++) {
		buffer[i] = 0;
	}
	MPI_Comm_size(comm, &ProcNum); // количество процессов
	if (my_rank == root) { // если ранг равен рангу корневого процесса
		for (int j = 0; j < count; j++) { // в локальный буфер сохраняем данные корневого процесса
			static_cast<int*>(buffer)[j] += static_cast<int*>(sendbuf)[j];
		}
		for (int i = 1; i < ProcNum; i++) { // принимаем данные от всех процессов
			MPI_Recv(recvbuf, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);
			for (int j = 0; j < count; j++) { // пробегаемся по всему сообщению и суммируем в локальный буфер
				static_cast<int*>(buffer)[j] += static_cast<int*>(recvbuf)[j];
			}
		}
		for (int j = 0; j < count; j++) {
			static_cast<int*>(recvbuf)[j] = static_cast<int*>(buffer)[j]; // копируем данные в буфер, возвращающий результат
		}
	}
	else {
		MPI_Send(sendbuf, count, datatype, root, 0, comm); // если не корневой процесс, отправляем данные
	}
}

// описание других операций аналогично по смыслу

void prod(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int my_rank) {
	int ProcNum;
	int* buffer = new int[count];
	for (int i = 0; i < count; i++) {
		buffer[i] = 1;
	}
	MPI_Comm_size(comm, &ProcNum);
	if (my_rank == root) {
		for (int j = 0; j < count; j++) {
			static_cast<int*>(buffer)[j] *= static_cast<int*>(sendbuf)[j];
		}
		for (int i = 1; i < ProcNum; i++) {
			MPI_Recv(recvbuf, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);
			for (int j = 0; j < count; j++) {
				static_cast<int*>(buffer)[j] *= static_cast<int*>(recvbuf)[j];
			}
		}
		for (int j = 0; j < count; j++) {
			static_cast<int*>(recvbuf)[j] = static_cast<int*>(buffer)[j];
		}
	}
	else {
		MPI_Send(sendbuf, count, datatype, root, 0, comm);
	}
}

void max(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int my_rank) {
	int ProcNum;
	int* buffer = new int[count];
	for (int i = 0; i < count; i++) {
		buffer[i] = -2147483647;
	}
	MPI_Comm_size(comm, &ProcNum);
	if (my_rank == root) {
		for (int j = 0; j < count; j++) {
			if (static_cast<int*>(buffer)[j] < static_cast<int*>(sendbuf)[j]) {
				static_cast<int*>(buffer)[j] = static_cast<int*>(sendbuf)[j];
			}
		}
		for (int i = 1; i < ProcNum; i++) {
			MPI_Recv(recvbuf, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);
			for (int j = 0; j < count; j++) {
				if (static_cast<int*>(buffer)[j] < static_cast<int*>(recvbuf)[j]) {
					static_cast<int*>(buffer)[j] = static_cast<int*>(recvbuf)[j];
				}
			}
		}
		for (int j = 0; j < count; j++) {
			static_cast<int*>(recvbuf)[j] = static_cast<int*>(buffer)[j];
		}
	}
	else {
		MPI_Send(sendbuf, count, datatype, root, 0, comm);
	}
}

void min(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int my_rank) {
	int ProcNum;
	int* buffer = new int[count];
	for (int i = 0; i < count; i++) {
		buffer[i] = 2147483647;
	}
	MPI_Comm_size(comm, &ProcNum);
	if (my_rank == root) {
		for (int j = 0; j < count; j++) {
			if (static_cast<int*>(buffer)[j] > static_cast<int*>(sendbuf)[j]) {
				static_cast<int*>(buffer)[j] = static_cast<int*>(sendbuf)[j];
			}
		}
		for (int i = 1; i < ProcNum; i++) {
			MPI_Recv(recvbuf, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);
			for (int j = 0; j < count; j++) {
				if (static_cast<int*>(buffer)[j] > static_cast<int*>(recvbuf)[j]) {
					static_cast<int*>(buffer)[j] = static_cast<int*>(recvbuf)[j];
				}
			}
		}
		for (int j = 0; j < count; j++) {
			static_cast<int*>(recvbuf)[j] = static_cast<int*>(buffer)[j];
		}
	}
	else {
		MPI_Send(sendbuf, count, datatype, root, 0, comm);
	}
}