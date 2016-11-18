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
  std::vector<std::string>* base_phoneme = pd->lookUp(base);
  std::cout << "Phoneme for base " << base << " ";
  for(int i = 0; i < base_phoneme->size(); i++) {
      std::cout<<(*base_phoneme)[i]<<" ";
  }

  Word* word = new Word("gravy");
  return word;
}
