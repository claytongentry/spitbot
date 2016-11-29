/*
 * Denouncer implementation
 */

#include "denouncer.h"

// Denouncer::Denouncer() {
//   dict = new std::map<std::string, std::vector<std::string>>;
//
// }

Denouncer::~Denouncer() {
  dict->erase(dict->begin(), dict->end());
  delete dict;
}

// void Denouncer::addOrUpdate(std::string pron, std::string word) {
//
// }

/*
 * Maps a phoneme dictionary entry to a
 * <std::string pronunciation, std::string word> pair
 * and inserts in the dictionary.
 */
void Denouncer::addPronunciation(std::string pron, std::string word) {
  std::pair<std::string, std::string> denounced_pair(pron, word);

  dict->insert(denounced_pair);
}
