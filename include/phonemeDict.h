/*Wrapper for map ds containing key-value pairs of words
 *and their pronunciation which is given as an array of phonemes
 *
 *the dictionary comes from the cmu phoneme dictionary found here:
 *http://www.speech.cs.cmu.edu/cgi-bin/cmudict
 */

#ifndef PHONEME_H
#define PHONEME_H

#include <map>
#include <string>
#include <vector>

#define DICTIONARY_FILE "dict/dict.txt"
#define COMMENT_HEAD ";;;"

class PhonemeDict {
public:
  PhonemeDict();
  ~PhonemeDict();

  std::string* lookUp(std::string word);

  int getSize();

private:
  //<word,phoneme>
  std::map<std::string, std::string>* dict;

  void addWord(std::string w);

  char encode(std::string phoneme);
};


#endif //PHONEME_H
