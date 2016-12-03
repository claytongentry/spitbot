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
#include "word.h"
#include "nouncer.h"
#include "denouncer.h"

class Rhymer {
  public:
    Rhymer(Nouncer* nouncer, Denouncer* denouncer);
    Word* rhyme(std::string base);

  private:
    Nouncer* n;
    Denouncer* d;
};

#endif
