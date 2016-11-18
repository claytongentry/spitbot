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

#define DICTIONARY_FILE "dict/dict.txt";

class PhonemeDict {
public:
  PhonemeDict();
  ~PhonemeDict();

  std::vector<std::string>* lookUp(std::string word);

  int getSize();

private:
  std::map<std::string,std::vector<std::string>>* dict;

  void buildDict();
  void addWord(std::string w);

  std::string allCaps(std::string word);
};


#endif //PHONEME_H
