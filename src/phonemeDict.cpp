#include "phonemeDict.h"
#include <iostream>
#include <fstream>
#include <sstream>

PhonemeDict::PhonemeDict(){
  dict = new std::map<std::string, std::vector<std::string>>;
  buildDict();
}

PhonemeDict::~PhonemeDict(){
  dict->erase(dict->begin(), dict->end());
  delete dict;
}

//given a string returns a pointer to the associated phoneme
//vector, null if not found
std::vector<std::string>* PhonemeDict::lookUp(std::string word) {
  /*TODO: the dictionary is all upper case, so we should change whatever
    *is to also be upper case*/
  /*TODO: maybe we should just have it build it in this case
   *though I don't know when that condition would be true*/
  if(dict->size() == 0) {
    std::cout<<"build the dictionary first"<<std::endl;
    return nullptr;
  }
  else {
    return &(*dict)[word];
  }
}

void PhonemeDict::buildDict() {
  //read in file
  std::ifstream file("dict/dict.txt");

  if (file) {
    std::cout<<"building..."<<std::endl;
    std::string line;

    //parse by line
    while (std::getline(file,line)) {
      //if not an entry skip
      if (line.substr(0,3) == ";;;") {
        continue;
      }
      else {
        addWord(line);
      }
    }
    std::cout<<"done!"<<std::endl;
  }
  else {
    std::cerr<<"unable to load dictionary";
  }
}

//add an entry from the dictionary to the map ds
void PhonemeDict::addWord(std::string line) {
  std::istringstream ss(line);
  std::string word;
  std::vector<std::string> phonemes;

  //read the word
  ss >> word;

  //read the phonemes into the vector
  std::string temp;
  while (ss >> temp) {
    phonemes.push_back(temp);
  }

  //put the <word,phoneme> pair in the map
  (*dict).insert(std::pair<std::string, std::vector<std::string>>(word,phonemes));
}

int PhonemeDict::getSize(){
  return dict->size();
}
