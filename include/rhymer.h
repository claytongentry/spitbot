/*
 * rhymer.h
 *
 * A class for identifying rhymes
 */


#ifndef rhymer_H
#define rhymer_H

#include "model.h"
#include "word.h"

class Rhymer
{
  public:
    Word* rhyme(std::string base, Model* m);
};

#endif
