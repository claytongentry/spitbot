#include "word.h"

Word::Word(std::string name, std::string stressPattern) :
    Element(Utils::removePunc(Utils::noCaps(name)),
            {1, stressPattern}) {};

std::string Word::getName() {
  return Element::getKey();
}

int Word::getFrequency() {
  return value.frequency;
}

std::string Word::getStressPattern() {
  return value.stressPattern;
}

void Word::incrementFrequency() {
  value.frequency++;
}
