// Copyright 2021 Nazarov Nikita
#include "../../../modules/task_2/nazarov_n_star_topology/star_topology.h"

MPI_Comm Star(const MPI_Comm comm) {
	int ProcNum, ProcRank;
	MPI_Comm star;

	MPI_Comm_size(comm, &ProcNum);
	MPI_Comm_rank(comm, &ProcRank);
	
	std::vector<int> index(ProcNum);
	std::vector<int> edges((ProcNum - 1) * 2);

	index[0] = ProcNum - 1;
	for (int i = 1; i < ProcNum; i++) {
		index[i] = index[i - 1] + 1;
	}

	for (int i = 0; i < (ProcNum - 1) * 2; i++) {
		if (i < ProcNum - 1) {
			edges[i] = i + 1;
		}
		else {
			edges[i] = 0;
		}
	}

	MPI_Graph_create(comm, ProcNum, index.data(), edges.data(), false, &star);
	return star;
}

bool IsStar(MPI_Comm star) {
	int test;
	MPI_Topo_test(star, &test);
	if (test != MPI_GRAPH) {
		return false;
	}

	int process, edg;
	MPI_Graphdims_get(star, &process, &edg);
	if (edg != (process - 1) * 2) {
		return false;
	}

	std::vector<int>index(process);
	std::vector<int>edges((process - 1) * 2);
	MPI_Graph_get(star, process, (process - 1) * 2, index.data(), edges.data());

	for (int i = 0; i < process; i++) {
		if (index[i] != process - 1 + i) {
			return false;
		}
	}

	for (int i = 0; i < (process - 1) * 2; i++) {
		if ((i < (process - 1) && edges[i] != i + 1) || 
			(i >= (process - 1) && edges[i] != 0)) {
			return false;
		}
	}
	return true;
}
