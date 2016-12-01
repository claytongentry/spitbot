/*
 * utils.h
 *
 * A class to hold generic utility functions
 */

#ifndef UTILS_H
#define UTILS_H

#include <locale>
#include <sstream>
#include <string>
#include <utility>

class Utils {
  public:
    static std::string allCaps(std::string word);
    static std::string flip(std::string text);
};

#endif // UTILS_H