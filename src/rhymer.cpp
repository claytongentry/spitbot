/*
 * Rhymer implementation
 */

#include <iostream>
#include <string>

#include "rhymer.h"
#include "model.h"

Rhymer::Rhymer(PhonemeDict* pd) {
  this->pd = pd;
}

Word* Rhymer::rhyme(std::string base, Model* m) {
  return new Word("gravy");
}

std::string getPhoneme(std::string word) {
  return "phoneme";
}
