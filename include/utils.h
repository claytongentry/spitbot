/*
 * utils.h
 *
 * A class to hold generic utility functions
 */

#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <ctime>
#include <locale>
#include <sstream>
#include <string>
#include <utility>

class Utils {
  public:
    static std::string allCaps(std::string s);
    static std::string noCaps(std::string s);
    static std::string removePunc(std::string s);
    static std::string flip(std::string text);
    static int random();
};

#endif // UTILS_H
