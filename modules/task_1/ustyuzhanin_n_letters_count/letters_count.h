// Copyright 2021 Ustyuzhanin Nikita
#pragma once

#include <mpi.h>
#include <string>
#include <random>

using std::string;

int countLetters(string str);
int countLettersMPI(string str, int size);

string randomStr(int size);
