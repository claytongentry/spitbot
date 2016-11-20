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
  //std::string phonemes;

  //read the word
  ss >> word;

  //read the phonemes into the vector
  std::string temp;
  while (ss >> temp) {
    phonemes.push_back(temp);
    //phoenems.push_back(encode(temp))
  }

  //put the <word,phoneme> pair in the map
  (*dict).insert(std::pair<std::string, std::vector<std::string>>(word,phonemes));
  //(*dict).insert(std::pair<std::string, std::string>(word,phonemes));
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

char PhonemeDict::encode(std::string phoneme) {
  char code = '0';
  if (phoneme == "AA") code = 'a';
  else if (phoneme =="AE") code = 'b';
  else if (phoneme =="AH") code = 'c';
  else if (phoneme == "AO") code = 'd';
  else if (phoneme == "AW") code = 'e';
  else if (phoneme == "AY") code = 'f';
  else if (phoneme == "B") code = 'g';
  else if (phoneme == "CH") code = 'h';
  else if (phoneme == "D") code = 'i';
  else if (phoneme == "DH") code = 'j';
  else if (phoneme == "EH") code = 'k';
  else if (phoneme == "ER") code = 'l';
  else if (phoneme == "EY") code = 'm';
  else if (phoneme == "F") code = 'n';
  else if (phoneme == "G") code = 'o';
  else if (phoneme == "HH") code = 'p';
  else if (phoneme == "IH") code = 'q';
  else if (phoneme == "IY") code = 'r';
  else if (phoneme == "JH") code = 's';
  else if (phoneme == "K") code = 't';
  else if (phoneme == "L") code = 'u';
  else if (phoneme == "M") code = 'v';
  else if (phoneme == "N") code = 'w';
  else if (phoneme == "NG") code = 'x';
  else if (phoneme == "OW") code = 'y';
  else if (phoneme == "OY") code = 'z';
  else if (phoneme == "P") code = 'A';
  else if (phoneme == "R") code = 'B';
  else if (phoneme == "S") code = 'C';
  else if (phoneme == "SH") code = 'D';
  else if (phoneme == "T") code = 'E';
  else if (phoneme == "TH") code = 'F';
  else if (phoneme == "UH") code = 'G';
  else if (phoneme == "UW") code = 'H';
  else if (phoneme == "V") code = 'I';
  else if (phoneme == "W") code = 'J';
  else if (phoneme == "Y") code = 'K';
  else if (phoneme == "Z") code = 'L';
  else if (phoneme == "ZH") code = 'M';

  return code;
}
