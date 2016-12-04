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
  if (base - radius < 0) {
    return Utils::randInRange(0, base + radius);
  } else if (base + radius >= size) {
    return Utils::randInRange(base - radius, size);
  } else {
    int range = radius * 2 + 1;
    return base + (rand() % range - radius);
  }
}
