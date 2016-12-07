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
    ~Battle();
    // Spits the constructed fire
    void spit();

    // Builds the flame from a base word using a Model
    std::string traceBack_words(Word* base, int numWords, Model* m);
    std::string traceBack_syls(Word* base, int numSyls, Model* m, Nouncer* n);

    // Returns the last word in the input string
    std::string getLast();

    // Returns the number of words in the input string
    int getNumWords();

  private:

    // The fire to be spit
    std::string fire;

    // The last word in the supplied line
    std::string lastGiven;

    // The number of words in the supplied line
    int numWords;

    // The number of syllables in the supplied line
    int numSyls;

    // Get the stats about supplied line
    void updateLineStats(std::string given, Nouncer* nouncer);
};

#endif //BATTLE_H
