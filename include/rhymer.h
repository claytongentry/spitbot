/*
 * rhymer.h
 *
 * A class for identifying rhymes
 */


#ifndef rhymer_H
#define rhymer_H

#include <iostream>
#include <string>

#include "model.h"
#include "nouncer.h"
#include "denouncer.h"

class Rhymer {
  public:
    Rhymer(Nouncer* nouncer, Denouncer* denouncer);
    ~Rhymer();

    // Returns a rhyming Word for the given base
    std::string rhyme(std::string base);

  private:
    Nouncer* n;
    Denouncer* d;

    // Randomizes a number given
    static int randomizeSelection(int baseIndex, int radius, int size);
};

#endif
