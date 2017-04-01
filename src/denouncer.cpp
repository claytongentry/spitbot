/*
 * Denouncer implementation
 */

#include "denouncer.h"

Denouncer::Denouncer() {}

Denouncer::~Denouncer() {}

/*
 * Maps a phoneme dictionary entry to a
 * <std::string pronunciation, std::string word> pair
 * and inserts in the dictionary.
 */
void Denouncer::addNounce(std::string nounce, std::string word) {
  /*TODO:  I don't like the name denounce_pair, when the pair is the nounce and the word
           I know that its in the denouncer but i think it should be nouncePair*/
  std::pair<std::string, std::string> denounced_pair(nounce, word);

  // look for pair in dict
  if (find(denounced_pair)) return;

  dict.push_back(denounced_pair);

  // maintain sorting
  std::sort(dict.begin(), dict.end());
}

/*
 * Returns the index of a nounce/word pair in the dictionary
 * by binary search. If the nounce is not found returns
 * index as if it were in the dictionary.
 */
int Denouncer::getIndex(std::string nounce) {

  int index = dict.size()/2;

  if (dict.at(index).first == nounce) return index;
  else if (dict.at(index).first < nounce) return binarySearch(nounce, index + 1, dict.size() - 1);
  else return binarySearch(nounce, 0, index - 1);
}

/*
 * Returns a word based on a given index
 */
std::string Denouncer::lookUp(int index) {
  if (index >= 0 && index < dict.size()) {
    return dict.at(index).second;
  }
  else return "_0";
}


int Denouncer::binarySearch(std::string nounce, int start, int end) {
  //if the range has shrunk to 0 (or less?) return the index
  //this is because even if dict.at(index) != nounce, if nounce should appear
  //at this location
  if (start >= end) return start;

  int index = start + (end - start) / 2;

  if (dict.at(index).first == nounce) return index;
  else if (dict.at(index).first < nounce) return binarySearch(nounce, index + 1, end);
  else return binarySearch(nounce, start, index - 1);
}

bool Denouncer::find(std::pair<std::string, std::string> denounced_pair) {
  return std::binary_search(dict.begin(), dict.end(), denounced_pair);
}
