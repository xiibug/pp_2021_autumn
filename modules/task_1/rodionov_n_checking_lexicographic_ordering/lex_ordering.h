#include <iostream>
#ifndef LEX_ORDERING


char* get_random_string(int len);
int basic_compare(const char c1, const char c2);
int seq_lex_compare(const char* str1, const char* str2, int size);
int omp_lex_compare(const char* str1, const char* str2, int len);


#endif // !LEX_ORDERING
