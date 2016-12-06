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

/*
 * Return a string that rhymes with the given string
 */
std::string Rhymer::rhyme(std::string baseWord) {
  std::string* baseNounce = n->lookUp(baseWord);
  int denouncerSize       = d->getSize();
  int baseIndex           = d->getIndex(*baseNounce);

  int index = randomizeSelection(baseIndex, 3, denouncerSize);

  return d->lookUp(index);
}

int Rhymer::randomizeSelection(int base, int radius, int size) {
  int start = (base - radius > 0)    ? (base - radius) : 0;
  int end   = (base + radius < size) ? (base + radius) : size;

  return Utils::randInRange(start, end);
}
