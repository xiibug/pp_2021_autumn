#ifndef MODULES_TEST_TASK1_LEVEDEV_A_UNIQUE_CHARS_UNIQUE_CHARS_H_
#define MODULES_TEST_TASK1_LEVEDEV_A_UNIQUE_CHARS_UNIQUE_CHARS_H_

#include <string>

std::string getRandomString(size_t size);
int UniqueCharsSequential(const std::string& str1, const std::string& str2);
int UniqueCharsParallel(const std::string& str1, const std::string& str2);

#endif  // MODULES_TEST_TASK1_LEVEDEV_A_UNIQUE_CHARS_UNIQUE_CHARS_H_
