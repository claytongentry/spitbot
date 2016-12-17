/*
 * word.cpp
 */

#include "word.h"

Word::Word() {
  value = "";
  frequency = 0;
  stressPattern = {};
}

Word::Word(std::string val, std::string stress) {
  if (val != "_NULL_") {
    val = Utils::removePunc(val);
    val = Utils::noCaps(val);
  }

  value = val;
  frequency = 1;
  stressPattern = stress;
}

Word::~Word(){}

Word::Word(const Word& w) {
  value = w.value;
  frequency = w.frequency;
  stressPattern = w.stressPattern;
}

std::string Word::getVal() {
  return value;
}

int Word::getFrequency() {
  return frequency;
}

std::string Word::getStressPattern() {
  return stressPattern;
}

void Word::setVal(std::string newValue) {
  value = newValue;
}

void Word::setFrequency(int newFrequency) {
  frequency = newFrequency;
}

void Word::incrementFrequency() {
  frequency++;
}

bool Word::operator==(const Word& w) {
  return (w.value == this->value);
}

std::ostream& operator<<(std::ostream& os, const Word& w) {
  os<<w.value<<" | "<<w.frequency;
  return os;
}
