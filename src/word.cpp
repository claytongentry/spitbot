#include "word.h"

std::string Word::checkForNull(std::string name) {
  if (name != "_NULL_") {
    name = Utils::removePunc(name);
    name = Utils::noCaps(name);
  }
  return name;
}

Word::Word(std::string name, std::string stressPattern) :
    Element(checkForNull(name),
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
