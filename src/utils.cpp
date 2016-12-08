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

  for (int i = s.length(); i >= 0; --i) {
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
 * Get a random number from within a range
 */
int Utils::randInRange(int start, int end) {
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(start, end);

  return distr(eng);
}
