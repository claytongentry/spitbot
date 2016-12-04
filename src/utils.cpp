/*
 * Utils implementation
 */

#include "utils.h"

/*
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
 * Convert a string to all lower case.
 */
std::string Utils::noCaps(std::string s) {
  std::locale loc;

  for (std::string::size_type i = 0; i < s.length(); ++i) {
    s[i] = std::tolower(s[i],loc);
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

/*
 * Returns a random number between 1 and 10
 */
int Utils::random() {
  return rand() % 10 + 1;
}
