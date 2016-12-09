/*
 * Nouncer Implementation
 */

#include "nouncer.h"

/*
 * Assembles the map<word,phoneme> dictionary by reading one line at a time,
 * separating the word from the pronunciation, encoding the phoneme, and
 * putting the pair in the map
 */
Nouncer::Nouncer() {

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

Nouncer::~Nouncer() {
  dict->erase(dict->begin(), dict->end());
  delete dict;
}

/*
 * Given a string, return a pointer to the associated nounce
 * or the nounce of "gravy" if the string is not found.
 */
std::string* Nouncer::lookUp(std::string word) {
  try {
    return &(dict->at(Utils::allCaps(word)));
  }
  catch (const std::out_of_range& oor) {
    std::string pronunciation = soundItOut(word);
    addWord(pronunciation);
    return &(dict->at(Utils::allCaps(word)));
  }
}

std::string Nouncer::soundItOut(std::string word) {
  std::string pronunciation = Utils::allCaps(word);

  for (int i = 0; i < string.length(); i++);

  return pronunciation;
}

/*
 * TODO: Let's encode outside this and pass in the nounce
 *
 * Maps a phoneme dictionary entry to a
 * <std::string word, std::string nounce> pair
 * and inserts in the dictionary.
 */
void Nouncer::addWord(std::string line) {
  std::istringstream ss(line);
  std::string word;
  std::string nounce;
  std::string phoneme;

  ss >> word;

  while (ss >> phoneme) {
    char encoded_phoneme = encode(phoneme);
    nounce.push_back(encoded_phoneme);
  }

  std::reverse(nounce.begin(), nounce.end());

  std::pair<std::string, std::string> word_phonemes(word, nounce);
  dict->insert(word_phonemes);
}

/*
 * Encodes the phoneme string as a nounce
 */
char Nouncer::encode(std::string phoneme) {
  char code = '\0';

  if      (phoneme == "AA")  code = ' ';
  else if (phoneme == "AA0") code = '!';
  else if (phoneme == "AA1") code = '\"';
  else if (phoneme == "AA2") code = '#';
  else if (phoneme == "AE")  code = '$';
  else if (phoneme == "AE0") code = '%';
  else if (phoneme == "AE1") code = '&';
  else if (phoneme == "AE2") code = '(';
  else if (phoneme == "AH")  code = ')';
  else if (phoneme == "AH0") code = '*';
  else if (phoneme == "AH1") code = '+';
  else if (phoneme == "AH2") code = ',';
  else if (phoneme == "AO")  code = '-';
  else if (phoneme == "AO0") code = '.';
  else if (phoneme == "AO1") code = '/';
  else if (phoneme == "AO2") code = '0';
  else if (phoneme == "AW")  code = '1';
  else if (phoneme == "AW0") code = '2';
  else if (phoneme == "AW1") code = '3';
  else if (phoneme == "AW2") code = '4';
  else if (phoneme == "AY")  code = '5';
  else if (phoneme == "AY0") code = '6';
  else if (phoneme == "AY1") code = '7';
  else if (phoneme == "AY2") code = '8';
  else if (phoneme == "B")   code = '9';
  else if (phoneme == "CH")  code = ':';
  else if (phoneme == "D")   code = ';';
  else if (phoneme == "DH")  code = '<';
  else if (phoneme == "EH")  code = '=';
  else if (phoneme == "EH0") code = '>';
  else if (phoneme == "EH1") code = '?';
  else if (phoneme == "EH2") code = '@';
  else if (phoneme == "ER")  code = 'A';
  else if (phoneme == "ER0") code = 'B';
  else if (phoneme == "ER1") code = 'C';
  else if (phoneme == "ER2") code = 'D';
  else if (phoneme == "EY")  code = 'E';
  else if (phoneme == "EY0") code = 'F';
  else if (phoneme == "EY1") code = 'G';
  else if (phoneme == "EY2") code = 'H';
  else if (phoneme == "F")   code = 'I';
  else if (phoneme == "G")   code = 'J';
  else if (phoneme == "HH")  code = 'K';
  else if (phoneme == "IH")  code = 'L';
  else if (phoneme == "IH0") code = 'M';
  else if (phoneme == "IH1") code = 'N';
  else if (phoneme == "IH2") code = 'O';
  else if (phoneme == "IY")  code = 'P';
  else if (phoneme == "IY0") code = 'Q';
  else if (phoneme == "IY1") code = 'R';
  else if (phoneme == "IY2") code = 'S';
  else if (phoneme == "JH")  code = 'T';
  else if (phoneme == "K")   code = 'U';
  else if (phoneme == "L")   code = 'V';
  else if (phoneme == "M")   code = 'W';
  else if (phoneme == "N")   code = 'X';
  else if (phoneme == "NG")  code = 'Y';
  else if (phoneme == "OW")  code = 'Z';
  else if (phoneme == "OW0") code = 'a';
  else if (phoneme == "OW1") code = 'b';
  else if (phoneme == "OW2") code = 'c';
  else if (phoneme == "OY")  code = 'd';
  else if (phoneme == "OY0") code = 'e';
  else if (phoneme == "OY1") code = 'f';
  else if (phoneme == "OY2") code = 'g';
  else if (phoneme == "P")   code = 'h';
  else if (phoneme == "R")   code = 'i';
  else if (phoneme == "S")   code = 'j';
  else if (phoneme == "SH")  code = 'k';
  else if (phoneme == "T")   code = 'l';
  else if (phoneme == "TH")  code = 'm';
  else if (phoneme == "UH")  code = 'n';
  else if (phoneme == "UH0") code = 'o';
  else if (phoneme == "UH1") code = 'p';
  else if (phoneme == "UH2") code = 'q';
  else if (phoneme == "UW")  code = 'r';
  else if (phoneme == "UW0") code = 's';
  else if (phoneme == "UW1") code = 't';
  else if (phoneme == "UW2") code = 'u';
  else if (phoneme == "V")   code = 'v';
  else if (phoneme == "W")   code = 'w';
  else if (phoneme == "Y")   code = 'y';
  else if (phoneme == "Z")   code = 'z';
  else if (phoneme == "ZH")  code = '{';
  else
    std::cerr << "Could not identify phoneme " << phoneme << std::endl;

  return code;
}

int Nouncer::getSize() {
  return dict->size();
}

void Nouncer::print(std::string filename) {
  std::ofstream of(filename);
  for (auto it = dict->begin(); it!=dict->end(); ++it) {
    of<<(*it).first<<":"<<(*it).second<<std::endl;
  }
}
