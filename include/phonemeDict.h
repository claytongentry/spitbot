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

#define DICTIONARY_FILE = "./dict/dict.txt";

class PhonemeDict {
public:
  PhonemeDict();
  std::string* lookUp(std::string word);

private:
  std::map<std::string,std::string*>* dict;
  void buildDict();
};


#endif //PHONEME_H
