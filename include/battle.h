/*
 * A Battle object will take in a line provided by the user.
 * 1st iteration will simply choose a random word in the
 * adjacency-list and return a line of equal number of words
 */

#ifndef BATTLE_H
#define BATTLE_H

#include <cstdlib>
#include <ctime>
#include <sstream>

#include "model.h"
#include "nouncer.h"
#include "rhymer.h"
#include "word.h"

class Battle {
  public:
    Battle(std::string given, Model* m, Nouncer* nouncer, Denouncer* denouncer);

    // Spits the constructed flame
    void spit();

    // Builds the flame from a base word using a Model
    std::string traceBack(Word* base, int numWords, Model* m);

    //returns the last word in the input string
    std::string getLast();

    //return the number of words in the input string
    int getNumWords();

  private:

    // The flame to be spit
    std::string fire;

    std::string inLast;
    int numWords;

    void findLastAndCount(std::string given);
};

#endif //BATTLE_H
