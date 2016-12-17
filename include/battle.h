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

class Battle {
  public:
    Battle(std::string given, Model* m, Nouncer* nouncer, Denouncer* denouncer);
    ~Battle();
    // Spits the constructed fire
    void spit();

    // Builds the flame from a base word using a Model
    std::string traceBack(Word* base, std::string stressPattern, Model* m, Nouncer* n);

    // Returns the last word in the input string
    std::string getLast();

    WordList filterStressPattern(WordList* leadersList, std::string stressPattern);

  private:

    // The fire to be spit
    std::string fire;

    // The last word in the supplied line
    std::string lastGiven;

    // Get the stats about supplied line
    void updateLineStats(std::string given, Nouncer* nouncer);

    std::string doStressPattern(std::string given, Nouncer* nouncer);
};

#endif //BATTLE_H
