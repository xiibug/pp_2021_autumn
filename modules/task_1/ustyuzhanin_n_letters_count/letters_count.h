#pragma once

#include <string>
#include <mpi.h>
#include <random>

using namespace std;

int countLetters(string str);
int countLettersMPI(string str, int size);

string randomStr(int size);