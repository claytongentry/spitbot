#include "phonemeDict.h"
#include <iostream>
#include <fstream>
#include <sstream>

PhonemeDict::PhonemeDict(){
  dict = new std::map<std::string, std::vector<std::string>>;
  buildDict();
}

std::vector<std::string>* PhonemeDict::lookUp(std::string word) {
  if(dict->size() == 0) {
    std::cout<<"build the dictionary first"<<std::endl;
    return nullptr;
  }
  else {
    return &(*dict)[word];
  }
}

void PhonemeDict::buildDict() {
  std::ifstream file("dict/dict.txt");

  if (file) {
    std::cout<<"building..."<<std::endl;
    std::string line;
    while (std::getline(file,line)) {
      if (line.substr(0,3) == ";;;") {
        continue;
      }
      else {
        //std::cout<<"adding word"<<std::endl;
        addWord(line);
      }
    }
    std::cout<<"done!"<<std::endl;
  }
  else {
    std::cerr<<"unable to load dictionary";
  }
}

void PhonemeDict::addWord(std::string line) {
  std::istringstream ss(line);
  std::string word;
  std::vector<std::string> phonemes;

  //read the word
  ss >> word;

  //read the phonemes into the
  std::string temp;
  while (ss >> temp) {
    phonemes.push_back(temp);
  }

  (*dict).insert(std::pair<std::string, std::vector<std::string>>(word,phonemes));
}

int PhonemeDict::getSize(){
  return dict->size();
}
