// Copyright 2021 Burdukov Mikhail
#include <mpi.h>
#include "../../../modules/task_1/burdukov_m_scalar_multiplication/scalar_multiplication.hpp"

std::vector<int>
generate_random_vector(const int size) {
  std::vector<int> vec(size);
  std::random_device dev;
  std::mt19937 gen(dev());
  for ( int i = 0 ; i < size ; i++ )
    vec[i] = gen() % 100;
  return vec;
}

int
non_parallel_scalar_muliply(const std::vector<int>& first ,
                  const std::vector<int>& second , int vlen) {
  int ans = 0;
  for ( int ind = 0; ind < vlen ; ind++ )
    ans+= first[ind] * ((second.size() <= static_cast<size_t>(ind))
        ? 0 : second[ind]);
  return ans;
}

int
scalar_muliply(const std::vector<int>& first , const std::vector<int>& second ,
            const int vlen) {
  int prank , pcount;
  std::vector<int> loc_f , loc_s;
  MPI_Comm_size(MPI_COMM_WORLD , &pcount);
  MPI_Comm_rank(MPI_COMM_WORLD , &prank);
  int global_answer = 0;
  int block = vlen/pcount;
  // Sending
  if ( prank == 0 ) {
    for ( int ind = 1 ; ind < pcount ; ind++ ) {
      int start = block*ind +vlen%pcount;
      // std::cout<<"send "<<start<<' '<<block<<std::endl;
      MPI_Send(first.data() + start , block , MPI_INT , ind ,
              0 , MPI_COMM_WORLD);
      MPI_Send(second.data() + start , block , MPI_INT , ind
              , 0 , MPI_COMM_WORLD);
    }
    int zero_size = block + vlen%pcount;
    loc_f.resize(zero_size); loc_s.resize(zero_size);
    loc_f = std::vector<int>(first.data() , first.data() +zero_size);
    loc_s = std::vector<int>(second.data() , second.data() + zero_size);
  } else {
    MPI_Status status;
    loc_f.resize(block); loc_s.resize(block);
    MPI_Recv(loc_f.data() , block , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &status);
    MPI_Recv(loc_s.data() , block , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &status);
  }
  // Calculations
  int local_answer = 0;
  if ( loc_f.size() != 0 && loc_s.size() != 0 ) {
    for ( size_t ind = 0 ; ind < loc_f.size() ; ind++ )
      local_answer += loc_f[ind] * ((loc_s.size() <= ind)
                      ? 0: loc_s[ind]);
  }
  // Merge result;
  MPI_Reduce(reinterpret_cast<void*>(&local_answer) ,
              reinterpret_cast<void*>(&global_answer) , 1 , MPI_INT ,
              MPI_SUM , 0 , MPI_COMM_WORLD);
  return global_answer;
}


