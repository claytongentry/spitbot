#include <iostream>
#include <fstream>
#include <sstream>

#include "phonemeDict.h"
#include "utils.h"

/*
 * Assembles the map<word,phoneme> dictionary by reading one line at a time,
 * separating the word from the pronunciation, encoding the phoneme, and
 * putting the pair in the map
 */
PhonemeDict::PhonemeDict() {

  dict = new std::map<std::string, std::string>;

  std::ifstream file(DICTIONARY_FILE);

  if (file) {
    std::string line;

    while (std::getline(file,line)) {
      if (line.substr(0,3) == COMMENT_HEAD) {
        continue;
      }
      else {
        addWord(line);
      }
    }
  }
  else {
    std::cerr << "Unable to load dictionary" << std::endl;
  }
}

PhonemeDict::~PhonemeDict() {
  dict->erase(dict->begin(), dict->end());
  delete dict;
}

/*
 * Given a string, return a pointer to the associated phoneme string
 * or the phoneme of "gravy" if the string is not found.
 */
std::string* PhonemeDict::lookUp(std::string word) {
  try {
    return &(dict->at(Utils::allCaps(word)));
  }
  catch (const std::out_of_range& oor) {
    return &(dict->at("GRAVY"));
  }
}

/*
 * Maps a phoneme dictionary entry to a
 * <std::string word, std::string encoded_phonemes> pair
 * and inserts in the dictionary.
 */
void PhonemeDict::addWord(std::string line) {
  std::istringstream ss(line);
  std::string word;
  std::string encoded_phonemes;
  std::string phoneme;

  ss >> word;

  while (ss >> phoneme) {
    char encoded_phoneme = encode(phoneme);
    encoded_phonemes.push_back(encoded_phoneme);
  }

  std::pair<std::string, std::string> word_phonemes(word, encoded_phonemes);
  dict->insert(word_phonemes);
}

char PhonemeDict::encode(std::string phoneme) {
  char code = '\0';

  if      (phoneme.substr(0,2) == "AA") code = 'A';
  else if (phoneme.substr(0,2) == "AE") code = 'B';
  else if (phoneme.substr(0,2) == "AH") code = 'C';
  else if (phoneme.substr(0,2) == "AO") code = 'D';
  else if (phoneme.substr(0,2) == "AW") code = 'E';
  else if (phoneme.substr(0,2) == "AY") code = 'F';
  else if (phoneme             == "B")  code = 'G';
  else if (phoneme             == "CH") code = 'H';
  else if (phoneme             == "D")  code = 'I';
  else if (phoneme             == "DH") code = 'J';
  else if (phoneme.substr(0,2) == "EH") code = 'K';
  else if (phoneme.substr(0,2) == "ER") code = 'L';
  else if (phoneme.substr(0,2) == "EY") code = 'M';
  else if (phoneme             == "F")  code = 'N';
  else if (phoneme             == "G")  code = 'O';
  else if (phoneme             == "HH") code = 'P';
  else if (phoneme.substr(0,2) == "IH") code = 'Q';
  else if (phoneme.substr(0,2) == "IY") code = 'R';
  else if (phoneme             == "JH") code = 'S';
  else if (phoneme             == "K")  code = 'T';
  else if (phoneme             == "L")  code = 'U';
  else if (phoneme             == "M")  code = 'V';
  else if (phoneme             == "N")  code = 'W';
  else if (phoneme             == "NG") code = 'X';
  else if (phoneme.substr(0,2) == "OW") code = 'Y';
  else if (phoneme.substr(0,2) == "OY") code = 'Z';
  else if (phoneme             == "P")  code = 'a';
  else if (phoneme             == "R")  code = 'b';
  else if (phoneme             == "S")  code = 'c';
  else if (phoneme             == "SH") code = 'd';
  else if (phoneme             == "T")  code = 'e';
  else if (phoneme             == "TH") code = 'f';
  else if (phoneme.substr(0,2) == "UH") code = 'g';
  else if (phoneme.substr(0,2) == "UW") code = 'h';
  else if (phoneme             == "V")  code = 'i';
  else if (phoneme             == "W")  code = 'j';
  else if (phoneme             == "Y")  code = 'k';
  else if (phoneme             == "Z")  code = 'l';
  else if (phoneme             == "ZH") code = 'm';
  else
    std::cerr << "Could not identify phoneme " << phoneme << std::endl;

  return code;
}

int PhonemeDict::getSize(){
  return dict->size();
}
