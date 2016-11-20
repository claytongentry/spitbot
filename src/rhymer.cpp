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
  std::cout << "rhymer looking up base" << std::endl;
  std::string* base_phoneme = pd->lookUp(base);
  std::cout << "Phoneme for base " << base << ": " << *base_phoneme << std::endl;

  Word* word = new Word("gravy");
  return word;
}
