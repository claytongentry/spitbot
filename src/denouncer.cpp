/*
 * Denouncer implementation
 */

#include "denouncer.h"

Denouncer::Denouncer() {
  dict = new std::map<std::string, std::string>;
}

/*
 * Maps a phoneme dictionary entry to a
 * <std::string pronunciation, std::string word> pair
 * and inserts in the dictionary.
 */
void Denouncer::addWord(std::string word) {
  std::string pronunciation = *Nouncer::lookUp(word);
  std::pair<std::string, std::string> denounced_pair(pronunciation, word);

  dict->insert(denounced_pair);
}
