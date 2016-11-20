/*
 * Utils implementation
 */

#include <utility>

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
