/*
 * Utils implementation
 */

#include "utils.h"

/*
 * Convert a string to all caps.
 */
std::string Utils::allCaps(std::string string) {
  std::locale loc;

  for (std::string::size_type i = 0; i < string.length(); ++i) {
    string[i] = std::toupper(string[i],loc);
  }

  return string;
}

/*
 * Reverses a string while preserving individual words
 */
std::string Utils::flip(std::string str) {
  std::string out;
  std::istringstream buffer(str);

  for ( auto i  = std::istream_iterator<std::string>(buffer);
             i != std::istream_iterator<std::string>();
             ++i )
    out = *i + ' ' + out;

  return out;
}
