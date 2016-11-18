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
  word = allCaps(word);
  /*TODO: maybe we should just have it build it in this case
   *though I don't know when that condition would be true*/
  if(dict->size() == 0) {
    std::cout << "build the dictionary first" << std::endl;
    return nullptr;
  }
  else {
    try {
      std::cout << "trying word " << word << std::endl;
      return &(*dict).at(word);
    }
    catch (const std::out_of_range& oor) {
      std::cout << "word "<<word<<" not found in dictionary" << std::endl;
      std::cout << "returning gravy..." << std::endl;
      return &(*dict).at("GRAVY");
    }
  }
}

void PhonemeDict::buildDict() {
  //read in file
  std::ifstream file("dict/dict.txt");

  if (file) {
    std::cout << "building..." << std::endl;
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
    std::cout << "done!" << std::endl;
  }
  else {
    std::cerr << "unable to load dictionary";
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

std::string PhonemeDict::allCaps(std::string word) {
  //to upper case
  std::locale loc;
  for (std::string::size_type i = 0; i < word.length(); ++i) {
    word[i] = std::toupper(word[i],loc);
  }
  return word;

}
