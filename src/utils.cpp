/*
 * Utils implementation
 */

#include "utils.h"
it /*
 * Convert a string to all caps.
 */
std::string Utils::allCaps(std::string s) {
  std::locale loc;

  for (std::string::size_type i = 0; i < s.length(); ++i) {
    s[i] = std::toupper(s[i],loc);
  }

  return s;
}

/*
 *Remove punctuation from a string
 */
std::string Utils::removePunc(std::string s) {
  std::locale loc;
  for (int i = 0; i < s.length(); ++i) {
    if (std::ispunct(s[i],loc)) {
      s.erase(i,1);
    }
  }
  return s;
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
