/*Wrapper for map ds containing key-value pairs of words
 *and their pronunciation which is given as an array of phonemes
 *
 *the dictionary comes from the cmu phoneme dictionary found here:
 *http://www.speech.cs.cmu.edu/cgi-bin/cmudict
 */

#ifndef NOUNCER_H
#define NOUNCER_H

#include <map>
#include <string>
#include <vector>

#define DICTIONARY_FILE "dict/dict.txt"
#define COMMENT_HEAD ";;;"

class Nouncer {
public:
  Nouncer();
  ~Nouncer();

  std::string* lookUp(std::string word);

  int getSize();

private:
  std::map<std::string, std::string>* dict;

  void addWord(std::string w);

  char encode(std::string phoneme);
};


#endif // NOUNCER_H
