/*
 * Nouncer Implementation
 */

#include "nouncer.h"

/*
 * Assembles the map<word,phoneme> dictionary by reading one line at a time,
 * separating the word from the pronunciation, encoding the phoneme, and
 * putting the pair in the map
 */

std::vector<char> Nouncer::cons = {
  '9',':',';','<','I','J','K','T','U','V','W',
  'X','Y','h','i','j','k','l','m','v','w','y','z','{'
};

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
    return &(dict->at("GRAVY"));
  }
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
  char phone = '\0';

  if      (phoneme == "AA")  phone = ' ';
  else if (phoneme == "AA0") phone = '!';
  else if (phoneme == "AA1") phone = '\"';
  else if (phoneme == "AA2") phone = '#';
  else if (phoneme == "AE")  phone = '$';
  else if (phoneme == "AE0") phone = '%';
  else if (phoneme == "AE1") phone = '&';
  else if (phoneme == "AE2") phone = '(';
  else if (phoneme == "AH")  phone = ')';
  else if (phoneme == "AH0") phone = '*';
  else if (phoneme == "AH1") phone = '+';
  else if (phoneme == "AH2") phone = ',';
  else if (phoneme == "AO")  phone = '-';
  else if (phoneme == "AO0") phone = '.';
  else if (phoneme == "AO1") phone = '/';
  else if (phoneme == "AO2") phone = '0';
  else if (phoneme == "AW")  phone = '1';
  else if (phoneme == "AW0") phone = '2';
  else if (phoneme == "AW1") phone = '3';
  else if (phoneme == "AW2") phone = '4';
  else if (phoneme == "AY")  phone = '5';
  else if (phoneme == "AY0") phone = '6';
  else if (phoneme == "AY1") phone = '7';
  else if (phoneme == "AY2") phone = '8';
  else if (phoneme == "B")   phone = '9';
  else if (phoneme == "CH")  phone = ':';
  else if (phoneme == "D")   phone = ';';
  else if (phoneme == "DH")  phone = '<';
  else if (phoneme == "EH")  phone = '=';
  else if (phoneme == "EH0") phone = '>';
  else if (phoneme == "EH1") phone = '?';
  else if (phoneme == "EH2") phone = '@';
  else if (phoneme == "ER")  phone = 'A';
  else if (phoneme == "ER0") phone = 'B';
  else if (phoneme == "ER1") phone = 'C';
  else if (phoneme == "ER2") phone = 'D';
  else if (phoneme == "EY")  phone = 'E';
  else if (phoneme == "EY0") phone = 'F';
  else if (phoneme == "EY1") phone = 'G';
  else if (phoneme == "EY2") phone = 'H';
  else if (phoneme == "F")   phone = 'I';
  else if (phoneme == "G")   phone = 'J';
  else if (phoneme == "HH")  phone = 'K';
  else if (phoneme == "IH")  phone = 'L';
  else if (phoneme == "IH0") phone = 'M';
  else if (phoneme == "IH1") phone = 'N';
  else if (phoneme == "IH2") phone = 'O';
  else if (phoneme == "IY")  phone = 'P';
  else if (phoneme == "IY0") phone = 'Q';
  else if (phoneme == "IY1") phone = 'R';
  else if (phoneme == "IY2") phone = 'S';
  else if (phoneme == "JH")  phone = 'T';
  else if (phoneme == "K")   phone = 'U';
  else if (phoneme == "L")   phone = 'V';
  else if (phoneme == "M")   phone = 'W';
  else if (phoneme == "N")   phone = 'X';
  else if (phoneme == "NG")  phone = 'Y';
  else if (phoneme == "OW")  phone = 'Z';
  else if (phoneme == "OW0") phone = 'a';
  else if (phoneme == "OW1") phone = 'b';
  else if (phoneme == "OW2") phone = 'c';
  else if (phoneme == "OY")  phone = 'd';
  else if (phoneme == "OY0") phone = 'e';
  else if (phoneme == "OY1") phone = 'f';
  else if (phoneme == "OY2") phone = 'g';
  else if (phoneme == "P")   phone = 'h';
  else if (phoneme == "R")   phone = 'i';
  else if (phoneme == "S")   phone = 'j';
  else if (phoneme == "SH")  phone = 'k';
  else if (phoneme == "T")   phone = 'l';
  else if (phoneme == "TH")  phone = 'm';
  else if (phoneme == "UH")  phone = 'n';
  else if (phoneme == "UH0") phone = 'o';
  else if (phoneme == "UH1") phone = 'p';
  else if (phoneme == "UH2") phone = 'q';
  else if (phoneme == "UW")  phone = 'r';
  else if (phoneme == "UW0") phone = 's';
  else if (phoneme == "UW1") phone = 't';
  else if (phoneme == "UW2") phone = 'u';
  else if (phoneme == "V")   phone = 'v';
  else if (phoneme == "W")   phone = 'w';
  else if (phoneme == "Y")   phone = 'y';
  else if (phoneme == "Z")   phone = 'z';
  else if (phoneme == "ZH")  phone = '{';
  else
    std::cerr << "Could not identify phoneme " << phoneme << std::endl;

  return phone;
}

bool Nouncer::isVowel(char& phone) {
  return (std::find(cons.begin(),cons.end(),phone) == cons.end());
}

int Nouncer::getSylCount(std::string word) {
  int count = 0;
  std::string* nounce = lookUp(word);

  for (auto i = nounce->begin(); i != nounce->end(); ++i) {
    if ( isVowel(*i) ) count++;
  }

  return count;
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
