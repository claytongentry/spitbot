/*
 * rhymer.h
 *
 * A class for identifying rhymes
 */


#ifndef rhymer_H
#define rhymer_H

#include "model.h"
#include "word.h"
#include "phonemeDict.h"

class Rhymer {
  public:
    Rhymer(PhonemeDict* phonemeDict);
    Word* rhyme(std::string base, Model* m);

  private:
    PhonemeDict* pd;
    std::string getPhoneme(std::string word);
};

#endif
