#include "phonemeDict.h"
#include "iostream"

PhonemeDict::PhonemeDict(){
  buildDict();
}

std::string* PhonemeDict::lookUp(std::string word) {
  std::string* pron = new std::string[1];
  pron[0] = "aba";
  return pron;
}

void PhonemeDict::buildDict(){
  dict = new std::map<std::string, std::string*>;
}
