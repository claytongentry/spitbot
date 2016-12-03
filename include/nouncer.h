/*
 * nouncer.h
 *
 * A class for mapping words to their pronunciations
 *
 * The class uses the Carnegie Mellon Phoneme Dictionary, found here:
 * http://www.speech.cs.cmu.edu/cgi-bin/cmudict
 * Phoneme sets are encoded and reversed to optimize rhyme matching.
 */

#ifndef NOUNCER_H
#define NOUNCER_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "utils.h"

#define DICTIONARY_FILE "dict/dict.txt"
#define COMMENT_HEAD ";;;"

class Nouncer {
public:
  Nouncer();
  ~Nouncer();

  // Returns the nounce of the given word
  std::string* lookUp(std::string word);

  // Encodes the phoneme string to a nounce
  char encode(std::string phoneme);

  // Returns the number of entries in the data structure
  int getSize();

  // Adds a word with its nounce to the data structure
  void addWord(std::string w);

private:
  std::map<std::string, std::string>* dict;
};

#endif // NOUNCER_H
