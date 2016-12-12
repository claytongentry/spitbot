/*
 * Battle implementation
 */

#include "battle.h"

/* Initializes the Battle object with information about the given line.
 * Calls a traceBack function to construct a response line.
 */
Battle::Battle(std::string given, Model* m, Nouncer* nouncer, Denouncer* denouncer) {
  updateLineStats(given, nouncer);

  int numWords   = getNumWords();
  Rhymer* rhymer = new Rhymer(nouncer, denouncer);
  Word* rhyme    = new Word(rhymer->rhyme(lastGiven));

  fire = traceBack_syls(rhyme, numWords, m, nouncer);

  delete rhymer;
  delete rhyme;
}

void Battle::spit() {
  std::cout << fire << std::endl;
}

Battle::~Battle(){}

/* Builds a response to the given line with the same number of words.*/
std::string Battle::traceBack_words(Word* base, int numWords, Model* m) {
  Word* _NULL_         = new Word("_NULL_");
  std::string response = base->getVal();

  //construct response by traversing the adjacency-list
  for (int addedWords = 1; addedWords < numWords; addedWords++) {
    // find word in model
    WordList* leadersList = m->find(base);
    Word* leader          = leadersList->pickLeader();

    // if _NULL_
    if (leader->getVal() == "_NULL_") {
      leadersList = m->find(_NULL_);
      leader      = leadersList->pickLeader();
    }

    // add it to the response
    response = leader->getVal() + " " + response;

    // set leader as new base
    base = leader;
  }

  delete _NULL_;

  return response;
}

/* Builds a response to the given line with the same number of syllables.*/
std::string Battle::traceBack_syls(Word* base, int numWords, Model* m, Nouncer* n) {
  Word* _NULL_         = new Word("_NULL_");
  std::string response = base->getVal();

  //get number of syls in base word
  int addedSyls = n->getSylCount(base->getVal());

  //construct response by traversing the adjacency-list
  while (addedSyls < numSyls) {
    // find word in model
    WordList* leadersList = m->find(base);
    Word* leader          = leadersList->pickLeader();

    // if _NULL_
    if (leader->getVal() == "_NULL_") {
      leadersList = m->find(_NULL_);
      leader      = leadersList->pickLeader();
    }

    // add it to the response
    response = leader->getVal() + " " + response;

    // set leader as new base
    base = leader;

    //update addedSyls
    addedSyls += n->getSylCount(base->getVal());
  }

  delete _NULL_;

  return response;
}

/*
 * Parses the input line and updates member variables with
 * relevant characteristics:
 * - word count
 * - syllable count
 * - last word of line (for rhyming)
 */
void Battle::updateLineStats(std::string given, Nouncer* n) {
  std::istringstream ss(given);
  std::string last;

  int words = 0;
  int syls = 0;

  while (ss >> last) {
    words++;
    syls += n->getSylCount(last);
  }

  lastGiven = last;
  numWords  = words;
  numSyls   = syls;
}

std::string Battle::getLast() {
  return lastGiven;
}

int Battle::getNumWords() {
  return numWords;
}
