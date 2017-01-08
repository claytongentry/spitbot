#ifndef WORD_H
#define WORD_H

#include <string>

#include "utils.h"

#include "element.h"

struct word_traits {
  int frequency;
  std::string stressPattern;
};

class Word : public Element<std::string, word_traits>{

public:
  Word() : Element() {};
  Word(std::string name, std::string stressPattern);

  std::string getName();
  int getFrequency();
  std::string getStressPattern();

  void incrementFrequency();

private:
  std::string checkForNull(std::string name);

};


#endif //WORD_H
