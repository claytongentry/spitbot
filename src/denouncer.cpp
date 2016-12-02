/*
 * Denouncer implementation
 */

#include "denouncer.h"
#include <iostream>

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

/*
 * Returns the index of a nounce/word pair in the dictionary
 * by binary search.  If the nounce is not found returns
 * index as if it were in the dictionary.
 */
int Denouncer::getIndex(std::string nounce) {
  std::cout<<"looking for "<<nounce<<std::endl;

  int index = dict->size()/2;

  std::cout<<dict->at(index).first<<":"<<dict->at(index).second<<std::endl;

  if (dict->at(index).first == nounce){
    std::cout<<"found "<<nounce<<"at "<<index<<std::endl;
    return index;
  }
  else if (dict->at(index).first < nounce) {
    std::cout<<nounce<<" is greater than the mid"<<std::endl;
    return binarySearch(nounce, index + 1, dict->size() - 1);
  }
  else {
    std::cout<<nounce<<" is less than the mid"<<std::endl;
    return binarySearch(nounce, 0, index - 1);
  }
}

int Denouncer::binarySearch(std::string nounce, int start, int end) {
  //if the range has shrunk to 0 (or less?) return the index
  //this is because even if dict->at(index) != nounce, if nounce should appear
  //at this location
  if (start >= end) return start;

  int index = (end - start) / 2;

  if (dict->at(index).first == nounce) return index;
  else if (dict->at(index).first < nounce) return binarySearch(nounce, index + 1, end);
  else return binarySearch(nounce, start, index - 1);
}
