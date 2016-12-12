/*
 * utils.h
 *
 * A class to hold generic utility functions
 */

#ifndef UTILS_H
#define UTILS_H

#include <locale>
#include <random>
#include <sstream>
#include <string>
#include <utility>

class Utils {
  public:
    static std::string allCaps(std::string s);
    static std::string noCaps(std::string s);
    static std::string removePunc(std::string s);
    static std::string flip(std::string text);
    static int randInRangeExclude(int start, int end, int exclude);
};

#endif // UTILS_H
