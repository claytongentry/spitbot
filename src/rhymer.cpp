/*
 * Rhymer implementation
 */

#include "rhymer.h"

Rhymer::Rhymer(Nouncer* n, Denouncer* d) {
  this->n = n;
  this->d = d;
}

Rhymer::~Rhymer() {
  n = nullptr;
  d = nullptr;
}

std::string Rhymer::rhyme(std::string base_word) {
  std::string* base_nounce = n->lookUp(base_word);
  std::cout << "Encoded phoneme for base " << base_word << ": " << *base_nounce << std::endl;

  /*
   * TODO: Look up a word that rhymes with base_nounce by going
   * a random(?) distance away from base_nounce in decnouncer
   */

  int index = d->getIndex(*base_nounce) + 1;

  if (index >= d->getSize()) index = index - 2;

  std::string rhyme_word    = d->lookUp(index);
  std::string* rhyme_nounce = n->lookUp(rhyme_word);

  std::cout << "Encoded phoneme for rhyme " << rhyme_word << ": " << *rhyme_nounce << std::endl;

  return rhyme_word;
}
