/*
 * Denouncer implementation
 */

#include "denouncer.h"

Denouncer::Denouncer() {
  dict = new std::vector<std::pair<std::string, std::string>>;
}

Denouncer::~Denouncer() {
  dict->erase(dict->begin(), dict->end());
  delete dict;
}

/*
 * Maps a phoneme dictionary entry to a
 * <std::string pronunciation, std::string word> pair
 * and inserts in the dictionary.
 */
void Denouncer::addPronunciation(std::string pron, std::string word) {
  std::pair<std::string, std::string> denounced_pair(pron, word);

  dict->push_back(denounced_pair);

  //maintain sorting
  std::sort(dict->begin(), dict->end());
}
